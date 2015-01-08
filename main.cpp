#include "shoot.h"
#include "logic.h"
#include "main.h"

const float FPS = 60;
float INC_X = 0;
float INC_Y = 0;
const int SCREEN_W = 600;
const int SCREEN_H = 480;
const int PLAYER_SIZE = 32;

static void *refresh_thread(ALLEGRO_THREAD *thread, void *arg);

int main() {
	ALLEGRO_EVENT_QUEUE *event_queue    = NULL;
	ALLEGRO_TIMER       *timer		    = NULL;
	ALLEGRO_THREAD		*refresh_1		= NULL;


	if(!al_init()) {
		fprintf(stderr, "Failed to initialize Allegro");
		return -1;
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

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//shoot shoot_data = shoot(display);
	//logic logic_data = logic(display);

	refresh refresh_data;

	//Creating thread for screen refresh
	refresh_1 = al_create_thread(refresh_thread, &refresh_data);
	al_start_thread(refresh_1);

	//Locks refresh_data to prevent conflicts
	al_lock_mutex(refresh_data.mutex);

	//Loops until first thread is ready
	while (!refresh_data.READY) {
		al_wait_cond(refresh_data.cond, refresh_data.mutex);
	}
	al_unlock_mutex(refresh_data.mutex);


	//shoot shoot_data = shoot();

	al_rest(5);
}

static void *refresh_thread(ALLEGRO_THREAD *thread, void *arg) {
	refresh *refresh_data = (refresh*) arg;

	//Block sets data then broadcasts ready condition
	{
		al_lock_mutex(refresh_data->mutex);

		refresh_data->READY = true;
		al_broadcast_cond(refresh_data->cond);

		al_unlock_mutex(refresh_data->mutex);
	}


	al_set_target_bitmap(al_get_backbuffer(refresh_data->display));

	int i = 0;

	while(!al_get_thread_should_stop(thread)) {
		al_clear_to_color(al_map_rgb(i, 0, 0));
		al_flip_display();

		al_rest(1/120);
		i++;
		std::cout << i << std::endl;
	}
}
