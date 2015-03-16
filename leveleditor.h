/*
 * leveleditor.h
 *
 *  Created on: 12 Mar 2015
 *      Author: denis2
 */

#ifndef LEVELEDITOR_H_
#define LEVELEDITOR_H_

#include "sprites.h"

class leveleditor {
public:
	leveleditor();

	void draw_windows();

	virtual ~leveleditor();

private:
	ALLEGRO_BITMAP *window_main;
	ALLEGRO_BITMAP *window_tiles;
	ALLEGRO_BITMAP *window_tile_editor;

	std::vector<std::vector<sprite>>* sprite_list_curr;
	ALLEGRO_BITMAP* sprite_sheet;
};

#endif /* LEVELEDITOR_H_ */
