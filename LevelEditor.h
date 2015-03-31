/*
 * leveleditor.h
 *
 *  Created on: 12 Mar 2015
 *      Author: denis2
 */

#ifndef LEVELEDITOR_H_
#define LEVELEDITOR_H_

#include "Sprites.h"
#include "Display.h"

class LevelEditor {
public:
	LevelEditor();

	void draw_windows(Display *display);
	void select_tile_tab(uint tab);
	void load_tile_page(uint page);
	void mouse_click(uint x, uint y);

	virtual ~LevelEditor();

private:
	ALLEGRO_BITMAP *window_main;
	bool display_foreground;
	ALLEGRO_BITMAP *window_main_background;
	bool display_background;
	ALLEGRO_BITMAP *window_main_menu;
	ALLEGRO_BITMAP *window_tiles;
	ALLEGRO_BITMAP *window_tile_editor;
	ALLEGRO_BITMAP *window_tile_menu;

	/*
	 * Used to point to bitmaps
	 */
	ALLEGRO_BITMAP *curr_bitmap;

//	ALLEGRO_BITMAP* sprite_sheet;

	std::map <std::string, std::vector<sprite>>* sprite_list_curr;
	std::vector <std::string> *sprite_sheet_names;

	uint tabs;
	uint pages;

	uint current_tab;
	uint current_page;
};

#endif /* LEVELEDITOR_H_ */
