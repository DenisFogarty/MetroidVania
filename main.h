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
	float get_char_height();
	float get_char_width();

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;

	bool game_running;

	float mouse_x, mouse_y;
	float cursor_size;

	float char_x, char_y;
	float char_height, char_width;

	int num_x_buttons_pressed;
	int num_y_buttons_pressed;

	bool up_pressed, down_pressed;
	bool left_pressed, right_pressed;

	bool paused;

protected:

};

#endif // MAIN_H_INCLUDED
