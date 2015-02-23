/*
 * items.h
 *
 *  Created on: 13 Feb 2015
 *      Author: denis2
 */

#ifndef ITEMS_H_
#define ITEMS_H_

#include <iostream>
#include <vector>
#include <allegro5/allegro.h>

class item {
public:
	item();

	float x, y;
	float width, height;
	float damage;
	float angle;

	ALLEGRO_BITMAP *item_sprite;

	virtual ~item();

private:


};


class items_data {
public:
	items_data();

	void add_items(float x, float y, float angle);
	item new_item;

	~items_data();

private:
	std::vector <item> items;
};

#endif /* ITEMS_H_ */
