/*
 * sprites.h
 *
 *  Created on: 7 Mar 2015
 *      Author: denis2
 */

#ifndef SPRITES_H_
#define SPRITES_H_

#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

#include "items.h"

class sprite : public item {
public:
	bool collision;
	float sheet_pos_x;
	float sheet_pos_y;
	int sheet_no;
};


class sprites {
public:
	sprites();

	void load_sprites();
	static ALLEGRO_BITMAP* get_sprite_sheet(int pos);
	static std::vector<std::vector<sprite>>* get_sprite_list();

private:
	ALLEGRO_BITMAP *sprite_sheet;
	ALLEGRO_CONFIG *config_sprites;

	static std::vector<ALLEGRO_BITMAP*> sprite_sheet_list;
	int sheets;

	std::string type;
	std::string blocks;

	char block_no[10];
	char int_string[3];

	int rows;
	int cols;

	sprite new_sprite_block;
	sprite new_sprite;
	std::vector<sprite> block_sprites;
	static std::vector<std::vector<sprite>> sprite_list;
	float sprite_offset_x;
	float sprite_offset_y;
	int curr_block;

	int i, j, k;

};

#endif /* SPRITES_H_ */
