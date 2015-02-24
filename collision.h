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

	bool detect_collision(float x, float y, float width, float height, float angle);

	virtual ~collision();

private:
	uint i;

	std::vector<item>* p_items;

	item current_item;
};

#endif /* COLLISION_H_ */
