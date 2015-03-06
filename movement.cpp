#include "movement.h"

movement::movement() {
	character = al_load_bitmap("sprites/running.png");

	dir = STOP;

	num_sprite = 0;
	prev_time = 0;

	player_x = 0;
	player_y = 230;
	movement_x = 0;
	movement_y = 0.5;
	gravity = 0.00125;

	char_height = 43;
	char_width = 35;

	jump = false;
	ground = true;

	p_items = items_data::get_item_vector();
	i = 0;
}


void movement::set_direction(int direction) {
	if(direction == 0) {
		movement_x = -0.2;
		dir = LEFT;
		num_sprite = 0;
	}
	else if(direction == 1){
		movement_x = 0.2;
		dir = RIGHT;
		num_sprite = 0;
	}

	/*
	 * The bool 'jump' will be false when the ground is hit
	 */
	if(direction == 2 && jump == false) {
		movement_y = -0.5;
		jump = true;
		ground = false;
	}

	if(direction == 4) {
		movement_x = 0;
		if(dir == RIGHT) {
			dir = STOP;
		} else {
			dir = STOP_LEFT;
		}
	}

	/*
	 * If jumping is cancelled, the 'movement_y' variable is set to the current gravity * split, which sends the player moving down
	 * This makes the downward momentum slower the closer they are to the ground. This makes the jumping feel more fluid
	 */
	if(direction == 6) {
		if(movement_y < 0.0) {
			movement_y = gravity * 2;
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


	for(i = 0; i < p_items->size(); i++) {

		current_item = (*p_items)[i];
		if(detect_collision.detect_collision(player_x, player_y, char_width, char_height, current_item.x, current_item.y, current_item.width, current_item.height)) {
			/*
			 * Checks if the player has collided with the left side of an object
			 */
			if(player_y + char_height - 1 > current_item.y &&
					player_y < current_item.y + current_item.height - 1 &&
					player_x < current_item.x) {

				player_x = current_item.x - char_width;
			}

			/*
			 * Checks if the player has collided with the right side of an object
			 */
			else if(player_y + char_height - 1 > current_item.y &&
					player_y < current_item.y + current_item.height - 1 &&
					player_x + char_width - 1 > current_item.x + current_item.width - 1) {

				player_x = current_item.x + current_item.width;
			}

			/*
			 * Checks if the player has collided with the underside of an object
			 */
			else if(player_x + char_width - 1 > current_item.x &&
					player_x < current_item.x + current_item.width - 1 &&
					player_y + char_height - 1 > current_item.y + current_item.height - 1) {

				movement_y = gravity * 20;
			}

			/*
			 * Checks if the player has hit ground
			 */
			else if(player_x + char_width - 1 > current_item.x &&
					player_x < current_item.x + current_item.width - 1 &&
					player_y < current_item.y) {

				jump = false;
				player_y = current_item.y - char_height;
			}
		}
	}
}


void movement::calculate_jump() {
	movement_y += gravity;

	if(movement_y > .75) {
		movement_y = .75;
	}
}


void movement::draw_character(ALLEGRO_DISPLAY &display) {
	al_draw_bitmap_region(character, pos_sprite[dir][num_sprite], dir*43, 35, 43, player_x, player_y, 0);

	if(al_get_time() - prev_time > .05) {
		prev_time = al_get_time();
		num_sprite++;
	}

	if(num_sprite > 9) {
		num_sprite = 0;
	}
}


int movement::get_x() {
	return player_x;
}

int movement::get_y() {
	return player_y;
}


movement::~movement() {

}
