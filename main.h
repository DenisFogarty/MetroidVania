#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class draw_display {
public:
	draw_display();
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;

private:

protected:

};

class SHOOT {
public:
	int x1, y1, x2, y2;
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

private:

protected:

};

class SHOOT2 {
public:
	int x1, y1, x2, y2;
	ALLEGRO_MUTEX *mutex;
	ALLEGRO_COND *cond;
	bool READY;
	SHOOT2():
		x1(640),
		y1(0),
		x2(630),
		y2(10),
		mutex(al_create_mutex()),
		cond(al_create_cond()),
		READY(false)
	{}

private:

protected:

};

#endif // MAIN_H_INCLUDED
