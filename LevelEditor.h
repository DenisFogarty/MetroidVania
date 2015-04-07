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
	std::string layer;
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

	void move_main_window();

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

	ALLEGRO_BITMAP	*change_tab_bitmap;
	ALLEGRO_BITMAP	*change_page_bitmap;

	ALLEGRO_FONT	*font;

	/*
	 * Used to point to bitmaps
	 */
	ALLEGRO_BITMAP	*curr_bitmap;

	/*
	 * Used for saving custom sprites
	 */
	ALLEGRO_BITMAP	*custom_sprite;

	ALLEGRO_BITMAP	*level_width_and_height;

	ALLEGRO_BITMAP	*exit_level_bitmap;
	ALLEGRO_BITMAP	*exit_coords_bitmap;

	ALLEGRO_CONFIG	*config;

	bool sprite_held;

	float held_sprite_width, held_sprite_height;

	float *mouse_x, *mouse_y;

	float x_offset, y_offset;

	float sprite_offset_x, sprite_offset_y;

	std::map <std::string, std::vector<sprite>>* sprite_list_curr;
	std::vector <std::string> *sprite_sheet_names;

	sprite_info temp_sprite_info;
	std::list<sprite_info> sprite_list_main_window_background;
	std::list<sprite_info> sprite_list_main_window_foreground;
	std::list<sprite_info> sprite_list_main_window_front;
	std::list<sprite_info> *sprite_list_main_window;

	std::list<sprite_info> sprite_list_editor_window;
	std::list<sprite_info>::iterator sprite_list_iterator;

	std::vector <sprite> sprite_list_tile_editor;

	uint tabs;
	uint pages;

	uint current_tab;
	uint current_page;

	char current_layer[6];

	char level_name[20];
	char full_level_name[24];
	char sprite_name[20];
	char full_sprite_name[24];
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
	void new_level();
	bool set_level_size();
	char level_width_string[6], level_height_string[6];
	int next_char_pos;
	float level_width, level_height;
	bool enter_level_width, enter_level_height;
	void set_exits();
	bool set_exit_coords();
	bool enter_exit_level, enter_exit_x, enter_exit_y;
	void exit_editor();

	void change_tab();
	bool change_tab_open;
	void change_page();
	bool change_page_open;
	void save_custom_sprite();

	char custom_sprite_data[10000];

	bool move_main;
	float orig_mouse_x, orig_mouse_y;
	float window_x, window_y;

	std::vector<std::vector<int>> exit_coords;	//x1, y1, x2, y2
	std::vector<std::string> exit_levels;
	std::vector<std::vector<int>> exit_to_coords;	//x1, y1, x2, y2

	void draw_all_layers();

	void set_bools_to_false();

	KeyboardInput keyboard;

};

#endif /* LEVELEDITOR_H_ */
