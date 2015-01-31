#include "movement.h"

movement::movement() {
	player_x = 0;
	player_y = 0;
	movement_speed = 0;
}


void movement::set_direction(int direction) {
	if(direction == 0 && movement_speed > 0) {
		movement_speed *= -1;
	}
	else if(movement_speed < 0) {
		movement_speed *= -1;
	}
}


int movement::get_x() {
	return player_x;
}

int movement::get_y() {
	return player_y;
}


movement::~movement() {
	// TODO Auto-generated destructor stub
}
