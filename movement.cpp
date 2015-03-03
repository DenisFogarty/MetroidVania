#include "movement.h"

movement::movement() {
	player_x = 0;
	player_y = 230;
	movement_x = 0;
	movement_y = 0.5;
	gravity = 0.00125;

	char_height = 40;
	char_width = 20;

	jump = false;
}


void movement::set_direction(int direction) {
	if(direction == 0) {
		movement_x = -0.2;
	}
	else if(direction == 1){
		movement_x = 0.2;
	}
	/*
	 * The bool 'jump' will be false when the ground is hit
	 */
	else if(direction == 2 && jump == false) {
		movement_y = -0.5;
		jump = true;
	}

	if(direction == 4) {
		movement_x = 0;
	}

	/*
	 * If jumping is cancelled, the 'movement_y' variable is set to the current gravity * split, which sends the player moving down
	 * This makes the downward momentum slower the closer they are to the ground. This makes the jumping feel more fluid
	 */
	if(direction == 6) {
		if(movement_y < 0.0) {
			movement_y = gravity;
		}
	}
}


void movement::calculate_movement() {
	player_x += movement_x;
	player_y += movement_y;

	if(jump) {
		calculate_jump();
	}

	if(player_x <= 0 || player_x >= 1920 - char_width) {
		set_direction(stop_x);
		player_x = (int)player_x;	//If the character is slightly off screen, casting it as an int returns them back to the screen. Remove this
	}
	if(player_y <= 0 || player_y >= 1080 - char_height) {
		set_direction(stop_y);
		player_y = 1080 - char_height;
		jump = false;
	}
	if(detect_collision.detect_collision(player_x, player_y, 20, 40)) {
		player_y = detect_collision.get_item_y() -40;
		jump = false;
	}
}


void movement::calculate_jump() {
	movement_y += gravity;

	if(movement_y > .75) {
		movement_y = .75;
	}
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
