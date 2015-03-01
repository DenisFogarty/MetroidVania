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


bool collision::detect_collision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float width, float height, float angle) {

	/*
	 * Checks all four point of the bullet and determines if any of them are hitting any item
	 * This only checks the 4 points of a box, so anything hitting the bullet from the side will not be detected
	 * This shouldn't be an issue, and greatly reduces the computation needed
	 */
	for(i = 0; i < p_items->size(); i++) {
		current_item = (*p_items)[i];
		if((x1 >= current_item.x &&
				y1 >= current_item.y &&
				x1 <= (current_item.x + current_item.width) &&
				y1 <= (current_item.y + current_item.height))
				||
				(x2 >= current_item.x &&
						y2 >= current_item.y &&
						x2 <= (current_item.x + current_item.width) &&
						y2 <= (current_item.y + current_item.height))
						||
						(x3 >= current_item.x &&
								y3 >= current_item.y &&
								x3 <= (current_item.x + current_item.width) &&
								y3 <= (current_item.y + current_item.height))
								||
								(x4 >= current_item.x &&
										y4 >= current_item.y &&
										x4 <= (current_item.x + current_item.width) &&
										y4 <= (current_item.y + current_item.height))) {

			return true;

		}
	}

	return false;
}


collision::~collision() {
	// TODO Auto-generated destructor stub
}
