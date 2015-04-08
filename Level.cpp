/*
 * level.cpp
 *
 *  Created on: 10 Mar 2015
 *      Author: denis2
 */

#include "Level.h"
#include "Sprites.h"

level::level() {

}

void level::load_sprites(std::string level_name) {

	for(uint i = 0; i < level_name.size(); i++) {
		level_local_name[i] = level_name[i];
		level_local_name[i + 1] = '\0';
	}

	strcat(level_full_name, level_local_name);

	config_level = al_load_config_file(level_full_name);

	num_sprites = std::stoi(al_get_config_value(config_level, "", "sprites"));
	num_exits = std::stoi(al_get_config_value(config_level, "", "exits"));
	width = std::stoi(al_get_config_value(config_level, "", "width"));
	height = std::stoi(al_get_config_value(config_level, "", "height"));

	char current_sprite[15] = {'s', 'p', 'r', 'i', 't', 'e', '_', '\0'};
	char current_num[4];
	for(uint i = 1; i <= num_sprites; i++) {
		sprintf(current_num, "%d", i);
		strcat(current_sprite, current_num);

		temp_sprite_info.x = std::stoi(al_get_config_value(config_level, current_sprite, "x"));
		temp_sprite_info.y = std::stoi(al_get_config_value(config_level, current_sprite, "y"));
		temp_sprite_info.sheet_name = al_get_config_value(config_level, current_sprite, "name");
		temp_sprite_info.sprite_pos_list = std::stoi(al_get_config_value(config_level, current_sprite, "num"));
		temp_sprite_info.layer = al_get_config_value(config_level, current_sprite, "layer");
		temp_sprite_info.sprite_bitmap = (*sprite_list_pointer)[temp_sprite_info.sheet_name].at(temp_sprite_info.sprite_pos_list).item_sprite;

		current_sprite[7] = '\0';

		if(temp_sprite_info.x <= width && temp_sprite_info.y <= height) {
			level_sprites.push_back(temp_sprite_info);
		}
	}

	level_local_name[0] = '\0';
	level_full_name[7] = '\0';

	//	temp_sprite_info.x = al_get_config_value();
}

void level::draw_sprites(int i) {

}

level::~level() {

}
