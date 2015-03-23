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
	char sheet_name[100];
};


class sprites {
public:
	sprites();

	void load_sprites();
	void draw_sprite();

	static std::map<std::string, std::vector<sprite>>* get_sprite_list();

private:
	ALLEGRO_BITMAP *sprite_sheet;
	ALLEGRO_CONFIG *config_main;
	ALLEGRO_CONFIG *config_sprites;

	char sheet_indiv[20];
	std::vector <std::string> sheets_split;
	uint num_sheets;
	uint sheet_no;
	uint char_pos;

	std::string type;
	std::string blocks;

	char sprite_conf[100];
	char sprite_sheet_name[100];
	char block_no[20];
	char int_string[4];

	uint rows;
	uint cols;

	sprite new_sprite_block;
	sprite new_sprite;
	std::vector<sprite> sprite_block;
	static std::map<std::string, std::vector<sprite>> sprite_list;
	float sprite_offset_x;
	float sprite_offset_y;
	uint curr_sheet;
	uint curr_block;

	uint i, j;

};

#endif /* SPRITES_H_ */
