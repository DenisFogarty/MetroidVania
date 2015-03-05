/*
 * collision.h
 *
 *  Created on: 23 Feb 2015
 *      Author: denis2
 */

#ifndef COLLISION_H_
#define COLLISION_H_

#include <iostream>

#include "items.h"

class collision {
public:
	collision();

	bool detect_collision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	bool detect_collision(float x, float y, float width, float height);

	bool detect_left_collision(float x, float y, float width, float height);
	bool detect_right_collision(float x, float y, float width, float height);
	bool detect_ground_collision(float x, float y, float width, float height);
	bool detect_roof_collision(float x, float y, float width, float height);

	float get_item_x();
	float get_item_y();
	float get_item_width();
	float get_item_height();

	virtual ~collision();

private:
	uint i;

	std::vector<item>* p_items;

	item current_item;
};

#endif /* COLLISION_H_ */
