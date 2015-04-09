/*
 * collision.cpp
 *
 *  Created on: 23 Feb 2015
 *      Author: denis2
 */

#include "Collision.h"

collision::collision() {
	i = 0;
}


void collision::set_sprite_list(std::vector <load_sprite_info> *sprite_list) {
	p_sprites = sprite_list;
}


bool collision::detect_rotated_collision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

	/*
	 * Checks all four point of the bullet and determines if any of them are hitting any item
	 * This only checks the 4 points of a box, so anything hitting the bullet from the side will not be detected
	 */
	for(i = 0; i < p_sprites->size(); i++) {

		current_item = &(*p_sprites)[i];

		if((x1 >= current_item->x &&
				y1 >= current_item->y &&
				x1 <= (current_item->x + current_item->width) &&
				y1 <= (current_item->y + current_item->height))
				||
				(x2 >= current_item->x &&
						y2 >= current_item->y &&
						x2 <= (current_item->x + current_item->width) &&
						y2 <= (current_item->y + current_item->height))
						||
						(x3 >= current_item->x &&
								y3 >= current_item->y &&
								x3 <= (current_item->x + current_item->width) &&
								y3 <= (current_item->y + current_item->height))
								||
								(x4 >= current_item->x &&
										y4 >= current_item->y &&
										x4 <= (current_item->x + current_item->width) &&
										y4 <= (current_item->y + current_item->height))) {

			return true;

		}
	}

	return false;
}


bool collision::detect_collision(float x, float y, float width, float height, float item_x, float item_y, float item_width, float item_height) {

	if(x + width >= item_x &&
			y + height >= item_y &&
			x <= item_x + item_width &&
			y <= item_y + item_height) {

		return true;

	}

	return false;
}


float collision::get_item_x() {
	return current_item->x;
}

float collision::get_item_y() {
	return current_item->y;
}

float collision::get_item_width() {
	return current_item->width;
}

float collision::get_item_height() {
	return current_item->height;
}


collision::~collision() {

}
