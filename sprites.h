/*
 * sprites.h
 *
 *  Created on: 7 Mar 2015
 *      Author: denis2
 */

#ifndef SPRITES_H_
#define SPRITES_H_

#include <vector>
#include <map>
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
	char sheet_name[20];
};


class sprites {
public:
	sprites();

	void load_sprites();
	void draw_sprite();

	static std::map<char[20], std::vector<sprite>>* get_sprite_list();

private:
	ALLEGRO_BITMAP *sprite_sheet;
	ALLEGRO_CONFIG *config_main;
	ALLEGRO_CONFIG *config_sprites;

	char sheets_all[200];
	char sheet_indiv[20];
	std::vector <char[20]> sheets_split;
	int sheet_no;
	int char_pos;

	int num_sheets;

	std::string type;
	std::string blocks;

	char block_no[10];
	char int_string[4];

	int rows;
	int cols;

	sprite new_sprite_block;
	sprite new_sprite;
	std::vector<sprite> sprite_block;
	static std::map<char*, std::vector<sprite>> sprite_list;
	float sprite_offset_x;
	float sprite_offset_y;
	int curr_block;

	int i, j, k;

};

#endif /* SPRITES_H_ */
