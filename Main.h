#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <list>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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
	virtual void key_event(ALLEGRO_EVENT *event) {};
	virtual void key_release(ALLEGRO_EVENT *event) {};
	virtual void mouse_event(std::string button) {};
	virtual void start(Display *display) {};
	virtual void exit_loop() {};

	void determine_event(Display *display);

	float mouse_x, mouse_y;

	bool loop_running;
	bool paused;

	virtual ~Control() {};

private:
	ALLEGRO_EVENT_QUEUE		*event_queue = al_create_event_queue();
	ALLEGRO_EVENT			event;

	ALLEGRO_TIMER       	*refresh_timer;
	ALLEGRO_TIMER			*game_timer;

	ALLEGRO_MOUSE_STATE		mouse_state;
};

class ControlEditor : public Control {
public:
	void key_event(ALLEGRO_EVENT *event);
	void key_release(ALLEGRO_EVENT *event);
	void mouse_event(std::string button);
	void start(Display *display);
	void exit_loop();

	~ControlEditor();

private:
	LevelEditor level_editor;

};

class ControlGame : public Control {
public:
	void key_event(ALLEGRO_EVENT *event);
	void key_release(ALLEGRO_EVENT *event);
	void mouse_event(std::string button);
	void start(Display *display);
	void exit_loop();

	~ControlGame();

private:
	GameScreen game_screen;

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
	level this_level;

	//	bullets_data add_bullets;
	//	movement char_move;
	//	items_data add_item;
	//	sprites add_sprites;
	//	level load_level;
	//	leveleditor level_editor;

	//	int next;

};

#endif // MAIN_H_INCLUDED
