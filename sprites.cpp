/*
 * sprites.cpp
 *
 *  Created on: 7 Mar 2015
 *      Author: denis2
 */

#include "sprites.h"

std::map<char[20], std::vector<sprite>> sprites::sprite_list;

sprites::sprites() {
	config_main = al_load_config_file("sprite_data/main.conf");

	sheets_all = (char *) malloc(sizeof(al_get_config_value(config_sprites, "", "sheets")));

	*sheets_all = *al_get_config_value(config_sprites, "", "sheets");

	sheet_no = 0;
	char_pos = 0;
	i = 0;
//
//	/*
//	 * Reads in the entire list of sprite config files, and splits them up
//	 */
//	while(sheets_all[i] != '\0') {
//		if(sheets_all[i] == ',') {
//			sheet_no++;
//			char_pos = 0;
//			sheets_split.push_back(sheet_indiv);
//		}
//		else if(sheets_all[i] != ' ') {
//			sheet_indiv[char_pos] = sheets_all[i];
//			char_pos++;
//		}
//		i++;
//	}
//	sheets_split.push_back(sheet_indiv);

	//	blocks = al_get_config_value(config_sprites, "", "blocks");
	//
	//	const char* file_name = al_get_config_value(config_sprites, "", "file");
	//
	//	sprite_sheet = al_load_bitmap(file_name);
	//
	//	num_sheets = 0;
	//
	block_no[0] = 'b';
	block_no[1] = 'l';
	block_no[2] = 'o';
	block_no[3] = 'c';
	block_no[4] = 'k';
	block_no[5] = ' ';
	//
	//	i = 0, j = 0, k = 0;
	//
	//	rows = 0, cols = 0;
	//
	//	sprite_offset_x = 0;
	//	sprite_offset_y = 0;
	//
	//	curr_block = 0;

	std::cout << sheets_split.size();
}


void sprites::load_sprites() {
	/*
	 * Goes through each sprite config file, loads the individual sprites and stores them
	 */
//	for(curr_sheet = 0; curr_sheet < sheets_split.size(); curr_sheet++) {
//
//		for(i = 0; i < sizeof(new_sprite.sheet_name)/sizeof(new_sprite.sheet_name[0]); i++) {
//			new_sprite.sheet_name[i] = sheets_split.at(curr_sheet)[i];
//		}
//
//		for(curr_block = 1; curr_block <= std::stoi(blocks); curr_block++) {
//
//			sprintf(int_string, "%d", curr_block);
//
//			/*
//			 * Sets the 7th character in the array to the terminating character, causing strcat to overwrite the previous number
//			 */
//			block_no[6] = '\0';
//
//			strcat(block_no, int_string);
//
//			/*
//			 * Stores the information from the config files in memory
//			 * Also saves individual bitmaps of each sprite
//			 */
//			new_sprite_block.sheet_pos_x = std::stoi(al_get_config_value(config_sprites, block_no, "startx"));
//			new_sprite_block.sheet_pos_y = std::stoi(al_get_config_value(config_sprites, block_no, "starty"));
//			new_sprite_block.width = std::stoi(al_get_config_value(config_sprites, block_no, "width"));
//			new_sprite_block.height = std::stoi(al_get_config_value(config_sprites, block_no, "height"));
//			rows = std::stoi(al_get_config_value(config_sprites, block_no, "rows"));
//			cols = std::stoi(al_get_config_value(config_sprites, block_no, "cols"));
//
//			for(i = 0; i < rows; i++) {
//				for(j = 0; j < cols; j++) {
//					new_sprite.sheet_pos_x = new_sprite_block.sheet_pos_x + sprite_offset_x;
//					new_sprite.sheet_pos_y = new_sprite_block.sheet_pos_y + sprite_offset_y;
//					new_sprite.width = new_sprite_block.width;
//					new_sprite.height = new_sprite_block.height;
//
//					sprite_offset_x += new_sprite_block.width;
//
//					std::cout << new_sprite.sheet_pos_x << " ";
//					std::cout << new_sprite.sheet_pos_y << std::endl;
//
//					new_sprite.item_sprite = al_create_sub_bitmap(sprite_sheet, new_sprite.sheet_pos_x, new_sprite.sheet_pos_y, new_sprite.width, new_sprite.height);
//
//					sprite_block.push_back(new_sprite);
//				}
//				sprite_offset_y += new_sprite_block.height;
//				sprite_offset_x = 0;
//			}
//
//			sprite_offset_x = 0;
//			sprite_offset_y = 0;
//		}
//		sprite_list[new_sprite.sheet_name] = sprite_block;
//	}
}

void sprites::draw_sprite() {
	al_draw_bitmap(sprite_sheet, 200, 1000, 0);
}

std::map<char[20], std::vector<sprite>>* sprites::get_sprite_list() {
	return &sprite_list;
}

