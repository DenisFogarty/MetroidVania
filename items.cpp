/*
 * items.cpp
 *
 *  Created on: 13 Feb 2015
 *      Author: denis2
 */

#include "items.h"

item::item() {
	x = 0;
	y = 0;

	width = 0;
	height = 0;

	damage = 0;

	angle = 0;

	item_sprite = NULL;
}


items_data::items_data() {
	items = std::vector<item>();
}


void items_data::add_items(float x, float y, float angle) {
	new_item.x = 50;
	new_item.y = 50;

	new_item.item_sprite = al_load_bitmap("sprites/box.png");
}


item::~item() {

}


items_data::~items_data() {

}
