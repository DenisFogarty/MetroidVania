/*
 * GameScreen.h
 *
 *  Created on: 17 Mar 2015
 *      Author: denis2
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "Items.h"
#include "Sprites.h"
#include "Movement.h"
#include "Display.h"
#include "Level.h"
#include "Shoot.h"

class exit_info {
public:
	std::string next_level;
	int next_x, next_y;
	int x1, y1, x2, y2;
};

class GameScreen {
public:
	GameScreen();

	void start_game(std::string start_level);
	void load_level(std::string next_level, int x, int y);
	void camera_update(float* camera_position, float x, float y, float width, float height);
	void cursor_update(float mouse_x, float mouse_y, Display *display);
	void refresh_screen(Display *display);
	void key_down(ALLEGRO_EVENT *event);
	void key_up(ALLEGRO_EVENT *event);
	void mouse_down(float mouse_x, float mouse_y, std::string button);
	void update_game();

	virtual ~GameScreen();

private:
	ALLEGRO_BITMAP	*foregrond_layer;
	ALLEGRO_BITMAP	*front_layer;
	ALLEGRO_BITMAP	*background;
	ALLEGRO_CONFIG	*config_main;
	ALLEGRO_CONFIG	*config_level;

	ALLEGRO_TRANSFORM camera;

	std::string level_names;
	std::vector<std::string> level_names_split;
	std::string current_level;

	float camera_position[2];
	float level_width;
	float level_height;

	int num_exits;
	exit_info next_exit;
	std::vector <exit_info> list_exits;

	ALLEGRO_BITMAP *cursor;
	float *mouse_x, *mouse_y;
	float cursor_size, cursor_middle;
	float cursor_color_r, cursor_color_g, cursor_color_b;

	float char_x, char_y;

	std::map <std::string, std::vector<sprite>>* sprite_list_curr;
	std::map<std::string, level> level_list;
	std::vector<std::string>* sprite_list_names;

	int start_x, start_y;

	bool moving_left, moving_right;

	char file_name[20];

	level level_class;
	movement calculate_movement;

	bullets_data add_bullets;
};

#endif /* GAMESCREEN_H_ */
