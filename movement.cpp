#include "movement.h"

movement::movement() {
	player_x = 0;
	player_y = 230;
	movement_x = 0;
	movement_y = 0;
	gravity = -0.3;

	char_height = 40;
	char_width = 20;

	orig_time = al_get_time();
	time = orig_time;
}


void movement::set_direction(int direction) {
	if(direction == 0) {
		movement_x = -0.2;
	}
	else if(direction == 1){
		movement_x = 0.2;
	}
	else if(direction == 2) {
		movement_y = -0.6;
	}
	else if(direction == 3) {
		movement_y = 0.5;
	}

	if(direction == 4) {
		movement_x = 0;
	}
	else if(direction == 5) {
		movement_y = 0;
	}
}


void movement::calculate_movement() {
	player_x += movement_x;
	player_y += movement_y;

	if(player_x <= 0 || player_x >= 1920 - char_width) {
		set_direction(stop_x);
		player_x = (int)player_x;	//If the character is slightly off screen, casting it as an int returns them back to the screen
	}
	if(player_y <= 0 || player_y >= 1080 - char_height) {
		set_direction(stop_y);
		player_y = (int)player_y;	//If the character is slightly off screen, casting it as an int returns them back to the screen
	}
}


void movement::calculate_jump() {
	time = al_get_time() - orig_time;
	gravity *= time;

	player_y += movement_y * gravity;
}


void movement::draw_character(ALLEGRO_DISPLAY &display) {
	al_draw_filled_rectangle(player_x, player_y, player_x + char_width, player_y + char_height, al_map_rgb(255, 0, 255));
}


int movement::get_x() {
	return player_x;
}

int movement::get_y() {
	return player_y;
}


movement::~movement() {

}
