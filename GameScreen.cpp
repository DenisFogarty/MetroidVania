/*
 * GameScreen.cpp
 *
 *  Created on: 17 Mar 2015
 *      Author: denis2
 */

#include "GameScreen.h"

GameScreen::GameScreen() {
	/*
	 * The following creates the in-game cursor
	 */
	mouse_x = 0;
	mouse_y = 0;
	cursor_size = 16;
	cursor_middle = cursor_size/2;

	cursor_color_r = 255;
	cursor_color_g = 0;
	cursor_color_b = 0;

	cursor = al_create_bitmap(cursor_size, cursor_size);
	if(!cursor) {
		fprintf(stderr, "Failed to initialise the bitmap cursor/n");
	}

	al_set_target_bitmap(cursor);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(cursor, al_map_rgb(0, 0, 0));

	al_draw_circle(cursor_middle, cursor_middle, cursor_middle - 1, al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b), 2);

	al_draw_pixel(cursor_middle,	cursor_middle,		al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
	al_draw_pixel(cursor_middle-1,	cursor_middle,		al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
	al_draw_pixel(cursor_middle,	cursor_middle+1,	al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));
	al_draw_pixel(cursor_middle-1,	cursor_middle+1,	al_map_rgb(cursor_color_r, cursor_color_g, cursor_color_b));

	moving_left = false;
	moving_right = false;

	/*
	 * Loading sprites
	 */
	sprite_list_curr = sprites::get_sprite_list();
	sprite_list_names = sprites::get_sprite_list_names();

	config_main = al_load_config_file("levels/main.conf");

	level_names = al_get_config_value(config_main, "", "levels");

	/*
	 * This loop stores the individual level names in a vector of strings
	 */
	std::string temp_string;
	for(uint i = 0; i < level_names.size(); i++) {
		if(level_names[i] == ',') {
			level_names_split.push_back(temp_string);
			temp_string.clear();
		}
		else if(level_names[i] != ' ' && level_names[i] != ',') {
			temp_string += level_names[i];
		}
	}
	level_names_split.push_back(temp_string);

	/*
	 * This loop loads the individual level files and stores them in a map
	 */
	for(uint i = 0; i < level_names_split.size(); i++) {
		level_list[level_names_split.at(i)] = level_class;
		level_list[level_names_split.at(i)].load_sprites(level_names_split.at(i));
	}

	current_level = al_get_config_value(config_main, "", "start");
	start_x = std::stoi(al_get_config_value(config_main, "", "x"));
	start_y = std::stoi(al_get_config_value(config_main, "", "y"));

	load_level(current_level, start_x, start_y);

	background = al_load_bitmap("sprites/land4.png");
};


void GameScreen::load_level(std::string next_level, int x, int y) {
	//	level::level_sprites.clear();

	level_class = level_list[next_level];

	calculate_movement.set_start_pos(x, y);

	level_width = level_class.width;
	level_height = level_class.height;

	calculate_movement.set_width_height(level_class.width, level_class.height);
}


void GameScreen::refresh_screen(Display *display) {
	display->draw_bitmap(background, 0, 0);
	for(uint i = 0; i < level_class.level_sprites.size(); i++) {
		display->draw_bitmap(level_class.level_sprites.at(i).sprite_bitmap, level_class.level_sprites.at(i).x, level_class.level_sprites.at(i).y);
	}

	calculate_movement.draw_character(display);

	char_x = calculate_movement.get_x();
	char_y = calculate_movement.get_y();

	camera_update(camera_position, char_x, char_y, 20, 40);

	add_bullets.draw_to_screen(display);

	al_identity_transform(&camera);
	al_translate_transform(&camera, -camera_position[0], -camera_position[1]);		//Moves objects as the screen moves
	al_use_transform(&camera);
}

void GameScreen::key_down(ALLEGRO_EVENT *event) {
	if(event->keyboard.keycode == ALLEGRO_KEY_W) {
		calculate_movement.set_direction(up);
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_A) {
		calculate_movement.set_direction(left);
		moving_left = true;
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_S) {
		calculate_movement.set_direction(down);
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_D) {
		calculate_movement.set_direction(right);
		moving_right = true;
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_LSHIFT) {
		calculate_movement.set_update_speed(500.0);
	}
}

void GameScreen::key_up(ALLEGRO_EVENT *event) {
	if(event->keyboard.keycode == ALLEGRO_KEY_W) {
		calculate_movement.set_direction(stop_jump);
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_A) {
		calculate_movement.set_direction(stop_x);
		moving_left = false;
		if(moving_right) {
			calculate_movement.set_direction(right);
		}
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_S) {
		calculate_movement.set_direction(down);
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_D) {
		calculate_movement.set_direction(stop_x);
		moving_right = false;
		if(moving_left) {
			calculate_movement.set_direction(left);
		}
	}
	if(event->keyboard.keycode == ALLEGRO_KEY_LSHIFT) {
		calculate_movement.set_update_speed(100.0);
	}
}


void GameScreen::mouse_down(float mouse_x, float mouse_y, std::string button) {

}


void GameScreen::update_game() {
	calculate_movement.calculate_movement(&level_class.level_sprites);
	add_bullets.calculate_movement();
}


void GameScreen::camera_update(float* camera_position, float x, float y, float width, float height) {
	camera_position[0] = -(1600 / 2) + (x + width / 2);
	camera_position[1] = -(900 / 2) + (y + height / 2);

	if(camera_position[0] < 0) {
		camera_position[0] = 0;
	}
	if(camera_position[0] > level_width) {
		camera_position[0] = level_width;
	}
	if(camera_position[1] < 0) {
		camera_position[1] = 0;
	}
	if(camera_position[1] > level_height) {
		camera_position[1] = level_height;
	}
}


void GameScreen::cursor_update(float mouse_x, float mouse_y, Display *display) {
	display->set_default_display();
	al_draw_bitmap(cursor, mouse_x + camera_position[0], mouse_y + camera_position[1], 0);
	display->hide_mouse_pointer();
}


GameScreen::~GameScreen() {
	al_destroy_config(config_main);
	al_destroy_bitmap(cursor);
	al_destroy_bitmap(foregrond_layer);
	al_destroy_bitmap(background);
	al_destroy_bitmap(front_layer);
}

