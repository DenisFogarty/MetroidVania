#include "main.h"

const float FPS = 120.0;
const int SCREEN_W = 600;
const int SCREEN_H = 480;

int main() {
	if(!al_init()) {
		fprintf(stderr, "Failed to initialise Allegro\n");
		return -1;
	}

	if(!al_init_primitives_addon()) {
		fprintf(stderr, "Failed to initialise Allegro Primitives\n");
	}

	al_init_image_addon();

	if(!al_install_keyboard()) {
		fprintf(stderr, "Failed to install keyboard\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "Failed to install mouse\n");
		return -1;
	}

	draw_display draw;

	uint version = al_get_allegro_version();

	int major = version >> 24;
	int minor = (version >> 16) &255;
	int revision = (version >> 8) &255;
	int release = version &255;

	std::cout << major << "." << minor << "." << revision << "[" << release << "]" << std::endl;

	draw.game_loop();
}


draw_display::draw_display() {
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(640, 480);
	if(!display) {
		fprintf(stderr, "Failed to initialise the display/n");
	}


	foreground = al_load_bitmap("sprites/land.png");
	if(!foreground) {
		fprintf(stderr, "Failed to initialise the bitmap foreground/n");
	}


	{//The following creates the in-game cursor
		mouse_x = 0;
		mouse_y = 0;
		cursor_size = 16;
		cursor_middle = cursor_size/2;

		cursor_color_r = 255;
		cursor_color_g = 0;
		cursor_color_b = 0;

		cursor = al_create_bitmap(cursor_size, cursor_size);
		if(!cursor) {
			fprintf(stderr, "Failed to initialise the bitmap cursor/n");
		}

		al_set_target_bitmap(cursor);

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_convert_mask_to_alpha(cursor, al_map_rgb(0, 0, 0));

		al_draw_circle(cursor_middle, cursor_middle, cursor_middle - 1, al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b), 2);

		al_draw_pixel(cursor_middle,	cursor_middle,		al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
		al_draw_pixel(cursor_middle-1,	cursor_middle,		al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
		al_draw_pixel(cursor_middle,	cursor_middle+1,	al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
		al_draw_pixel(cursor_middle-1,	cursor_middle+1,	al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
	}


	al_set_target_bitmap(al_get_backbuffer(display));

	char_x = 0;
	char_y = 0;

	num_x_buttons_pressed = 0;
	num_y_buttons_pressed = 0;

	left_pressed = false;
	right_pressed = false;
	up_pressed = false;
	down_pressed = false;

	paused = false;

	game_running = true;
}


void draw_display::game_loop() {
	ALLEGRO_EVENT_QUEUE 	*event_queue    = NULL;
	ALLEGRO_TIMER       	*refresh_timer	= NULL;
	ALLEGRO_TIMER			*game_timer		= NULL;

	ALLEGRO_MOUSE_STATE		mouse_state;


	refresh_timer = al_create_timer(1.0/FPS);
	if(!refresh_timer) {
		fprintf(stderr, "Failed to initialise refresh timer\n");
	}

	game_timer = al_create_timer(1.0/1000);
	if(!game_timer) {
		fprintf(stderr, "Failed to initialise game timer/n");
	}

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_timer(refresh_timer);
	}


	al_register_event_source(event_queue, al_get_timer_event_source(refresh_timer));
	al_register_event_source(event_queue, al_get_timer_event_source(game_timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	ALLEGRO_EVENT ev;

	al_set_target_bitmap(al_get_backbuffer(display));

	al_hide_mouse_cursor(display);

	bullets_data add_bullets;
	movement char_move;

	al_start_timer(refresh_timer);
	al_start_timer(game_timer);


	//Main game loop
	while(game_running) {
		al_wait_for_event(event_queue, &ev);

		switch(ev.type)
		{

		case ALLEGRO_EVENT_TIMER:
			if(ev.timer.source == refresh_timer) {
				al_clear_to_color(al_map_rgb(0, 0, 0));

				al_draw_bitmap(foreground, 0, 0, 0);

				add_bullets.draw_to_screen(*display);

				char_move.draw_character(*display);

				al_draw_bitmap(cursor, mouse_x, mouse_y, 0);

				al_flip_display();

			} else if (ev.timer.source == game_timer && !paused){	//game_timer
				add_bullets.calculate_direction();
				char_move.calculate_movement();
			}

			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			if(ev.keyboard.keycode == ALLEGRO_KEY_W) {
				char_move.set_direction(up);
				up_pressed = true;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
				char_move.set_direction(left);
				left_pressed = true;
				num_x_buttons_pressed += 1;
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
				char_move.set_direction(right);
				right_pressed = true;
				num_x_buttons_pressed += 1;
			}

			break;

		case ALLEGRO_EVENT_KEY_UP:
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				if(!paused) {
					paused = true;
				}
				else {
					paused = false;
				}
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_W){
				up_pressed = false;
				char_move.set_direction(down);
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_A){
				num_x_buttons_pressed -= 1;
				left_pressed = false;
				if(right_pressed) {
					char_move.set_direction(right);
				}
			}
			else if(ev.keyboard.keycode == ALLEGRO_KEY_D){
				num_x_buttons_pressed -= 1;
				right_pressed = false;
				if(left_pressed) {
					char_move.set_direction(left);
				}
			}

			if(num_x_buttons_pressed == 0) {
				char_move.set_direction(stop_x);
			}

			break;

		case ALLEGRO_EVENT_MOUSE_AXES:
			char_x = char_move.get_x();
			char_y = char_move.get_y();
			if(ev.mouse.x != char_x || ev.mouse.y != char_y) {
				mouse_x = ev.mouse.x;
				mouse_y = ev.mouse.y;
			}

			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if(!paused) {
				char_x = char_move.get_x();
				char_y = char_move.get_y();

				al_get_mouse_state(&mouse_state);

				if(al_mouse_button_down(&mouse_state, 1)) {
					add_bullets.add_bullet(char_x, char_y, mouse_x, mouse_y);
				}
			}

			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			game_running = false;

			break;

		default:
			break;
		}
	}
}


draw_display::~draw_display() {
	al_destroy_display(display);
	al_destroy_bitmap(foreground);
}
