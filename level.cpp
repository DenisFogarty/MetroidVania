/*
 * level.cpp
 *
 *  Created on: 10 Mar 2015
 *      Author: denis2
 */

#include "level.h"

level::level() {

}

void level::load_sprites() {
	sprite_list_curr = sprites::get_sprite_list();

	al_draw_bitmap(sprite_list_curr->at(0).at(0).item_sprite, 0, 1020, 0);
}

void level::draw_sprites(int i) {
	al_draw_bitmap(sprite_list_curr->at(0).at(i).item_sprite, 100, 900, 0);
}

level::~level() {
	// TODO Auto-generated destructor stub
}
