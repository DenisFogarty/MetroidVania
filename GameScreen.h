/*
 * GameScreen.h
 *
 *  Created on: 17 Mar 2015
 *      Author: denis2
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include <allegro5/allegro.h>
#include <stdio.h>

#include "items.h"
#include "sprites.h"

class GameScreen {
public:
	GameScreen();

	void load_level();
	void camera_update(float* camera_position, float x, float y, float width, float height);

	virtual ~GameScreen();

private:
	ALLEGRO_DISPLAY	*display;
	ALLEGRO_BITMAP	*background_layer_1;
	ALLEGRO_BITMAP	*background_layer_2;
	ALLEGRO_BITMAP	*background_layer_3;
	ALLEGRO_CONFIG	*config_main;
	ALLEGRO_CONFIG	*config_level;

	float camera_position[2];
	float level_width;
	float level_height;

	char file_name[20];

	items_data items;
};

#endif /* GAMESCREEN_H_ */
