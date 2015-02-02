#include "movement.h"

movement::movement() {
	player_x = 0;
	player_y = 230;
	movement_x = 0;
	movement_y = 0;
}


void movement::set_direction(int direction) {
	if(direction == 0) {
		movement_x = -.2;
	}
	else if(direction == 1){
		movement_x = .2;
	}
	else if(direction == 2) {
		movement_y = -.2;
	}
	else if(direction == 3) {
		movement_y = .2;
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

	if(player_x <= 0 || player_x >= 620) {
		set_direction(stop_x);
		player_x = (int)player_x;
	}
	if(player_y <= 0 || player_y >= 460) {
		set_direction(stop_y);
		player_y = (int)player_y;
	}
}


void movement::draw_character(ALLEGRO_DISPLAY &display) {
	al_draw_filled_rectangle(player_x, player_y, player_x + 20, player_y + 20, al_map_rgb(255, 0, 0));
}


int movement::get_x() {
	return player_x;
}

int movement::get_y() {
	return player_y;
}


movement::~movement() {

}
