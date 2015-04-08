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
	level_width_and_height = al_create_bitmap(200, 25);
	exit_level_bitmap = al_create_bitmap(200, 25);
	exit_coords_bitmap = al_create_bitmap(40, 25);

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

	al_set_target_bitmap(level_width_and_height);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(exit_level_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(exit_coords_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	sprite_held = false;

	held_sprite_height = 0;
	held_sprite_width = 0;

	sprite_list_curr = sprites::get_sprite_list();
	sprite_sheet_names = sprites::get_sprite_list_names();

	current_tab = 0;
	current_page = 0;

	level_width = 1600;
	level_height = 900;

	change_tab_bitmap = al_create_bitmap(400, 25 * sprite_sheet_names->size());
	change_page_bitmap = al_create_bitmap(400, 25 * (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].size() / 20);

	al_set_target_bitmap(change_tab_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(change_page_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	sprite_list_main_window = &sprite_list_main_window_foreground;

	x_offset = 0;
	y_offset = 0;

	sprite_offset_x = 0;
	sprite_offset_y = 0;

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

	enter_exit_level = false;
	enter_exit_x = false;
	enter_exit_y = false;

	move_main = false;
	window_x = 300, window_y = 0;

	enter_level_width = false;
	enter_level_height = false;
	next_char_pos = 0;

	if(!al_init_image_addon()) {
		fprintf(stderr, "Failed to initialise image addon");
	}
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
		tabs = sprite_sheet_names->size();

	} else {
		std::cout << "Tab does not exist" << std::endl;
	}
	load_tile_page(0);
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

		/*
		 * If image is larger than 100 * 100, this bool will be set to true
		 * The image will then be resized to fit the window
		 */
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
				al_draw_scaled_bitmap(curr_bitmap, 0, 0, width, height, (i%4) * 100, (i/4) * 100, 100, width / height_scale, 0);
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

			set_bools_to_false();
		}
		else if(*mouse_x > 1200 && *mouse_y > 600) {
			al_set_target_bitmap(window_tile_editor);
			x_offset = 1200;
			y_offset = 600;
			tile_editor_clicked();

			set_bools_to_false();
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

			set_bools_to_false();
		}
		else if(*mouse_x < 300) {
			x_offset = 0;
			y_offset = 0;
			main_menu_clicked();

			enter_sprite_name_text = false;
			change_tab_open = false;
			change_page_open = false;

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
	if(change_tab_open && *mouse_x > 1200 && *mouse_x < 1300) {
		current_tab = (int)((*mouse_y - 100) / 25);
		if(current_tab >= tabs) {
			current_tab = tabs - 1;
		}
		load_tile_tab(current_tab);
	}
	else if(change_page_open && *mouse_x > 1200 && *mouse_x < 1300) {
		current_page = (int)((*mouse_y - 100) / 25);
		if(current_page >= pages) {
			current_page = pages - 1;
		}
		load_tile_page(current_page);
	}
	else {
		sprite_number = ((int) ((*mouse_x - x_offset) / 100) + ((int) ((*mouse_y - y_offset) / 100) * 4) + (20 * (current_page)));

		curr_bitmap = (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].at(sprite_number).item_sprite;

		sprite_held = true;

		held_sprite_height = al_get_bitmap_height(curr_bitmap) / 2;
		held_sprite_width = al_get_bitmap_width(curr_bitmap) / 2;
	}
}


void LevelEditor::main_window_clicked() {
	uint width, height;
	int x, y;
	sprite_list_iterator = sprite_list_main_window->begin();
	move_main = true;

	for(uint i = 0; i < sprite_list_main_window->size(); i++) {
		width = al_get_bitmap_width(sprite_list_iterator->sprite_bitmap);
		height = al_get_bitmap_height(sprite_list_iterator->sprite_bitmap);
		x = sprite_list_iterator->x;
		y = sprite_list_iterator->y;

		if(*mouse_x - x_offset > x + sprite_offset_x &&
				*mouse_x - x_offset < x + width + sprite_offset_x &&
				*mouse_y - y_offset > y + sprite_offset_y &&
				*mouse_y - y_offset < y + height + sprite_offset_y) {

			curr_bitmap = sprite_list_iterator->sprite_bitmap;
			sprite_list_main_window->erase(sprite_list_iterator);

			draw_all_layers();

			sprite_held = true;
			move_main = false;

			held_sprite_width = al_get_bitmap_width(curr_bitmap) / 2;
			held_sprite_height = al_get_bitmap_height(curr_bitmap) / 2;

			break;
		}
		sprite_list_iterator++;
	}

	if(move_main) {
		orig_mouse_x = *mouse_x;
		orig_mouse_y = *mouse_y;
	}
}


/*
 * Draws sprite to main window
 */
void LevelEditor::main_window_released() {
	if(sprite_held) {
		temp_sprite_info.sheet_name = sprite_sheet_names->at(current_tab);
		temp_sprite_info.x = *mouse_x - x_offset - al_get_bitmap_width(curr_bitmap) / 2 - sprite_offset_x;
		if(temp_sprite_info.x < 0) {
			temp_sprite_info.x = 0;
		}
		temp_sprite_info.y = *mouse_y - y_offset - al_get_bitmap_height(curr_bitmap) / 2 - sprite_offset_y;
		if(temp_sprite_info.y < 0) {
			temp_sprite_info.y = 0;
		}
		temp_sprite_info.sprite_bitmap = curr_bitmap;
		temp_sprite_info.sprite_pos_list = sprite_number;

		al_set_target_bitmap(window_main);
		al_draw_bitmap(curr_bitmap, temp_sprite_info.x + sprite_offset_x, temp_sprite_info.y + sprite_offset_y, 0);
		sprite_list_main_window->push_back(temp_sprite_info);
	}
	else if(move_main) {
		sprite_offset_x += (window_x - 300.0);
		sprite_offset_y += window_y;

		sprite_list_iterator->x += sprite_offset_x;
		sprite_list_iterator->y += sprite_offset_y;

		draw_all_layers();

		window_x = 300;
		window_y = 0;

		move_main = false;
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

			sprite_held = true;

			al_set_target_bitmap(window_tile_editor);
			al_clear_to_color(al_map_rgb(255, 255, 255));
			sprite_list_iterator = sprite_list_editor_window.begin();
			for(uint i = 0; i < sprite_list_editor_window.size(); i++) {
				al_draw_bitmap(sprite_list_iterator->sprite_bitmap, sprite_list_iterator->x, sprite_list_iterator->y, 0);
			}

			draw_all_layers();

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
	else if(*mouse_x > 200 && *mouse_x < 250 && *mouse_y > 200 && *mouse_y < 225){
		if(strcmp(current_layer, "Fore") == 0) {
			current_layer[0] = 'B';
			current_layer[1] = 'a';
			current_layer[2] = 'c';
			current_layer[3] = 'k';
			current_layer[4] = '\0';
			sprite_list_main_window = &sprite_list_main_window_background;
		}
		else if(strcmp(current_layer, "Back") == 0) {
			current_layer[0] = 'F';
			current_layer[1] = 'r';
			current_layer[2] = 'o';
			current_layer[3] = 'n';
			current_layer[4] = 't';
			current_layer[5] = '\0';
			sprite_list_main_window = &sprite_list_main_window_front;
		}
		else {
			current_layer[0] = 'F';
			current_layer[1] = 'o';
			current_layer[2] = 'r';
			current_layer[3] = 'e';
			current_layer[4] = '\0';
			sprite_list_main_window = &sprite_list_main_window_foreground;
		}

		draw_all_layers();

		enter_name_text = false;
	}
	else if(*mouse_x > 30 && *mouse_x < 80 && *mouse_y > 275 && *mouse_y < 300) {
		save_level();
	}
	else if(*mouse_x > 30 && *mouse_x < 80 && *mouse_y > 425 && *mouse_y < 450) {
		level_width_string[0] = ' ';
		level_width_string[5] = ' ';

		level_height_string[0] = ' ';
		level_height_string[5] = ' ';

		new_level();
	}
	else if(*mouse_x > 30 && *mouse_x < 80 && *mouse_y > 500 && *mouse_y < 525) {

	}
	else if(*mouse_x > 30 && *mouse_x < 80 && *mouse_y > 575 && *mouse_y < 600) {

	}
	else if(*mouse_x > 30 && *mouse_x < 80 && *mouse_y > 650 && *mouse_y < 675) {

	}
	else if(*mouse_x > 30 && *mouse_x < 70 && *mouse_y > 725 && *mouse_y < 750) {

	}
	else if(*mouse_x > 80 && *mouse_x < 120 && *mouse_y > 725 && *mouse_y < 750) {
		save_level();
	}
	else {
		enter_name_text = false;
	}
}


void LevelEditor::tile_menu_clicked() {
	if(*mouse_x > 1400 && *mouse_x < 1580 && *mouse_y > 50 && *mouse_y < 75) {
		enter_sprite_name_text = true;
		change_tab_open = false;
		change_page_open = false;
	}
	else if(*mouse_x > 1450 && *mouse_x < 1550 && *mouse_y > 25 && *mouse_y < 50){
		save_custom_sprite();

		enter_sprite_name_text = false;
		change_tab_open = false;
		change_page_open = false;
	}
	else if(*mouse_x > 1350 && *mouse_x < 1390 && *mouse_y > 50 && *mouse_y < 75) {
		change_page();

		enter_sprite_name_text = false;
		change_tab_open = false;
	}
	else if(*mouse_x > 1200 && *mouse_x < 1300 && *mouse_y > 50 && *mouse_y < 75) {
		change_tab();

		enter_sprite_name_text = false;
		change_page_open = false;
	}
}


void LevelEditor::key_pressed(ALLEGRO_EVENT *event) {
	if(enter_name_text) {
		key_pressed_main(event);
	}

	else if(enter_sprite_name_text) {
		key_pressed_tile(event);
	}

	else if(enter_level_width || enter_level_height) {
		char next_number = keyboard.keyboard(event);
		if(enter_level_width) {
			if((next_number == '1' || next_number == '2' || next_number == '3' || next_number == '4' || next_number == '5' || next_number == '6' || next_number == '7' || next_number == '8' || next_number == '9' || next_number == '0')
					&& level_width_string[5] != '\0') {

				level_width_string[next_char_pos] = next_number;
				next_char_pos++;
				level_width_string[next_char_pos] = '\0';
			}
			else if(next_number == '<') {
				if(next_char_pos > 0) {
					next_char_pos--;
					level_width_string[next_char_pos] = '\0';
					level_width_string[5] = ' ';
				}
			}
			else if(next_number == '\n') {
				enter_level_width = false;
				next_char_pos = 0;
				level_width = atoi(level_width_string);
			}
		}

		else if(enter_level_height) {
			char next_number = keyboard.keyboard(event);
			if((next_number == '1' || next_number == '2' || next_number == '3' || next_number == '4' || next_number == '5' || next_number == '6' || next_number == '7' || next_number == '8' || next_number == '9' || next_number == '0')
					&& level_height_string[5] != '\0') {

				level_height_string[next_char_pos] = next_number;
				next_char_pos++;
				level_height_string[next_char_pos] = '\0';
			}
			else if(next_number == '<') {
				if(next_char_pos > 0) {
					next_char_pos--;
					level_height_string[next_char_pos] = '\0';
					level_height_string[5] = ' ';
				}
			}
			else if(next_number == '\n') {
				enter_level_height = false;
				level_height = atoi(level_width_string);
			}
		}
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


void LevelEditor::change_tab() {
	change_tab_open = true;
}

void LevelEditor::change_page() {
	change_page_open = true;
}


void LevelEditor::save_custom_sprite() {
	if(sprite_name[0] != '\0') {
		sprite_list_iterator = sprite_list_editor_window.begin();

		float min_x = 400, min_y = 400;
		float max_x = 0, max_y = 0;

		for(uint i = 0; i < sprite_list_editor_window.size(); i++) {
			if(sprite_list_iterator->x < min_x) {
				min_x = sprite_list_iterator->x;
			}
			if(sprite_list_iterator->x < min_y) {
				min_y = sprite_list_iterator->y;
			}
			if(sprite_list_iterator->x + al_get_bitmap_width(sprite_list_iterator->sprite_bitmap) - 1 > max_x) {
				max_x = sprite_list_iterator->x + al_get_bitmap_width(sprite_list_iterator->sprite_bitmap) - 1;
			}
			if(sprite_list_iterator->y + al_get_bitmap_height(sprite_list_iterator->sprite_bitmap) - 1 > max_y) {
				max_y = sprite_list_iterator->y + al_get_bitmap_height(sprite_list_iterator->sprite_bitmap) - 1;
			}
			sprite_list_iterator++;
		}

		custom_sprite = al_create_bitmap(400 - max_x + 1, 300 - max_y + 1);
		al_set_target_bitmap(custom_sprite);
		custom_sprite = al_create_sub_bitmap(window_tile_editor, min_x, min_y, max_x - min_x + 1, max_y - min_y + 1);
		al_convert_mask_to_alpha(custom_sprite, al_map_rgb(255, 255, 255));

		strcpy(full_sprite_name, sprite_name);
		strcat(full_sprite_name, ".png");

		char temp_file_name[36] = {'s', 'p', 'r', 'i', 't', 'e', 's', '_', 'c', 'u', 's', 't', 'o', 'm', '/', '\0'};
		strcat(temp_file_name, full_sprite_name);
		al_save_bitmap(temp_file_name, custom_sprite);

		config = al_load_config_file("sprite_custom_data/main.conf");

		const char *temp_custom_sprite_data = al_get_config_value(config, "", "sheets");

		strcpy(custom_sprite_data, temp_custom_sprite_data);

		strcat(custom_sprite_data, sprite_name);
	}
}


void LevelEditor::move_main_window() {
	if(move_main) {
		window_x = 300 + (*mouse_x - orig_mouse_x);
		window_y = *mouse_y - orig_mouse_y;

		if(sprite_offset_x + (window_x - 300) > 0 && *mouse_x > orig_mouse_x) {
			sprite_offset_x = 0;
			window_x = 300;
		}
		if(sprite_offset_y + window_y > 0 && *mouse_y > orig_mouse_y) {
			sprite_offset_y = 0;
			window_y = 0;
		}

		if (sprite_offset_x + (window_x - 300) < (-1 * (level_width - 900)) && *mouse_x < orig_mouse_x) {
			window_x = 300;
		}
		if(sprite_offset_y - window_y < (-1 * (level_height - 900)) && *mouse_y < orig_mouse_y) {
			window_y =  0;
		}
	}
}

/*
 * Draws all layers, then returns control to the layer currently selected
 */
void LevelEditor::draw_all_layers() {
	std::list <sprite_info> *temp_list_holder = sprite_list_main_window;

	al_set_target_bitmap(window_main);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	for(uint i = 0; i < 3; i++) {
		if(i == 0) {
			sprite_list_main_window = &sprite_list_main_window_background;
		}
		else if(i == 1) {
			sprite_list_main_window = &sprite_list_main_window_foreground;
		}
		else {
			sprite_list_main_window = &sprite_list_main_window_front;
		}

		sprite_list_iterator = sprite_list_main_window->begin();
		for(uint i = 0; i < sprite_list_main_window->size(); i++) {
			al_draw_bitmap(sprite_list_iterator->sprite_bitmap, sprite_list_iterator->x + sprite_offset_x, sprite_list_iterator->y + sprite_offset_y, 0);
			sprite_list_iterator++;
		}
	}

	sprite_list_main_window = temp_list_holder;
}


void LevelEditor::set_bools_to_false() {
	enter_name_text = false;
	enter_sprite_name_text = false;
	change_tab_open = false;
	change_page_open = false;
	enter_level_width = false;
	enter_level_height = false;
	enter_exit_level = false;
	enter_exit_x = false;
	enter_exit_y = false;
}


void LevelEditor::new_level() {
	enter_level_width = true;
	enter_level_height = true;

	/*
	 * Clears the main window
	 */
	sprite_list_main_window_background.clear();

	sprite_list_main_window_foreground.clear();

	sprite_list_main_window_front.clear();

	al_set_target_bitmap(window_main);
	al_clear_to_color(al_map_rgb(255, 255, 255));
}


void LevelEditor::save_level() {
	char full_level_name[50] = {'l', 'e', 'v', 'e', 'l', 's', '/'};

	int num_of_sprites = 0;

	char num_sprites_string[5];

	char temp_num[5];

	char section[10] = {'s', 'p', 'r', 'i', 't', 'e', '_'};

	if(level_name[0] != '\0') {
		std::list<sprite_info>::iterator temp_iterator;

		if(strcmp(current_layer, "Fore") == 0) {
			temp_iterator = sprite_list_main_window_foreground.begin();
		}
		if(strcmp(current_layer, "Back") == 0) {
			temp_iterator = sprite_list_main_window_background.begin();
		}
		if(strcmp(current_layer, "Front") == 0) {
			temp_iterator = sprite_list_main_window_front.begin();
		}

		num_of_sprites += sprite_list_main_window_background.size();
		num_of_sprites += sprite_list_main_window_foreground.size();
		num_of_sprites += sprite_list_main_window_front.size();

		sprintf(num_sprites_string,"%d",num_of_sprites);

		strcat(full_level_name, level_name);
		strcat(full_level_name, ".level");

		create_config = al_create_config();

		al_set_config_value(create_config, "", "sprites", num_sprites_string);
		al_set_config_value(create_config, "", "width", level_width_string);
		al_set_config_value(create_config, "", "height", level_height_string);

		uint loop = 0;

		sprite_list_iterator = sprite_list_main_window_background.begin();
		for(uint i = 1; i <= sprite_list_main_window_background.size(); i++) {
			loop++;
			sprintf(temp_num, "%d", loop);
			strcat(section, temp_num);
			al_add_config_section(create_config, section);

			char temp_sheet_name[sprite_list_iterator->sheet_name.size()];
			for(uint j = 0; j < sprite_list_iterator->sheet_name.size(); j++) {
				temp_sheet_name[j] = sprite_list_iterator->sheet_name[j];
				temp_sheet_name[j+1] = '\0';
			}

			al_set_config_value(create_config, section, "name", temp_sheet_name);

			sprintf(temp_num, "%d", sprite_list_iterator->sprite_pos_list);

			al_set_config_value(create_config, section, "num", temp_num);

			sprintf(temp_num, "%d", (int) sprite_list_iterator->x);

			al_set_config_value(create_config, section, "x", temp_num);

			sprintf(temp_num, "%d", (int) sprite_list_iterator->y);

			al_set_config_value(create_config, section, "y", temp_num);

			al_set_config_value(create_config, section, "layer", "back");

			al_set_config_value(create_config, section, "damage", "0");

			section[7] = '\0';
			sprite_list_iterator++;
		}

		sprite_list_iterator = sprite_list_main_window_foreground.begin();
		for(uint i = 1; i <= sprite_list_main_window_foreground.size(); i++) {
			loop++;
			sprintf(temp_num, "%d", loop);
			strcat(section, temp_num);
			al_add_config_section(create_config, section);

			char temp_sheet_name[sprite_list_iterator->sheet_name.size()];
			for(uint j = 0; j < sprite_list_iterator->sheet_name.size(); j++) {
				temp_sheet_name[j] = sprite_list_iterator->sheet_name[j];
				temp_sheet_name[j+1] = '\0';
			}

			al_set_config_value(create_config, section, "name", temp_sheet_name);

			sprintf(temp_num, "%d", sprite_list_iterator->sprite_pos_list);

			al_set_config_value(create_config, section, "num", temp_num);

			sprintf(temp_num, "%d", (int) sprite_list_iterator->x);

			al_set_config_value(create_config, section, "x", temp_num);

			sprintf(temp_num, "%d", (int) sprite_list_iterator->y);

			al_set_config_value(create_config, section, "y", temp_num);

			al_set_config_value(create_config, section, "layer", "fore");

			al_set_config_value(create_config, section, "damage", "0");

			section[7] = '\0';
			sprite_list_iterator++;
		}

		sprite_list_iterator = sprite_list_main_window_front.begin();
		for(uint i = 1; i <= sprite_list_main_window_front.size(); i++) {
			loop++;
			sprintf(temp_num, "%d", loop);
			strcat(section, temp_num);
			al_add_config_section(create_config, section);

			char temp_sheet_name[sprite_list_iterator->sheet_name.size()];
			for(uint j = 0; j < sprite_list_iterator->sheet_name.size(); j++) {
				temp_sheet_name[j] = sprite_list_iterator->sheet_name[j];
				temp_sheet_name[j+1] = '\0';
			}

			al_set_config_value(create_config, section, "name", temp_sheet_name);

			sprintf(temp_num, "%d", sprite_list_iterator->sprite_pos_list);

			al_set_config_value(create_config, section, "num", temp_num);

			sprintf(temp_num, "%d", (int) sprite_list_iterator->x);

			al_set_config_value(create_config, section, "x", temp_num);

			sprintf(temp_num, "%d", (int) sprite_list_iterator->y);

			al_set_config_value(create_config, section, "y", temp_num);

			al_set_config_value(create_config, section, "layer", "front");

			al_set_config_value(create_config, section, "damage", "0");

			section[7] = '\0';
			sprite_list_iterator++;
		}
		loop = 0;

		al_save_config_file(full_level_name, create_config);

		sprite_list_iterator = temp_iterator;
	}
}


void LevelEditor::load_level() {

}


void LevelEditor::draw_windows(Display *display) {
	display->draw_bitmap(window_main_background, window_x, window_y);
	display->draw_bitmap(window_main, window_x, window_y);
	display->draw_bitmap(window_main_menu, 0, 0);
	display->draw_bitmap(window_tiles, 1200, 100);
	display->draw_bitmap(window_tile_editor, 1200, 600);
	display->draw_bitmap(window_tile_menu, 1200, 0);
	display->draw_bitmap(level_name_bitmap, 25, 100);
	if(sprite_held && held_sprite_width < 200 && held_sprite_height < 200) {
		display->draw_bitmap(curr_bitmap, *mouse_x - held_sprite_width, *mouse_y - held_sprite_height);
	}

	display->draw_text("Level name", 30, 75);
	display->draw_text(level_name, 25, 125);
	display->draw_text("Layer", 30, 200);
	display->draw_text(current_layer, 200, 200);
	display->draw_text("Save", 30, 275);
	display->draw_text("Load", 30, 350);
	display->draw_text("New", 30, 425);
	display->draw_text("Set Exits", 30, 500);
	display->draw_text("Exits", 30, 575);
	display->draw_bitmap(exit_level_bitmap, 30, 650);
	display->draw_bitmap(exit_coords_bitmap, 30, 725);
	display->draw_bitmap(exit_coords_bitmap, 80, 725);
	display->draw_text("Exit", 30, 800);

	display->draw_text("Tab", 1200, 25);
	display->draw_text(sprite_sheet_names->at(current_tab), 1200, 50);
	display->draw_text("Page", 1350, 25);
	display->draw_text(std::to_string(current_page + 1), 1350, 50);
	display->draw_text("Save", 1450, 25);
	display->draw_bitmap(sprite_name_bitmap, 1400, 50);
	display->draw_text(sprite_name, 1400, 55);

	if(change_tab_open) {
		display->draw_bitmap(change_tab_bitmap, 1200, 100);
		for(uint i = 0; i < sprite_sheet_names->size(); i++) {
			display->draw_text(sprite_sheet_names->at(i), 1200, 100 + 25 * i);
		}
	}

	if(change_page_open) {
		display->draw_bitmap(change_page_bitmap, 1200, 100);
		for(uint i = 0; i < (*sprite_list_curr)[sprite_sheet_names->at(current_tab)].size() / 20 + 1; i++) {
			display->draw_text(std::to_string(i + 1), 1200, 100 + 25 * i);
		}
	}

	if(enter_level_width) {
		display->draw_text("Width", 600, 400);
		display->draw_bitmap(level_width_and_height, 600, 425);
		display->draw_text(level_width_string, 600, 425);
	}
	else if(enter_level_height) {
		display->draw_text("Height", 600, 400);
		display->draw_bitmap(level_width_and_height, 600, 425);
		display->draw_text(level_height_string, 600, 425);
	}
}


void LevelEditor::exit_editor() {
	sprite_list_main_window_background.clear();

	sprite_list_main_window_foreground.clear();

	sprite_list_main_window_front.clear();
}


LevelEditor::~LevelEditor() {
	al_destroy_bitmap(window_main);
	al_destroy_bitmap(window_main_menu);
	al_destroy_bitmap(window_tiles);
	al_destroy_bitmap(window_tile_menu);
	al_destroy_bitmap(window_tile_editor);
	al_destroy_bitmap(level_name_bitmap);
	al_destroy_bitmap(sprite_name_bitmap);
	al_destroy_bitmap(change_tab_bitmap);
	al_destroy_bitmap(change_page_bitmap);
	al_destroy_bitmap(level_width_and_height);
	al_destroy_bitmap(exit_level_bitmap);
	al_destroy_bitmap(exit_coords_bitmap);
	al_destroy_font(font);
	al_shutdown_font_addon();
}
