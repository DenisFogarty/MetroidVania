/*
 * Display.h
 *
 *  Created on: 25 Mar 2015
 *      Author: denis2
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "Items.h"
#include "Sprites.h"
#include "LevelEditor.h"

class Display {
public:
	Display();

	void load_level();
	void camera_update(float* camera_position, float x, float y, float width, float height);
	void cursor_update(float mosue_x, float mouse_y);

	virtual ~Display();

private:
	ALLEGRO_DISPLAY	*display;
	ALLEGRO_BITMAP	*background_layer_1;
	ALLEGRO_BITMAP	*background_layer_2;
	ALLEGRO_BITMAP	*background_layer_3;
	ALLEGRO_CONFIG	*config_main;
	ALLEGRO_CONFIG	*config_level;
	ALLEGRO_MONITOR_INFO monitor_info;

	float camera_position[2];
	float screen_width;
	float screen_height;

	char file_name[20];

	items_data items;
};

#endif /* DISPLAY_H_ */
