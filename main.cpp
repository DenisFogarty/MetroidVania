#include "shoot.h"
#include "main.h"

const float FPS = 60;
float INC_X = 0;
float INC_Y = 0;
const int SCREEN_W = 600;
const int SCREEN_H = 480;
const int PLAYER_SIZE = 32;

int main() {
    ALLEGRO_EVENT_QUEUE *event_queue    = NULL;
	ALLEGRO_TIMER       *timer		    = NULL;
	ALLEGRO_DISPLAY     *display        = NULL;

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

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "Failed to initialize display");
		al_destroy_timer(timer);
		return -1;
	}

	event_queue = al_create_event_queue();
	if(!event_queue) {
	   fprintf(stderr, "failed to create event_queue!\n");
	   al_destroy_display(display);
	   al_destroy_timer(timer);
	   return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "Failed to initialize mouse\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//shoot shoot_data = shoot(display);

    al_rest(3);
}
