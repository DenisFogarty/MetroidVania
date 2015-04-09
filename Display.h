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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <string>


class Display {
public:
	Display();

	void load_level();
	void update_screen_size(float screen_width, float screen_height);
	void camera_update(float* camera_position, float x, float y, float width, float height);
	void draw_bitmap(ALLEGRO_BITMAP *bitmap, float pos_x, float pos_y);
	void draw_text(char text[30], float pos_x, float pos_y);
	void draw_text(std::string text_string, float pos_x, float pos_y);
	void hide_mouse_pointer();
	void show_mouse_pointer();
	void set_default_display();

	virtual ~Display();

private:
	ALLEGRO_DISPLAY	*display;
	ALLEGRO_BITMAP	*background_layer_1;
	ALLEGRO_CONFIG	*config_level;
	ALLEGRO_MONITOR_INFO monitor_info;
	ALLEGRO_FONT *font;

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
