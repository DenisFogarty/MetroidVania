/*
 * Display.cpp
 *
 *  Created on: 25 Mar 2015
 *      Author: denis2
 */

#include "Display.h"

Display::Display() {
	screen_width = 1600;
	screen_height = 900;

	if(!al_init_primitives_addon()) {
		fprintf(stderr, "Failed to initialise the primitives addon\n");
	}


	if(!al_init_image_addon()) {
		fprintf(stderr, "Failed to install image addon\n");
	}


	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(screen_width, screen_height);
	if(!display) {
		fprintf(stderr, "Failed to initialise the display\n");
	}


	/*
	 * Move this to other function in same class
	 */
	background_layer_1 = al_load_bitmap("sprites/land3.png");
	if(!background_layer_1) {
		fprintf(stderr, "Failed to initialise the bitmap foreground\n");
	}

	al_get_monitor_info(0, &monitor_info);

	screen_width_full = monitor_info.x2;
	screen_height_full = monitor_info.y2;

	screen_width_chosen = 1600;
	screen_height_chosen = 900;

	al_set_target_bitmap(al_get_backbuffer(display));
}


void Display::draw_bitmap(ALLEGRO_BITMAP *bitmap, float pos_x, float pos_y) {
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(bitmap, pos_x, pos_y, 0);
}


Display::~Display() {
	al_destroy_display(display);
	al_destroy_bitmap(background_layer_1);
//	al_destroy_bitmap(background_layer_2);
//	al_destroy_bitmap(background_layer_3);
//	al_destroy_config(config_main);
//	al_destroy_config(config_level);
}

