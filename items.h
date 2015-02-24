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
	friend class collision;
public:
	items_data();

	void add_items(float x, float y, float angle);
	void draw_items();

	~items_data();

private:
	static std::vector <item> items;
	int num_items;
	item new_item;
	item current_item;
};

#endif /* ITEMS_H_ */
