/*
 * sprites.cpp
 *
 *  Created on: 7 Mar 2015
 *      Author: denis2
 */

#include "Sprites.h"

std::map <std::string, std::vector<sprite>> sprites::sprite_list;
std::vector <std::string> sprites::sheets_split;

sprites::sprites() {
	config_main = al_load_config_file("sprite_data/main.conf");

	std::cout << al_get_config_value(config_main, "", "sheets") << std::endl;

	const char *sheets_all = al_get_config_value(config_main, "", "sheets");

	std::cout << sheets_all << std::endl;

	sheet_no = 0;
	char_pos = 0;
	i = 0;

	/*
	 * Reads in the entire list of sprite config files, and splits them up
	 */
	do {
		if(sheets_all[i] != ' ' && sheets_all[i] != ',' && sheets_all[i] != '\0') {
			sheet_indiv[char_pos] = sheets_all[i];
			std::cout << sheet_indiv[char_pos] << std::endl;
			char_pos++;
			sheet_indiv[char_pos] = '\0';
		}
		if(sheets_all[i] == ',' || sheets_all[i + 1] == '\0') {
			sheet_no++;
			char_pos = 0;
			sheets_split.push_back(sheet_indiv);
		}
		i++;
	} while(sheets_all[i] != '\0');


	sprite_conf[0] = 's';
	sprite_conf[1] = 'p';
	sprite_conf[2] = 'r';
	sprite_conf[3] = 'i';
	sprite_conf[4] = 't';
	sprite_conf[5] = 'e';
	sprite_conf[6] = '_';
	sprite_conf[7] = 'd';
	sprite_conf[8] = 'a';
	sprite_conf[9] = 't';
	sprite_conf[10] = 'a';
	sprite_conf[11] = '/';
	sprite_conf[12] = '\0';

	sprite_sheet_name[0] = 's';
	sprite_sheet_name[1] = 'p';
	sprite_sheet_name[2] = 'r';
	sprite_sheet_name[3] = 'i';
	sprite_sheet_name[4] = 't';
	sprite_sheet_name[5] = 'e';
	sprite_sheet_name[6] = 's';
	sprite_sheet_name[7] = '/';
	sprite_sheet_name[8] = '\0';

	block_no[0] = 'b';
	block_no[1] = 'l';
	block_no[2] = 'o';
	block_no[3] = 'c';
	block_no[4] = 'k';
	block_no[5] = ' ';
	block_no[6] = '\0';


	i = 0, j = 0;

	rows = 0, cols = 0;

	sprite_offset_x = 0;
	sprite_offset_y = 0;

	curr_block = 0;

	load_sprites();
}


void sprites::load_sprites() {
	/*
	 * Goes through each sprite config file, loads the individual sprites and stores them
	 */
	for(sheet_no = 0; sheet_no < sheets_split.size(); sheet_no++) {
		std::cout << sheets_split.at(sheet_no).size() << std::endl;

		for(i = 0; i < sheets_split.at(sheet_no).size(); i++) {
			sprite_conf[i + 12] = sheets_split.at(sheet_no)[i];
			new_sprite.sheet_name[i] = sheets_split.at(sheet_no)[i];
		}
		sprite_conf[i + 12] = '\0';

		config_sprites = al_load_config_file(sprite_conf);

		sprite_sheet_name[8] = '\0';
		strcat(sprite_sheet_name, al_get_config_value(config_sprites, "", "file"));
		sprite_sheet = al_load_bitmap(sprite_sheet_name);

		blocks = al_get_config_value(config_sprites, "", "blocks");

		for(curr_block = 1; curr_block <= (uint) std::stoi(blocks); curr_block++) {

			sprintf(int_string, "%d", curr_block);

			/*
			 * Sets the 7th character in the array to the terminating character, causing strcat to overwrite the previous number
			 */
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

			for(i = 0; i < rows; i++) {
				for(j = 0; j < cols; j++) {
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
		sprite_list[new_sprite.sheet_name] = sprite_block;
	}
}

std::map <std::string, std::vector<sprite>>* sprites::get_sprite_list() {
	return &sprite_list;
}

std::vector <std::string>* sprites::get_sprite_list_names() {
	return &sheets_split;
}

