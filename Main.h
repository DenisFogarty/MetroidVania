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

class Control {
public:
	virtual void key_event() {};
	virtual void mouse_event() {};
	void determine_event(Display *display);

	virtual ~Control() {};
};

class ControlMenu : public Control {
public:
	void key_event() {};
	void mouse_event() {};

	~ControlMenu();

};

class ControlEditor : public Control {
public:
	void key_event();
	void mouse_event();

	~ControlEditor();

};

class ControlGame : public Control {
public:
	void key_event();
	void mouse_event();

	~ControlGame();

};


class MainGame {
public:
	void main_menu(Display *display);
	void camera_update(float* camera_position, float x, float y, float width, float height);

	~MainGame() {};

private:
	ALLEGRO_BITMAP			*cursor;
	ALLEGRO_BITMAP			*menu_picture;

	ALLEGRO_EVENT_QUEUE 	*event_queue    = NULL;
	ALLEGRO_EVENT			event;

	ALLEGRO_TIMER       	*refresh_timer	= NULL;
	ALLEGRO_TIMER			*game_timer		= NULL;

	ALLEGRO_MOUSE_STATE		mouse_state;

	ALLEGRO_KEYBOARD_EVENT	*keyboard_event;

	bool game_running;

	float mouse_x, mouse_y;
	float cursor_size;
	float cursor_middle;

	void timer();
	void key_down();
	void key_up();
	void mouse_down();

	Control *control;
	ControlEditor control_editor;
	ControlGame control_game;
	ControlMenu control_menu;

	//	bullets_data add_bullets;
	//	movement char_move;
	//	items_data add_item;
	//	sprites add_sprites;
	//	level load_level;
	//	leveleditor level_editor;

	//	int next;

};

#endif // MAIN_H_INCLUDED
