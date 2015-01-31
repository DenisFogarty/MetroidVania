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

	if(!al_install_keyboard()) {
		fprintf(stderr, "Failed to install keyboard\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "Failed to install mouse\n");
		return -1;
	}


	draw_display draw;

	draw.game_loop();


	uint version = al_get_allegro_version();

	int major = version >> 24;
	int minor = (version >> 16) &255;
	int revision = (version >> 8) &255;
	int release = version &255;

	std::cout << major << "." << minor << "." << revision << "[" << release << "]" << std::endl;
}


draw_display::draw_display() {
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	display = al_create_display(640, 480);
	if(!display) {
		fprintf(stderr, "Failed to initialise the display/n");
	}

	foreground = al_create_bitmap(640, 480);
	if(!foreground) {
		fprintf(stderr, "Failed to initialise the bitmap foreground/n");
	}

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

				add_bullets.draw_to_screen(*display);

				al_flip_display();

			} else {	//game_timer
				add_bullets.calculate_direction();
			}
			break;

		case ALLEGRO_EVENT_KEY_UP:
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {

				al_stop_timer(refresh_timer);
				al_wait_for_event(event_queue, &ev);		//Clears current event (key_down, ALLEGRO_KEY_ESCAPE)

				while(ev.type != ALLEGRO_EVENT_KEY_UP || ev.keyboard.keycode != ALLEGRO_KEY_ESCAPE) {
					al_wait_for_event(event_queue, &ev);
				}

				al_start_timer(refresh_timer);
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			al_get_mouse_state(&mouse_state);

			if(al_mouse_button_down(&mouse_state, 1)) {
				add_bullets.add_bullet(320, 240, 325, 245, 27, -4, 76.3, 459);
			}

			if (al_mouse_button_down(&mouse_state, 2)){
				add_bullets.remove_bullet(0);
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
