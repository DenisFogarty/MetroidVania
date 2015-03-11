/*
 * sprites.cpp
 *
 *  Created on: 7 Mar 2015
 *      Author: denis2
 */

#include "sprites.h"

std::vector<std::vector<sprite>> sprites::sprite_list;

sprites::sprites() {
	config_sprites = al_load_config_file("blocks.conf");

	type =  al_get_config_value(config_sprites, "", "type");

	blocks = al_get_config_value(config_sprites, "", "blocks");

	const char* file_name = al_get_config_value(config_sprites, "", "file");

	sprite_sheet = al_load_bitmap(file_name);

	sheets = 0;

	block_no[0] = 'b';
	block_no[1] = 'l';
	block_no[2] = 'o';
	block_no[3] = 'c';
	block_no[4] = 'k';
	block_no[5] = ' ';

	i = 0, j = 0, k = 0;

	rows = 0, cols = 0;

	sprite_offset_x = 0;
	sprite_offset_y = 0;

	curr_block = 0;
}


void sprites::load_sprites() {
	new_sprite.sheet_no = 0;

	for(i = 1; i <= std::stoi(blocks); i++) {

		sprintf(int_string, "%d", i);

		//Sets the 7th character in the array to the terminating character, causing strcat to overwrite the previous number
		block_no[6] = '\0';

		strcat(block_no, int_string);

		/*
		 * Stores the information from the config files in memory
		 * Also saves individual bitmaps of each sprite
		 */
		new_sprite_block.sheet_pos_x = std::stoi(al_get_config_value(config_sprites, block_no, "startx"));
		new_sprite_block.sheet_pos_y = std::stoi(al_get_config_value(config_sprites, block_no, "starty"));
		new_sprite_block.width = std::stoi(al_get_config_value(config_sprites, block_no, "width"));
		new_sprite_block.height = std::stoi(al_get_config_value(config_sprites, block_no, "height"));
		rows = std::stoi(al_get_config_value(config_sprites, block_no, "rows"));
		cols = std::stoi(al_get_config_value(config_sprites, block_no, "cols"));

		for(j = 0; j < rows; j++) {
			for(k = 0; k < cols; k++) {
				new_sprite.sheet_pos_x = new_sprite_block.sheet_pos_x + sprite_offset_x;
				new_sprite.sheet_pos_y = new_sprite_block.sheet_pos_y + sprite_offset_y;
				new_sprite.width = new_sprite_block.width;
				new_sprite.height = new_sprite_block.height;

				sprite_offset_x += new_sprite_block.width;

				std::cout << new_sprite.sheet_pos_x << " ";
				std::cout << new_sprite.sheet_pos_y << std::endl;

				new_sprite.item_sprite = al_create_sub_bitmap(sprite_sheet, new_sprite.sheet_pos_x, new_sprite.sheet_pos_y, new_sprite.width, new_sprite.height);

				sprite_block.push_back(new_sprite);
			}
			sprite_offset_y += new_sprite_block.height;
			sprite_offset_x = 0;
		}

		sprite_offset_x = 0;
		sprite_offset_y = 0;
	}
	curr_block++;
	sprite_list.push_back(sprite_block);
}

void sprites::draw_sprite() {
	al_draw_bitmap(sprite_sheet, 200, 1000, 0);
}

std::vector<std::vector<sprite>>* sprites::get_sprite_list() {
	return &sprite_list;
}

