/*
 * GameScreen.cpp
 *
 *  Created on: 17 Mar 2015
 *      Author: denis2
 */

#include "GameScreen.h"

GameScreen::GameScreen() {
	//The following creates the in-game cursor
	mouse_x = 0;
	mouse_y = 0;
	cursor_size = 16;
	cursor_middle = cursor_size/2;

	cursor_color_r = 255;
	cursor_color_g = 0;
	cursor_color_b = 0;

	cursor = al_create_bitmap(cursor_size, cursor_size);
	if(!cursor) {
		fprintf(stderr, "Failed to initialise the bitmap cursor/n");
	}

	al_set_target_bitmap(cursor);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(cursor, al_map_rgb(0, 0, 0));

	al_draw_circle(cursor_middle, cursor_middle, cursor_middle - 1, al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b), 2);

	al_draw_pixel(cursor_middle,	cursor_middle,		al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
	al_draw_pixel(cursor_middle-1,	cursor_middle,		al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
	al_draw_pixel(cursor_middle,	cursor_middle+1,	al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
	al_draw_pixel(cursor_middle-1,	cursor_middle+1,	al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
};


void GameScreen::load_level() {
	if(!(config_main = al_load_config_file("level/main.conf"))) {
		fprintf(stderr, "Main file not found\n");
	}

	file_name[0] = 's';
	file_name[1] = 'p';
	file_name[2] = 'r';
	file_name[3] = 'i';
	file_name[4] = 't';
	file_name[5] = 'e';
	file_name[6] = 's';
	file_name[7] = '/';
	file_name[8] = '\0';
}


void GameScreen::camera_update(float* camera_position, float x, float y, float width, float height) {
	camera_position[0] = -(level_width / 2) + (x + width / 2);
	camera_position[1] = -(level_height / 2) + (y + height / 2);

	if(camera_position[0] < 0) {
		camera_position[0] = 0;
	}
	else if(camera_position[0] > 1280) {
		camera_position[0] = 1280;
	}
	if(camera_position[1] < 0) {
		camera_position[1] = 0;
	}
	else if(camera_position[1] > 600) {
		camera_position[1] = 600;
	}
}


void GameScreen::cursor_update(float mouse_x, float mouse_y) {
	//	al_set_target_bitmap(al_get_backbuffer(display));
	//	al_draw_bitmap(cursor, mouse_x, mouse_y, 0);
}


GameScreen::~GameScreen() {
	// TODO Auto-generated destructor stub
}

