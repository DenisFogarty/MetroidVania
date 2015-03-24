/*
 * leveleditor.cpp
 *
 *  Created on: 12 Mar 2015
 *      Author: denis2
 */

#include "LevelEditor.h"

leveleditor::leveleditor() {
//	sprite_list_curr = sprites::get_sprite_list();

	window_main = al_create_bitmap(480, 480);
	window_tiles = al_create_bitmap(160, 360);
	window_tile_editor = al_create_bitmap(160, 120);

	al_set_target_bitmap(window_main);
	al_clear_to_color(al_map_rgb(255, 0, 0));

	al_set_target_bitmap(window_tiles);
	al_clear_to_color(al_map_rgb(0, 255, 0));

	al_set_target_bitmap(window_tile_editor);
	al_clear_to_color(al_map_rgb(0, 0, 255));
}

void leveleditor::draw_windows() {
	al_draw_bitmap(window_main, 0, 0, 0);
	al_draw_bitmap(window_tiles, 480, 0, 0);
	al_draw_bitmap(window_tile_editor, 480, 360, 0);
}

leveleditor::~leveleditor() {
	// TODO Auto-generated destructor stub
}
