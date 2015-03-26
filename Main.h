#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "GameScreen.h"
#include "GameScreen.h"
#include "Items.h"
#include "Level.h"
#include "LevelEditor.h"
#include "Movement.h"
#include "Shoot.h"
#include "Sprites.h"
#include "Display.h"

class draw_display {
public:
	draw_display();

	void game_loop();
	void camera_update(float* camera_position, float x, float y, float width, float height);

	~draw_display();

private:
	ALLEGRO_DISPLAY			*display;
	ALLEGRO_BITMAP			*foreground;
	ALLEGRO_BITMAP			*cursor;
	ALLEGRO_EVENT_QUEUE 	*event_queue    = NULL;
	ALLEGRO_TIMER       	*refresh_timer	= NULL;
	ALLEGRO_TIMER			*game_timer		= NULL;

	ALLEGRO_MOUSE_STATE		mouse_state;
	ALLEGRO_TRANSFORM		camera;
	ALLEGRO_EVENT			ev;

	bool game_running;

	float mouse_x, mouse_y;
	float cursor_size;
	float cursor_middle;
	float cursor_color_r, cursor_color_g, cursor_color_b;

	float char_x, char_y;

	bool left_pressed, right_pressed;

	bool basic;

	bool paused;

	float camera_position[2];

	void timer();
	void key_down();
	void key_up();
	void mouse_down();

//	bullets_data add_bullets;
//	movement char_move;
//	items_data add_item;
//	sprites add_sprites;
//	level load_level;
//	leveleditor level_editor;

	int next;

};

#endif // MAIN_H_INCLUDED
