/*
 * leveleditor.cpp
 *
 *  Created on: 12 Mar 2015
 *      Author: denis2
 */

#include "LevelEditor.h"

LevelEditor::LevelEditor() {
	//	sprite_list_curr = sprites::get_sprite_list();

	window_main = al_create_bitmap(900, 900);
	window_main_background = al_create_bitmap(900, 900);
	window_main_menu = al_create_bitmap(300, 900);
	window_tiles = al_create_bitmap(400, 500);
	window_tile_editor = al_create_bitmap(400, 300);
	window_tile_menu = al_create_bitmap(400, 100);

	al_set_target_bitmap(window_main);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(window_tiles);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(window_main_menu);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(window_tile_editor);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(window_tile_menu);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	display_foreground = true;
	display_background = true;

	sprite_list_curr = sprites::get_sprite_list();
	sprite_sheet_names = sprites::get_sprite_list_names();
}


void LevelEditor::select_tile_tab(uint tab) {
	if(tab < sprite_sheet_names->size()) {

		current_tab = tab;
		current_page = 1;
		pages = ((*sprite_list_curr)[(*sprite_sheet_names).at(tab)].size())/20;
		if(((*sprite_list_curr)[sprite_sheet_names->at(tab)].size()) % 20 > 0) {
			pages++;
		}

	} else {
		std::cout << "Tab does not exist" << std::endl;
	}
}


void LevelEditor::load_tile_page(uint page) {
	if(page < pages) {

		current_page = page;

		al_set_target_bitmap(window_tiles);
		al_clear_to_color(al_map_rgb(255, 255, 255));

		uint current_sprite = page * 20;

		uint i = 0;
		/*
		 * x and y used to determine the tile each bitmap is to be drawn in
		 */
		uint x = 0, y = 0;

		float width = 0, height = 0;
		float width_scale = 0, height_scale = 0;

		bool scale = false;

		/*
		 * Loop for drawing sprites to tile window
		 */
		while(current_sprite < (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].size() && i < 20) {
			curr_bitmap = (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].at(current_sprite).item_sprite;

			width = al_get_bitmap_width(curr_bitmap);
			height = al_get_bitmap_height(curr_bitmap);
			if(width >= 100.0 || height >= 100.0) {
				width_scale = width/100.0;
				height_scale = height/100.0;
				scale = true;
			}

			if(scale) {
				if(al_get_bitmap_width(curr_bitmap) > al_get_bitmap_height(curr_bitmap)) {
					al_draw_scaled_bitmap(curr_bitmap, 0, 0, width, height, 0, (y / 4)  * 100 + (50 - ((height / width_scale) / 2)), 100, height / width_scale, 0);
				} else {
					al_draw_scaled_bitmap(curr_bitmap, 0, 0, width, height, (y / 4)  * 100 + (50 - ((width / height_scale) / 2)), 0, 100, width / height_scale, 0);
				}
			} else {
				al_draw_bitmap(curr_bitmap, (x % 4) * 100 + (50 - (width / 2)), (y / 4)  * 100 + (50 - (height / 2)), 0);
			}

			scale = false;

			i++;
			x++;
			y++;
			current_sprite++;
		}
	} else {
		std::cout << "Page does not exist" << std::endl;
	}
}


void LevelEditor::draw_windows(Display *display) {
	display->draw_bitmap(window_main_background, 300, 0);
	display->draw_bitmap(window_main, 300, 0);
	display->draw_bitmap(window_main_menu, 0, 0);
	display->draw_bitmap(window_tiles, 1200, 100);
	display->draw_bitmap(window_tile_editor, 1200, 600);
	display->draw_bitmap(window_tile_menu, 1200, 0);
}


LevelEditor::~LevelEditor() {
	al_destroy_bitmap(window_main);
	al_destroy_bitmap(window_main_menu);
	al_destroy_bitmap(window_tiles);
	al_destroy_bitmap(window_tile_menu);
	al_destroy_bitmap(window_tile_editor);
}
