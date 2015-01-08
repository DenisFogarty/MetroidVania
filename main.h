#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class setup {
public:

private:

protected:
};

class refresh {
public:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;
	ALLEGRO_MUTEX *mutex;
	ALLEGRO_COND *cond;
	bool READY;

	refresh():
		display(al_create_display(640, 480)),
		foreground(al_create_bitmap(640, 480)),
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
