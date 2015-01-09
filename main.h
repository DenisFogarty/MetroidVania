#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class draw_display {
public:
	ALLEGRO_MUTEX *mutex;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;
private:

protected:
};

class refresh {
public:
	ALLEGRO_MUTEX *mutex;
	ALLEGRO_COND *cond;
	bool READY;

	refresh():
		mutex(al_create_mutex()),
		cond(al_create_cond()),
		READY(false)
	{}

	~refresh() {
		al_destroy_mutex(mutex);
		al_destroy_cond(cond);
	}
};

#endif // MAIN_H_INCLUDED
