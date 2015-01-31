#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "shoot.h"

class draw_display {
public:
	draw_display();
	~draw_display();

	void game_loop();

	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;
	bool game_running;

private:

protected:

};

#endif // MAIN_H_INCLUDED
