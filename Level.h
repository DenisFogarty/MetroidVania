/*
 * level.h
 *
 *  Created on: 10 Mar 2015
 *      Author: denis2
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "Sprites.h"

class load_sprite_info {
public:
	ALLEGRO_BITMAP *sprite_bitmap;
	float x, y;
	std::string sheet_name;
	int sprite_pos_list;
	std::string layer;
};

class load_level {
public:
	float exit_x1, exit_y1, exit_x2, exit_y2;

};

class level {
public:
	level();

	void load_sprites();
	void draw_sprites(int i);

	virtual ~level();

private:
	std::vector<sprite> sprite_list_curr;
};

#endif /* LEVEL_H_ */
