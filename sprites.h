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
	int rows, cols;
};


class sprites {
public:
	sprites();

	void load_sprites();

	virtual ~sprites();

private:
	ALLEGRO_BITMAP *sprite_sheet;
	ALLEGRO_CONFIG *config_sprites;

	std::string temp;

	std::string type;
	std::string blocks;
	std::string file_name;

	char block_no[10];
	char int_string[3];

	int rows;
	int cols;

	sprite new_sprite_block;
	static std::vector <sprite> list_sprite_blocks;

	int i, j, k;

};

#endif /* SPRITES_H_ */
