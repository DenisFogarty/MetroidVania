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

class items {
public:
	items();

	float x1, y1, x2, y2;
	float damage;
	float angle;

	void add_item_coords(float x, float y, float angle = 0);

	virtual ~items();

private:


};

#endif /* ITEMS_H_ */
