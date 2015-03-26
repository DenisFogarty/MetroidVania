/*
 * Display.cpp
 *
 *  Created on: 25 Mar 2015
 *      Author: denis2
 */

#include "Display.h"

Display::Display() {
	screen_width = 1280;
	screen_height = 720;

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

	std::cout << monitor_info.x2 << std::endl;
	al_rest(5);

	al_set_target_bitmap(al_get_backbuffer(display));
}

Display::~Display() {
	// TODO Auto-generated destructor stub
}

