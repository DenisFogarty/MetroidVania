#include "main.h"

float FPS = 60.0;
float GAME_UPDATE = 500;
float SCREEN_WIDTH = 640.0;
float SCREEN_HEIGHT = 480.0;

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

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(!display) {
		fprintf(stderr, "Failed to initialise the display/n");
	}


	foreground = al_load_bitmap("sprites/land3.png");
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


	left_pressed = false;
	right_pressed = false;

	basic = true;

	paused = false;

	game_running = true;

	next = 0;
}


void draw_display::camera_update(float* camera_position, float x, float y, float width, float height) {
	camera_position[0] = -(SCREEN_WIDTH / 2) + (x + width / 2);
	camera_position[1] = -(SCREEN_HEIGHT / 2) + (y + height / 2);

	if(camera_position[0] < 0) {
		camera_position[0] = 0;
	}
	else if(camera_position[0] > 1280) {
		camera_position[0] = 1280;
	}
	if(camera_position[1] < 0) {
		camera_position[1] = 0;
	}
	else if(camera_position[1] > 600) {
		camera_position[1] = 600;
	}
}


void draw_display::timer() {
	if(ev.timer.source == refresh_timer) {
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_draw_bitmap(foreground, 0, 0, 0);

		add_bullets.draw_to_screen(*display);

		add_item.draw_items();

		//		add_sprites.draw_sprite();

		load_level.draw_sprites(next);

		char_move.draw_character(*display);

		char_x = char_move.get_x();
		char_y = char_move.get_y();

		camera_update(camera_position, char_x, char_y, 20, 40);

		al_identity_transform(&camera);
		al_translate_transform(&camera, -camera_position[0], -camera_position[1]);		//Moves objects as the screen moves
		al_use_transform(&camera);

		al_draw_bitmap(cursor, mouse_x + camera_position[0], mouse_y + camera_position[1], 0);

		al_flip_display();

	} else if (ev.timer.source == game_timer && !paused){	//game_timer
		add_bullets.calculate_movement();
		char_move.calculate_movement();
	}
}


void draw_display::key_down() {
	if(ev.keyboard.keycode == ALLEGRO_KEY_W) {
		char_move.set_direction(up);
	}
	else if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
		char_move.set_direction(left);
		left_pressed = true;
	}
	else if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
		char_move.set_direction(right);
		right_pressed = true;
	}
	else if(ev.keyboard.keycode == ALLEGRO_KEY_R) {
		if(basic) {
			basic = false;
		} else {
			basic = true;
		}
	}
	else if(ev.keyboard.keycode == ALLEGRO_KEY_G) {
		add_item.add_items(100, 100, 0);
	}
}


void draw_display::key_up() {
	if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		if(!paused) {
			paused = true;
		}
		else {
			paused = false;
		}
	}
	else if(ev.keyboard.keycode == ALLEGRO_KEY_W){
		char_move.set_direction(stop_jump);
	}
	else if(ev.keyboard.keycode == ALLEGRO_KEY_A){
		left_pressed = false;
		if(right_pressed) {
			char_move.set_direction(right);
		}
		else {
			char_move.set_direction(stop_x);
		}
	}
	else if(ev.keyboard.keycode == ALLEGRO_KEY_D){
		right_pressed = false;
		if(left_pressed) {
			char_move.set_direction(left);
		}
		else {
			char_move.set_direction(stop_x);
		}
	}
}


void draw_display::mouse_down() {
	if(!paused) {
		char_x = char_move.get_x();
		char_y = char_move.get_y();

		mouse_x = ev.mouse.x;
		mouse_y = ev.mouse.y;

		al_get_mouse_state(&mouse_state);

		if(al_mouse_button_down(&mouse_state, 1)) {
			if(basic) {
				add_bullets.add_basic(char_x, char_y, mouse_x + camera_position[0], mouse_y + camera_position[1]);
			} else {
				add_bullets.add_rocket(char_x, char_y, mouse_x + camera_position[0], mouse_y + camera_position[1]);
			}
		}
		else if(al_mouse_button_down(&mouse_state, 2)) {
			//			add_item.add_items(mouse_x + camera_position[0], mouse_y + camera_position[1], 0);
			add_item.add_items(mouse_x + camera_position[0], mouse_y + camera_position[1], 0);
		}
	}
}


void draw_display::game_loop() {
	refresh_timer = al_create_timer(1.0/FPS);
	if(!refresh_timer) {
		fprintf(stderr, "Failed to initialise refresh timer\n");
	}

	game_timer = al_create_timer(1.0/GAME_UPDATE);
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

	al_set_target_bitmap(al_get_backbuffer(display));

	al_hide_mouse_cursor(display);

	al_start_timer(refresh_timer);
	al_start_timer(game_timer);

	add_item.add_items(50, 50, 0);
	add_item.add_items(250, 250, 0);

	add_sprites.load_sprites();

	load_level.load_sprites();


	//Main game loop
	while(game_running) {
		al_wait_for_event(event_queue, &ev);

		switch(ev.type)
		{

		case ALLEGRO_EVENT_TIMER:
			timer();

			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			key_down();

			break;

		case ALLEGRO_EVENT_KEY_UP:
			key_up();

			break;

		case ALLEGRO_EVENT_MOUSE_AXES:
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;

			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			mouse_down();

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
