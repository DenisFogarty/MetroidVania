/*
 * level.h
 *
 *  Created on: 10 Mar 2015
 *      Author: denis2
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "sprites.h"

class level {
public:
	level();

	void load_sprites();
	void draw_sprites(int i);

	virtual ~level();

private:
	std::vector<std::vector<sprite>>* sprite_list_curr;

	ALLEGRO_BITMAP* sprite_sheet_list_curr;
};

#endif /* LEVEL_H_ */
