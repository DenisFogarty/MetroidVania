#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "shoot.h"
#include "movement.h"

class draw_display {
public:
	draw_display();
	~draw_display();

	void game_loop();

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;

	bool game_running;
	float mouse_x, mouse_y;

protected:

};

#endif // MAIN_H_INCLUDED
