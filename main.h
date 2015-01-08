#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class setup {
public:
	static ALLEGRO_DISPLAY *display;
private:

protected:
};

class refresh {
public:
	ALLEGRO_MUTEX *mutex;
	ALLEGRO_COND *cond;
	bool ready;

	refresh():
		mutex(al_create_mutex()),
		cond(al_create_cond()),
		ready(false)
	{}

	~refresh() {
		al_destroy_mutex(mutex);
		al_destroy_cond(cond);
	}
};

#endif // MAIN_H_INCLUDED
