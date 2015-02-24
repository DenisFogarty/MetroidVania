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


std::vector<item> items_data::items;


items_data::items_data() {
	num_items = 0;
}


void items_data::add_items(float x, float y, float angle) {
	new_item.x = x;
	new_item.y = y;

	new_item.item_sprite = al_load_bitmap("sprites/box.png");

	new_item.width = al_get_bitmap_width(new_item.item_sprite);
	new_item.height = al_get_bitmap_height(new_item.item_sprite);

	items.push_back(new_item);
	num_items++;
}


void items_data::draw_items() {
	for (int i = 0; i < num_items; i++) {
		current_item = items[i];
		al_draw_bitmap(current_item.item_sprite, current_item.x, current_item.y, 0);
	}
}


item::~item() {

}


items_data::~items_data() {

}
