#include "main.h"

const float FPS = 120.0;
const int SCREEN_W = 600;
const int SCREEN_H = 480;


int main() {
	ALLEGRO_EVENT_QUEUE *event_queue    = NULL;
	ALLEGRO_TIMER       *timer		    = NULL;
	ALLEGRO_TIMER		*timer2			= NULL;
	ALLEGRO_MOUSE_STATE	mouse_state;

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

	timer = al_create_timer(1.0/FPS);
	if(!timer) {
		fprintf(stderr, "Failed to initialize timer\n");
		return -1;
	}
	timer2 = al_create_timer(1.0/1000);

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_timer(timer);
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "Failed to initialize mouse\n");
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	draw_display draw;

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(timer2));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(draw.display));

	ALLEGRO_EVENT ev;


	uint version = al_get_allegro_version();

	int major = version >> 24;
	int minor = (version >> 16) &255;
	int revision = (version >> 8) &255;
	int release = version &255;


	std::cout << major << "." << minor << "." << revision << "[" << release << "]" << std::endl;


	al_set_target_bitmap(al_get_backbuffer(draw.display));

	al_start_timer(timer);
	al_start_timer(timer2);

	al_hide_mouse_cursor(draw.display);

	bullets_data add_bullets;

	//Main game logic
	while(draw.game_running) {
		al_wait_for_event(event_queue, &ev);

		switch(ev.type)
		{

		case ALLEGRO_EVENT_TIMER:
			if(ev.timer.source == timer) {
				al_clear_to_color(al_map_rgb(0, 0, 0));

				add_bullets.draw_to_screen(*draw.display);

				al_flip_display();

			} else {	//timer2
				add_bullets.calculate_position();
			}
			break;

		case ALLEGRO_EVENT_KEY_UP:
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {

				al_stop_timer(timer);
				al_wait_for_event(event_queue, &ev);		//Clears current event (key_down, ALLEGRO_KEY_ESCAPE)

				while(ev.type != ALLEGRO_EVENT_KEY_UP || ev.keyboard.keycode != ALLEGRO_KEY_ESCAPE) {
					al_wait_for_event(event_queue, &ev);
				}

				al_start_timer(timer);
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			al_get_mouse_state(&mouse_state);

			if(mouse_state.buttons & 1) {
				add_bullets.add_bullet(0, 0, 5, 5, 0, 0, 50, 50);
			} else if (mouse_state.buttons & 2){
				add_bullets.remove_bullet(3);
			}
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			draw.game_running = false;
			break;

		default:
			break;
		}
	}
}


draw_display::draw_display() {
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(640, 480);

	foreground = al_create_bitmap(640, 480);

	game_running = true;
}


draw_display::~draw_display() {
	al_destroy_display(display);
	al_destroy_bitmap(foreground);
}
