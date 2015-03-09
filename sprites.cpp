/*
 * sprites.cpp
 *
 *  Created on: 7 Mar 2015
 *      Author: denis2
 */

#include "sprites.h"

std::vector <sprite> sprites::list_sprite_blocks;

sprites::sprites() {
	config_sprites = al_load_config_file("blocks.conf");

	type =  al_get_config_value(config_sprites, "", "type");

	blocks = al_get_config_value(config_sprites, "", "blocks");

	file_name = al_get_config_value(config_sprites, "", "file");

	block_no[0] = 'b';
	block_no[1] = 'l';
	block_no[2] = 'o';
	block_no[3] = 'c';
	block_no[4] = 'k';
	block_no[5] = ' ';

	i = 0, j = 0, k = 0;

	rows = 0, cols = 0;
}

void sprites::load_sprites() {
	for(i = 1; i <= std::stoi(blocks); i++) {

		sprintf(int_string, "%d", i);

		//Sets the 7th character in the array to the terminating character, causing strcat to overwrite the previous number
		block_no[6] = '\0';

		strcat(block_no, int_string);

		printf("%s\n", block_no);

		rows = std::stoi(al_get_config_value(config_sprites, block_no, "rows"));

		cols = std::stoi(al_get_config_value(config_sprites, block_no, "cols"));

		new_sprite_block.sheet_pos_x = std::stoi(al_get_config_value(config_sprites, block_no, "startx"));
		new_sprite_block.sheet_pos_y = std::stoi(al_get_config_value(config_sprites, block_no, "starty"));
		new_sprite_block.width = std::stoi(al_get_config_value(config_sprites, block_no, "width"));
		new_sprite_block.height = std::stoi(al_get_config_value(config_sprites, block_no, "height"));
		new_sprite_block.rows = std::stoi(al_get_config_value(config_sprites, block_no, "rows"));
		new_sprite_block.cols = std::stoi(al_get_config_value(config_sprites, block_no, "cols"));

		list_sprite_blocks.push_back(new_sprite_block);
	}
}

sprites::~sprites() {
	// TODO Auto-generated destructor stub
}
