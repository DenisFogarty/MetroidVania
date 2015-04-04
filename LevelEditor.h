/*
 * leveleditor.h
 *
 *  Created on: 12 Mar 2015
 *      Author: denis2
 */

#ifndef LEVELEDITOR_H_
#define LEVELEDITOR_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <vector>
#include <list>
#include <string>

#include "Sprites.h"
#include "Display.h"
#include "KeyboardInput.h"

class sprite_info {
public:
	ALLEGRO_BITMAP *sprite_bitmap;
	float x, y;
	std::string sheet_name;
	int sprite_pos_list;
};

class LevelEditor {
public:
	LevelEditor();

	void draw_windows(Display *display);

	void load_tile_tab(uint tab);
	void load_tile_page(uint page);

	void mouse_click(std::string button);
	void mouse_release(std::string button);

	void key_pressed(ALLEGRO_EVENT *event);
	void key_pressed_main(ALLEGRO_EVENT *event);
	void key_pressed_tile(ALLEGRO_EVENT *event);
	void key_released(ALLEGRO_EVENT *event);

	void set_mouse_pos_pointers(float *mouse_x, float *mouse_y);

	virtual ~LevelEditor();

private:
	ALLEGRO_BITMAP	*window_main;
	ALLEGRO_BITMAP	*window_main_background;

	ALLEGRO_BITMAP	*window_main_menu;
	ALLEGRO_BITMAP	*window_tiles;
	ALLEGRO_BITMAP	*window_tile_editor;
	ALLEGRO_BITMAP	*window_tile_menu;

	ALLEGRO_BITMAP	*level_name_bitmap;
	ALLEGRO_BITMAP	*sprite_name_bitmap;

	ALLEGRO_FONT	*font;

	/*
	 * Used to point to bitmaps
	 */
	ALLEGRO_BITMAP *curr_bitmap;

	bool sprite_held;

	float *mouse_x, *mouse_y;

	float x_offset, y_offset;

	std::map <std::string, std::vector<sprite>>* sprite_list_curr;
	std::vector <std::string> *sprite_sheet_names;

	sprite_info temp_sprite_info;
	std::list<sprite_info> sprite_list_main_window;
//	std::vector<sprite_info> sprite_list_main_window;
	std::list<sprite_info> sprite_list_editor_window;
	std::list<sprite_info>::iterator sprite_list_iterator;
//	std::vector <std::string> sprite_list_main_window_names;

	std::vector <sprite> sprite_list_tile_editor;

	uint tabs;
	uint pages;

	uint current_tab;
	uint current_page;

	char current_layer[5];

	char level_name[20];
	char sprite_name[20];
	int text_char_pos;
	bool enter_name_text;
	bool enter_sprite_name_text;

	void draw_main_menu_options();
	void draw_tile_menu_options();

	void tile_window_clicked();
	void main_window_released();
	void main_window_clicked();
	void tile_editor_released();
	void tile_editor_clicked();
	void main_menu_clicked();
	void tile_menu_clicked();

	void save_level();
	void load_level();
	void exit_editor();

	void change_tab();
	bool change_tab_open;
	void change_page();
	bool change_page_open;
	void save_custom_sprite();

	KeyboardInput keyboard;

};

#endif /* LEVELEDITOR_H_ */
