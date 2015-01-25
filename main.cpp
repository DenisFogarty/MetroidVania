#include "main.h"

const float FPS = 60.0;
float INC_X = 0;
float INC_Y = 0;
const int SCREEN_W = 600;
const int SCREEN_H = 480;

static void *shoot(ALLEGRO_THREAD *thread, void *arg);

int main() {
	ALLEGRO_EVENT_QUEUE *event_queue    = NULL;
	ALLEGRO_TIMER       *timer		    = NULL;
	ALLEGRO_THREAD		*shoot_thread	= NULL;

	if(!al_init()) {
		fprintf(stderr, "Failed to initialise Allegro");
		return -1;
	}

	if(!al_init_primitives_addon()) {
		fprintf(stderr, "Failed to initialise Allegro Primitives");
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "Failed to install keyboard");
		return -1;
	}

	timer = al_create_timer(1.0/FPS);
	if(!timer) {
		fprintf(stderr, "Failed to initialize timer");
		return -1;
	}

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		//al_destroy_bitmap(foreground);
		al_destroy_timer(timer);
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "Failed to initialize mouse\n");
		//al_destroy_bitmap(foreground);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	draw_display draw;

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(draw.display));

	ALLEGRO_EVENT ev;


	uint32_t version = al_get_allegro_version();

	int major = version >> 24;
	int minor = (version >> 16) &255;
	int revision = (version >> 8) &255;
	int release = version &255;


	std::cout << major << "." << minor << "." << revision << "[" << release << "]" << std::endl;


	shoot_thread = al_create_thread(shoot, &void);
	al_start_thread(shoot_thread);


	al_set_target_bitmap(al_get_backbuffer(draw.display));

	al_start_timer(timer);

	al_hide_mouse_cursor(draw.display);

	while(1) {
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_flip_display();
		}else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
	}

	al_destroy_thread(shoot_thread);
}


draw_display::draw_display() {
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(640, 480);

	foreground = al_create_bitmap(640, 480);
}


draw_display::~draw_display() {
	al_destroy_display(display);
	al_destroy_bitmap(foreground);
}


static void *shoot(ALLEGRO_THREAD *thread, void *arg) {


	ALLEGRO_EVENT_QUEUE *game_event = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0/1000.0);

	al_register_event_source(game_event, al_get_keyboard_event_source());
	al_register_event_source(game_event, al_get_mouse_event_source());
	al_register_event_source(game_event, al_get_timer_event_source(timer));
	al_register_event_source(game_event, al_get_mouse_event_source());

	float speedx = .4;
	float speedy = .3;

	al_start_timer(timer);

	ALLEGRO_EVENT ev;

	while(!al_get_thread_should_stop(thread)) {
		al_wait_for_event(game_event, &ev);

		if(ev.type != ALLEGRO_EVENT_TIMER) {

			if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			}

		} else {
			//Call shoot.h to calculate bullets position
		}
	}
}
