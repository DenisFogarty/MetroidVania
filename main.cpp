#include "shoot.h"
#include "logic.h"
#include "main.h"

const float FPS = 60.0;
float INC_X = 0;
float INC_Y = 0;
const int SCREEN_W = 600;
const int SCREEN_H = 480;
const int PLAYER_SIZE = 32;

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

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());


	draw_display draw;
	SHOOT shoot_data;
	SHOOT2 shoot_data2;



	shoot_thread = al_create_thread(shoot, &shoot_data);
	al_start_thread(shoot_thread);

	al_lock_mutex(shoot_data.mutex);
	while(!shoot_data.READY) {
		al_wait_cond(shoot_data.cond, shoot_data.mutex);
	}
	al_unlock_mutex(shoot_data.mutex);



	al_set_target_bitmap(al_get_backbuffer(draw.display));

	int i = 0;

	while(i < 300) {
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_lock_mutex(shoot_data.mutex);

		al_draw_line(shoot_data.x1, shoot_data.y1, shoot_data.x2, shoot_data.y2, al_map_rgb(255, 0, 0), 3);

		al_unlock_mutex(shoot_data.mutex);


		al_lock_mutex(shoot_data2.mutex);

		al_draw_line(shoot_data2.x1, shoot_data2.y1, shoot_data2.x2, shoot_data2.y2, al_map_rgb(0, 255, 0), 3);

		al_unlock_mutex(shoot_data2.mutex);


		al_flip_display();

		i++;

		al_rest(1.0/60.0);
	}

	al_destroy_thread(shoot_thread);
	al_destroy_cond(shoot_data.cond);
	al_destroy_cond(shoot_data2.cond);
}


draw_display::draw_display() {
	display = al_create_display(640, 480);
	foreground = al_create_bitmap(640, 480);
}

draw_display::~draw_display() {
	al_destroy_display(display);
	al_destroy_bitmap(foreground);
}


static void *shoot(ALLEGRO_THREAD *thread, void *arg) {
	SHOOT *shoot_data = (SHOOT*) arg;

	al_lock_mutex(shoot_data->mutex);
	shoot_data->READY = true;
	al_broadcast_cond(shoot_data->cond);
	al_unlock_mutex(shoot_data->mutex);

	while(!al_get_thread_should_stop(thread)) {
		al_lock_mutex(shoot_data->mutex);

		shoot_data->x1 += 1;
		shoot_data->y1 += 1;
		shoot_data->x2 += 1;
		shoot_data->y2 += 1;

		al_unlock_mutex(shoot_data->mutex);

		std::cout << shoot_data->x1 << std::endl;

		al_rest(1.0/120.0);
	}
}
