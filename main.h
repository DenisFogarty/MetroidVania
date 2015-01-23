#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "shoot.h"
#include "classlist.h"

class draw_display {
public:
	draw_display();
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;
	~draw_display();

private:

protected:

};

class SHOOT {
public:
	float x1, y1, x2, y2;
	ALLEGRO_MUTEX *mutex;
	ALLEGRO_COND *cond;
	bool READY;
	SHOOT():
		x1(0),
		y1(0),
		x2(10),
		y2(10),
		mutex(al_create_mutex()),
		cond(al_create_cond()),
		READY(false)
	{}
	shoot calc;

protected:

};

#endif // MAIN_H_INCLUDED
