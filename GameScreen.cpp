/*
 * GameScreen.cpp
 *
 *  Created on: 17 Mar 2015
 *      Author: denis2
 */

#include "GameScreen.h"

GameScreen::GameScreen() {
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(level_width, level_height);
	if(!display) {
		fprintf(stderr, "Failed to initialise the display/n");
	}

	background_layer_1 = al_load_bitmap("sprites/land3.png");
	if(!background_layer_1) {
		fprintf(stderr, "Failed to initialise the bitmap foreground/n");
	}

	al_set_target_bitmap(al_get_backbuffer(display));
}


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



GameScreen::~GameScreen() {
	// TODO Auto-generated destructor stub
}

