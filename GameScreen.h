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

class GameScreen {
public:
	GameScreen();

	void load_level();
	void camera_update(float* camera_position, float x, float y, float width, float height);
	void cursor_update(float mosue_x, float mouse_y);

	virtual ~GameScreen();

private:
	ALLEGRO_DISPLAY	*display;
	ALLEGRO_BITMAP	*background_layer_1;
	ALLEGRO_BITMAP	*background_layer_2;
	ALLEGRO_BITMAP	*background_layer_3;
	ALLEGRO_CONFIG	*config_main;
	ALLEGRO_CONFIG	*config_level;

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
	std::vector<std::string>* sprite_list_names;

	char file_name[20];

	items_data items;
};

#endif /* GAMESCREEN_H_ */
