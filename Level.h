/*
 * level.h
 *
 *  Created on: 10 Mar 2015
 *      Author: denis2
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "Sprites.h"

#include <iostream>
#include <string>

class load_sprite_info {
public:
	ALLEGRO_BITMAP *sprite_bitmap;
	int x, y;
	std::string sheet_name;	//Name of sprite config files, used to identify the block of sprites
	int sprite_pos_list;
	std::string layer;
	float width, height;

};

class exits {
public:
	float exit_x1, exit_y1, exit_x2, exit_y2;

};

class level {
public:
	level();

	void load_sprites(std::string level_name);
	void draw_sprites(int i);

	virtual ~level();


	ALLEGRO_CONFIG	*config_level;

	load_sprite_info temp_sprite_info;

	std::map <std::string, std::vector<sprite>>* sprite_list_pointer = sprites::get_sprite_list();

	uint num_sprites;
	uint num_exits;
	uint width;
	uint height;

	std::vector<load_sprite_info> level_sprites;
	std::vector<exits> level_exits;

	char level_local_name[33];
	char level_full_name[40] = {'l', 'e', 'v', 'e', 'l', 's', '/', '\0'};

};

#endif /* LEVEL_H_ */
