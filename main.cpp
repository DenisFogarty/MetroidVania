#include "shoot.h"
#include "logic.h"
#include "main.h"

const float FPS = 60.0;
float INC_X = 0;
float INC_Y = 0;
const int SCREEN_W = 600;
const int SCREEN_H = 480;
const int PLAYER_SIZE = 32;

static void *refresh_thread(ALLEGRO_THREAD *thread, void *arg);

draw_display draw;

int main() {
	ALLEGRO_EVENT_QUEUE *event_queue    = NULL;
	ALLEGRO_TIMER       *timer		    = NULL;
	ALLEGRO_THREAD		*refresh_1		= NULL;
	ALLEGRO_DISPLAY		*display		= NULL;

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

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	draw.display = al_create_display(640, 480);
	draw.foreground = al_create_bitmap(640, 480);
	draw.mutex = al_create_mutex();
	*draw.READY = false;
	draw.cond = al_create_cond();

	//shoot shoot_data = shoot(display);
	//logic logic_data = logic(display);

	refresh refresh_data;

	//Creating thread for screen refresh
	refresh_1 = al_create_thread(refresh_thread, &refresh_data);
	std::cout << "Thread created" << std::endl;
	al_start_thread(refresh_1);
	std::cout << "Thread started" << std::endl;

	//Locks refresh_data to prevent conflicts
	//al_lock_mutex(refresh_data.mutex);

	//Loops until first thread is ready
	while (!draw.READY) {
		al_wait_cond(draw.cond, draw.mutex);
	}
	al_unlock_mutex(draw.mutex);


	shoot shoot_data = shoot(draw.foreground, draw.mutex, draw.cond, draw.READY);

	al_rest(5);
}


static void *refresh_thread(ALLEGRO_THREAD *thread, void *arg) {
	refresh *refresh_data = (refresh*) arg;

	//Block sets data then broadcasts ready condition
	{
		al_lock_mutex(draw.mutex);
		std::cout << "mutex locked" << std::endl;

		*draw.READY = true;
		al_broadcast_cond(draw.cond);

		al_unlock_mutex(draw.mutex);
		std::cout << "mutex unlocked" << std::endl;
	}

	al_set_target_bitmap(al_get_backbuffer(draw.display));
	std::cout << "display set as target" << std::endl;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	std::cout << "display flipped" << std::endl;
	//al_draw_line(0, 0, 50, 50, al_map_rgb(255, 0, 0), 5);

	while(!al_get_thread_should_stop(thread)) {
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		al_lock_mutex(draw.mutex);
		while (!draw.READY) {
			al_wait_cond(draw.cond, draw.mutex);
		}

		*draw.READY = false;
		std::cout << "mutex locked" << std::endl;
		/*al_lock_bitmap(draw->foreground, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
		{
			al_draw_bitmap(draw->foreground, 0, 0, 0);
		}*/
		al_lock_bitmap(draw.foreground, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);
		std::cout << "bitmap locked" << std::endl;

		al_draw_bitmap(draw.foreground, 0, 0, 0);
		std::cout << "bitmap drawn" << std::endl;

		al_flip_display();
		std::cout << "display flipped" << std::endl;

		al_unlock_bitmap(draw.foreground);
		std::cout << "bitmap unlocked" << std::endl;

		al_unlock_mutex(draw.mutex);
		*draw.READY = true;
		al_broadcast_cond(draw.cond);
		std::cout << "mutex unlocked" << std::endl;

		al_rest(1.0/60.0);
	}
}
