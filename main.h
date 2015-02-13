#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "shoot.h"
#include "movement.h"

#define screenwidth 640
#define screenheight 480

class draw_display {
public:
	draw_display();
	~draw_display();

	void game_loop();
	void camera_update(float* camera_position, float x, float y, float width, float height);

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *foreground;
	ALLEGRO_BITMAP *cursor;

	bool game_running;

	float mouse_x, mouse_y;
	float cursor_size;
	float cursor_middle;
	float cursor_color_r, cursor_color_g, cursor_color_b;

	float char_x, char_y;

	int num_x_buttons_pressed;
	int num_y_buttons_pressed;

	bool up_pressed, down_pressed;
	bool left_pressed, right_pressed;

	bool paused;

	float camera_position[2];

protected:

};

#endif // MAIN_H_INCLUDED
