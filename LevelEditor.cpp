/*
 * leveleditor.cpp
 *
 *  Created on: 12 Mar 2015
 *      Author: denis2
 */

#include "LevelEditor.h"

LevelEditor::LevelEditor() {

	window_main = al_create_bitmap(900, 900);
	window_main_background = al_create_bitmap(900, 900);
	window_main_menu = al_create_bitmap(300, 900);
	window_tiles = al_create_bitmap(400, 500);
	window_tile_editor = al_create_bitmap(400, 300);
	window_tile_menu = al_create_bitmap(400, 100);
	level_name_bitmap = al_create_bitmap(250, 50);
	sprite_name_bitmap = al_create_bitmap(180, 25);

	al_set_target_bitmap(window_main);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(window_tiles);
	al_clear_to_color(al_map_rgb(100, 100, 100));

	al_set_target_bitmap(window_main_menu);
	al_clear_to_color(al_map_rgb(200, 200, 200));

	al_set_target_bitmap(window_tile_editor);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(window_tile_menu);
	al_clear_to_color(al_map_rgb(200, 200, 200));

	al_set_target_bitmap(level_name_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(sprite_name_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	sprite_held = false;

	sprite_list_curr = sprites::get_sprite_list();
	sprite_sheet_names = sprites::get_sprite_list_names();

	current_tab = 0;
	current_page = 0;

	load_tile_tab(0);
	load_tile_page(0);

	current_layer[0] = 'F';
	current_layer[1] = 'o';
	current_layer[2] = 'r';
	current_layer[3] = 'e';
	current_layer[4] = '\0';

	level_name[0] = '\0';
	sprite_name[0] = '\0';
	text_char_pos = 0;
	enter_name_text = false;
	enter_sprite_name_text = false;
	font = al_load_font("fonts/LiberationSerif-Regular.ttf", 20, 0);

	change_tab_open = false;
	change_page_open = false;
}


void LevelEditor::set_mouse_pos_pointers(float *mouse_x, float *mouse_y) {
	this->mouse_x = mouse_x, this->mouse_y = mouse_y;
}


void LevelEditor::load_tile_tab(uint tab) {
	if(tab < sprite_sheet_names->size()) {

		current_tab = tab;
		current_page = 0;
		pages = ((*sprite_list_curr)[(*sprite_sheet_names).at(tab)].size())/20;
		if(((*sprite_list_curr)[sprite_sheet_names->at(tab)].size()) % 20 > 0) {
			pages++;
		}

	} else {
		std::cout << "Tab does not exist" << std::endl;
	}
}


void LevelEditor::load_tile_page(uint page) {
	if(page < pages) {

		current_page = page;

		al_set_target_bitmap(window_tiles);
		al_clear_to_color(al_map_rgb(100, 100, 100));

		uint current_sprite = page * 20;

		uint i = 0;
		/*
		 * x and y used to determine the tile each bitmap is to be drawn in
		 */
		uint x = 0, y = 0;

		float width = 0, height = 0;
		float width_scale = 0, height_scale = 0;

		bool scale = false;

		/*
		 * Loop for drawing sprites to tile window
		 */
		while(current_sprite < (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].size() && i < 20) {
			curr_bitmap = (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].at(current_sprite).item_sprite;

			width = al_get_bitmap_width(curr_bitmap);
			height = al_get_bitmap_height(curr_bitmap);
			if(width >= 100.0 || height >= 100.0) {
				width_scale = width/100.0;
				height_scale = height/100.0;
				scale = true;
			}

			if(scale) {
				if(al_get_bitmap_width(curr_bitmap) > al_get_bitmap_height(curr_bitmap)) {
					al_draw_scaled_bitmap(curr_bitmap, 0, 0, width, height, 0, (y / 4)  * 100 + (50 - ((height / width_scale) / 2)), 100, height / width_scale, 0);
				} else {
					al_draw_scaled_bitmap(curr_bitmap, 0, 0, width, height, (y / 4)  * 100 + (50 - ((width / height_scale) / 2)), 0, 100, width / height_scale, 0);
				}
			} else {
				al_draw_bitmap(curr_bitmap, (x % 4) * 100 + (50 - (width / 2)), (y / 4)  * 100 + (50 - (height / 2)), 0);
			}

			scale = false;

			i++;
			x++;
			y++;
			current_sprite++;
		}
	} else {
		std::cout << "Page does not exist" << std::endl;
	}
}


void LevelEditor::mouse_click(std::string button) {
	if(button == "left") {
		if(*mouse_x > 1200 && *mouse_y > 100 && *mouse_y < 600) {
			x_offset = 1200;
			y_offset = 100;
			tile_window_clicked();

			enter_name_text = false;
			enter_sprite_name_text = false;
		}
		else if(*mouse_x > 1200 && *mouse_y > 600) {
			al_set_target_bitmap(window_tile_editor);
			x_offset = 1200;
			y_offset = 600;
			tile_editor_clicked();

			enter_name_text = false;
			enter_sprite_name_text = false;
		}
		else if(*mouse_x > 1200 && *mouse_y < 100) {
			x_offset = 1200;
			y_offset = 0;
			tile_menu_clicked();

			enter_name_text = false;
		}
		else if(*mouse_x > 300 && *mouse_x < 1200) {
			al_set_target_bitmap(window_main);
			x_offset = 300;
			y_offset = 0;
			main_window_clicked();

			enter_name_text = false;
			enter_sprite_name_text = false;
		}
		else if(*mouse_x < 300) {
			x_offset = 0;
			y_offset = 0;
			main_menu_clicked();

			enter_sprite_name_text = false;
		}
	}
}

void LevelEditor::mouse_release(std::string button) {

	if(button == "left") {
		if(*mouse_x > 1200 && *mouse_y > 600) {
			al_set_target_bitmap(window_tile_editor);
			x_offset = 1200;
			y_offset = 600;
			tile_editor_released();
		}
		else if(*mouse_x > 300 && *mouse_x < 1200) {
			al_set_target_bitmap(window_main);
			x_offset = 300;
			y_offset = 0;
			main_window_released();
		}
		sprite_held = false;
	}
}


void LevelEditor::tile_window_clicked() {
	/*
	 * Gets the position of the chosen sprite based on where the user clicks
	 */
	int sprite_number = ((int) ((*mouse_x - x_offset) / 100) + ((int) ((*mouse_y - y_offset) / 100) * 4) + (20 * (current_page)));

	curr_bitmap = (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].at(sprite_number).item_sprite;

	sprite_held = true;
}


void LevelEditor::main_window_released() {
	if(sprite_held) {
		temp_sprite_info.sheet_name = sprite_sheet_names->at(current_tab);
		temp_sprite_info.x = *mouse_x - x_offset - al_get_bitmap_width(curr_bitmap) / 2;
		temp_sprite_info.y = *mouse_y - y_offset - al_get_bitmap_height(curr_bitmap) / 2;
		temp_sprite_info.sprite_bitmap = curr_bitmap;

		al_set_target_bitmap(window_main);
		al_draw_bitmap(curr_bitmap, temp_sprite_info.x, temp_sprite_info.y, 0);
		sprite_list_main_window.push_back(temp_sprite_info);
	}
}


void LevelEditor::main_window_clicked() {
	uint width, height;
	uint x, y;
	sprite_list_iterator = sprite_list_main_window.begin();

	for(uint i = 0; i < sprite_list_main_window.size(); i++) {
		width = al_get_bitmap_width(sprite_list_iterator->sprite_bitmap);
		height = al_get_bitmap_height(sprite_list_iterator->sprite_bitmap);
		x = sprite_list_iterator->x;
		y = sprite_list_iterator->y;

		if(*mouse_x - x_offset > x && *mouse_x - x_offset < x + width && *mouse_y - y_offset > y && *mouse_y - y_offset < y + height) {
			curr_bitmap = sprite_list_iterator->sprite_bitmap;
			sprite_list_main_window.erase(sprite_list_iterator);
			al_set_target_bitmap(window_main);
			al_clear_to_color(al_map_rgb(255, 255, 255));
			sprite_list_iterator = sprite_list_main_window.begin();
			for(uint i = 0; i < sprite_list_main_window.size(); i++) {
				al_draw_bitmap(sprite_list_iterator->sprite_bitmap, sprite_list_iterator->x, sprite_list_iterator->y, 0);
				sprite_list_iterator++;
			}
			sprite_held = true;
			break;
		}
		sprite_list_iterator++;
	}
}


void LevelEditor::tile_editor_clicked() {
	uint width, height;
	uint x, y;
	sprite_list_iterator = sprite_list_editor_window.begin();

	for(uint i = 0; i < sprite_list_editor_window.size(); i++) {
		width = al_get_bitmap_width(sprite_list_iterator->sprite_bitmap);
		height = al_get_bitmap_height(sprite_list_iterator->sprite_bitmap);
		x = sprite_list_iterator->x;
		y = sprite_list_iterator->y;

		if(*mouse_x - x_offset > x && *mouse_x - x_offset < x + width && *mouse_y - y_offset > y && *mouse_y - y_offset < y + height) {
			curr_bitmap = sprite_list_iterator->sprite_bitmap;
			sprite_list_editor_window.erase(sprite_list_iterator);
			al_set_target_bitmap(window_tile_editor);
			al_clear_to_color(al_map_rgb(255, 255, 255));
			sprite_list_iterator = sprite_list_editor_window.begin();
			for(uint i = 0; i < sprite_list_editor_window.size(); i++) {
				al_draw_bitmap(sprite_list_iterator->sprite_bitmap, sprite_list_iterator->x, sprite_list_iterator->y, 0);
				sprite_list_iterator++;
			}
			sprite_held = true;
			break;
		}
		sprite_list_iterator++;
	}
}


void LevelEditor::tile_editor_released() {
	if(sprite_held) {
		temp_sprite_info.sheet_name = sprite_sheet_names->at(current_tab);
		temp_sprite_info.x = *mouse_x - x_offset - al_get_bitmap_width(curr_bitmap) / 2;
		temp_sprite_info.y = *mouse_y - y_offset - al_get_bitmap_height(curr_bitmap) / 2;
		temp_sprite_info.sprite_bitmap = curr_bitmap;

		al_set_target_bitmap(window_tile_editor);
		al_draw_bitmap(curr_bitmap, temp_sprite_info.x, temp_sprite_info.y, 0);
		sprite_list_editor_window.push_back(temp_sprite_info);
	}
}


void LevelEditor::main_menu_clicked() {
	if(*mouse_y > 100 && *mouse_y < 150 && *mouse_x > 25 && *mouse_x < 275) {
		enter_name_text = true;
		enter_sprite_name_text = false;
	}
	else {
		enter_name_text = false;
	}
}


void LevelEditor::tile_menu_clicked() {
	if(*mouse_x > 1400 && *mouse_x < 1580 && *mouse_y > 50 && *mouse_y < 75) {
		enter_sprite_name_text = true;
		enter_name_text = false;
	}
	else {
		enter_sprite_name_text = false;
	}
}


void LevelEditor::key_pressed(ALLEGRO_EVENT *event) {
	if(enter_name_text) {
		key_pressed_main(event);
	}
	else if(enter_sprite_name_text) {
		key_pressed_tile(event);
	}
}


void LevelEditor::key_pressed_main(ALLEGRO_EVENT *event) {
	if(enter_name_text) {
		text_char_pos = strlen(level_name);

		if(event->keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
			if(level_name[0] != '\0') {
				level_name[text_char_pos - 1] = '\0';
			}
		}
		else if(event->keyboard.keycode == ALLEGRO_KEY_LSHIFT || event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) {
			keyboard.change_case("upper");
		}
		else if(text_char_pos < 19){
			level_name[text_char_pos] = keyboard.keyboard(event);
			level_name[text_char_pos + 1] = '\0';
		}
	}
}

void LevelEditor::key_pressed_tile(ALLEGRO_EVENT *event) {
	if(enter_sprite_name_text) {
		text_char_pos = strlen(sprite_name);

		if(event->keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
			if(sprite_name[0] != '\0') {
				sprite_name[text_char_pos - 1] = '\0';
			}
		}
		else if(event->keyboard.keycode == ALLEGRO_KEY_LSHIFT || event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) {
			keyboard.change_case("upper");
		}
		else if(text_char_pos < 19){
			sprite_name[text_char_pos] = keyboard.keyboard(event);
			sprite_name[text_char_pos + 1] = '\0';
		}
	}
}

void LevelEditor::key_released(ALLEGRO_EVENT *event) {
	if(event->keyboard.keycode == ALLEGRO_KEY_LSHIFT || event->keyboard.keycode == ALLEGRO_KEY_RSHIFT) {
		keyboard.change_case("lower");
	}
}


void LevelEditor::draw_windows(Display *display) {
	display->draw_bitmap(window_main_background, 300, 0);
	display->draw_bitmap(window_main, 300, 0);
	display->draw_bitmap(window_main_menu, 0, 0);
	display->draw_bitmap(window_tiles, 1200, 100);
	display->draw_bitmap(window_tile_editor, 1200, 600);
	display->draw_bitmap(window_tile_menu, 1200, 0);
	display->draw_bitmap(level_name_bitmap, 25, 100);
	if(sprite_held) {
		display->draw_bitmap(curr_bitmap, *mouse_x - (al_get_bitmap_width(curr_bitmap) / 2), *mouse_y - (al_get_bitmap_height(curr_bitmap) / 2));
	}

	display->draw_text("Level name", 30, 75);
	display->draw_text(level_name, 25, 125);
	display->draw_text("Layer", 30, 200);
	display->draw_text(current_layer, 200, 200);
	display->draw_text("Save", 30, 275);
	display->draw_text("Load", 30, 350);
	display->draw_text("Exit", 30, 425);

	display->draw_text("Tab", 1250, 25);
	display->draw_text(std::to_string(current_tab + 1), 1250, 50);
	display->draw_text("Page", 1350, 25);
	display->draw_text(std::to_string(current_page + 1), 1350, 50);
	display->draw_text("Save", 1450, 25);
	display->draw_bitmap(sprite_name_bitmap, 1400, 50);
	display->draw_text(sprite_name, 1400, 55);

}


LevelEditor::~LevelEditor() {
	al_destroy_bitmap(window_main);
	al_destroy_bitmap(window_main_menu);
	al_destroy_bitmap(window_tiles);
	al_destroy_bitmap(window_tile_menu);
	al_destroy_bitmap(window_tile_editor);
	al_shutdown_font_addon();
}
