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
#include "LevelEditor.h"
#include "Display.h"
#include "Level.h"
#include "Shoot.h"

class GameScreen {
public:
	GameScreen();

	void start_game(std::string start_level);
	void load_level(std::string next_level, int x, int y);
	void camera_update(float* camera_position, float x, float y, float width, float height);
	void cursor_update(float mosue_x, float mouse_y);
	void refresh_screen(Display *display);
	void update_game();

	virtual ~GameScreen();

private:
	ALLEGRO_DISPLAY	*display;
	ALLEGRO_BITMAP	*background_layer;
	ALLEGRO_BITMAP	*foregrond_layer;
	ALLEGRO_BITMAP	*front_layer;
	ALLEGRO_BITMAP	*background;
	ALLEGRO_CONFIG	*config_main;
	ALLEGRO_CONFIG	*config_level;
	ALLEGRO_CONFIG	*config_start;

	std::string level_names;
	std::vector<std::string> level_names_split;

	float camera_position[2];
	float level_width;
	float level_height;

	ALLEGRO_BITMAP *cursor;
	float mouse_x, mouse_y;
	float cursor_size, cursor_middle;
	float cursor_color_r, cursor_color_g, cursor_color_b;

	std::map <std::string, std::vector<sprite>>* sprite_list_curr;
	std::map<std::string, level> level_list;
	std::vector<std::string>* sprite_list_names;

	std::string start_level;
	int start_x, start_y;

	char file_name[20];

	level level_class;

//	items_data items;
};

#endif /* GAMESCREEN_H_ */
