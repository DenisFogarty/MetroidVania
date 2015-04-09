/*
 * collision.h
 *
 *  Created on: 23 Feb 2015
 *      Author: denis2
 */

#ifndef COLLISION_H_
#define COLLISION_H_

#include <iostream>

#include "Items.h"
#include "Level.h"

class collision {
public:
	collision();

	bool detect_rotated_collision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	bool detect_collision(float x, float y, float width, float height, float item_x, float item_y, float item_width, float item_height);

	float get_item_x();
	float get_item_y();
	float get_item_width();
	float get_item_height();

	void set_sprite_list(std::vector <load_sprite_info> *sprite_list);

	virtual ~collision();

private:
	uint i;

	std::vector<load_sprite_info> *p_sprites;	//Points to all sprites drawn in the level

	load_sprite_info *current_item;
};

#endif /* COLLISION_H_ */
