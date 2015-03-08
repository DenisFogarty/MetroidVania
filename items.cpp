/*
 * items.cpp
 *
 *  Created on: 13 Feb 2015
 *      Author: denis2
 */

#include "items.h"

std::vector<item> items_data::items;

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
	num_items = 0;
}


void items_data::add_items(float x, float y, float angle) {
	new_item.x = x;
	new_item.y = y;

	new_item.item_sprite = al_load_bitmap("sprites/blocks.png");

	new_item.width = 16;
	new_item.height = 16;

	items.push_back(new_item);
	num_items++;
}


std::vector<item>* items_data::get_item_vector() {
	return &items;
}


void items_data::draw_items() {
	for (int i = 0; i < num_items; i++) {
		current_item = items[i];
		al_draw_bitmap_region(current_item.item_sprite, 8, 8, 16, 16, current_item.x, current_item.y, 0);
	}
}


item::~item() {

}


items_data::~items_data() {

}
