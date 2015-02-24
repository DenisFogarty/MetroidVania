/*
 * collision.cpp
 *
 *  Created on: 23 Feb 2015
 *      Author: denis2
 */

#include "collision.h"

collision::collision() {
	i = 0;

	p_items = &items_data::items;
}


bool collision::detect_collision(float x, float y, float width, float height, float angle) {

	for(i = 0; i < p_items->size(); i++) {
		current_item = (*p_items)[i];
		if((x + width) >= current_item.x &&
				(y + height) >= current_item.y &&
				x <= (current_item.x + current_item.width) &&
				y <= (current_item.y + current_item.height)) {

			return true;

		}
	}
	return false;
}


collision::~collision() {
	// TODO Auto-generated destructor stub
}
