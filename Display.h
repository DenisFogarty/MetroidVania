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


class Display {
public:
	Display();

	void load_level();
	void update_screen_size(float screen_width, float screen_height);
	void camera_update(float* camera_position, float x, float y, float width, float height);
	void draw_bitmap(ALLEGRO_BITMAP *bitmap, float pos_x, float pos_y);

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
	float screen_width_full;
	float screen_height_full;
	float screen_width_chosen;
	float screen_height_chosen;
	float multiply_to_scale_width;
	float multiply_to_scale_height;

	char file_name[20];
};

#endif /* DISPLAY_H_ */
