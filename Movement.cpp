#include "Movement.h"

movement::movement() {
	character = al_load_bitmap("sprites/running.png");

	update_speed = 100.0;

	dir = STOP_RIGHT;

	num_sprite = 0;
	prev_time = 0;

	player_x = 10;
	player_y = 1080-43;
	movement_x = 0;
	movement_y = 0;
	move_speed = 300.0;

	velocity = 400.0;
	gravity = 1400.0;

	char_height = 43;
	char_width = 35;

	jump = false;
	ground = true;

	i = 0;
}


void movement::set_start_pos(float x, float y) {
	player_x = x;
	player_y = y;
}

void movement::set_width_height(float width, float height) {
	level_width = width;
	level_height = height;
}


void movement::set_direction(int direction) {
	if(direction == 1) {
		movement_x = move_speed/update_speed;
		dir = RIGHT;
		num_sprite = 0;
	}
	else if(direction == 0) {
		movement_x = -move_speed/update_speed;
		dir = LEFT;
		num_sprite = 0;
	}

	/*
	 * The bool 'jump' will be false when the ground is hit
	 */
	if(direction == 2 && jump == false && velocity == 400) {
		velocity = -600;
		movement_y = (1.0/update_speed) * velocity;
		jump = true;
	}

	if(direction == 4) {
		movement_x = 0;
		if(dir == RIGHT) {
			dir = STOP_RIGHT;
		} else if(dir == LEFT) {
			dir = STOP_LEFT;
		}
	}

	if(direction == 6) {
		if(movement_y < 0.0) {
			velocity = 10;
		}
	}
}


void movement::calculate_movement(std::vector<load_sprite_info> *sprite_info) {
	calculate_fall();

	player_x += movement_x;
	player_y += movement_y;

	if(player_x <= 0 || player_x >= level_width - char_width) {
		set_direction(stop_x);
		player_x = level_width - char_width - 1;
	}

	if(player_y <= 0 || player_y >= level_height - char_height) {
		set_direction(stop_y);
		player_y = level_height - char_height;
		velocity = 400;
		jump = false;
	}

	detect_collision.set_sprite_list(sprite_info);

	for(i = 0; i < sprite_info->size(); i++) {

		current_item = &(*sprite_info)[i];
		if(detect_collision.detect_collision(player_x, player_y, char_width, char_height, current_item->x, current_item->y, current_item->width, current_item->height)) {

			/*
			 * Checks if the player has hit ground
			 */
			if(player_x + char_width - 1 > current_item->x &&
					player_x < current_item->x + current_item->width - 1 &&
					player_y < current_item->y) {

				jump = false;
				player_y = current_item->y - char_height;
				velocity = 400;
			}
			/*
			 * Checks if the player has collided with the underside of an object
			 */
			else if(player_x + char_width - 1 > current_item->x &&
					player_x < current_item->x + current_item->width - 1 &&
					player_y + char_height - 1 > current_item->y + current_item->height - 1) {

				player_y = current_item->y + current_item->height;
				velocity = 10;
			}

			/*
			 * Checks if the player has collided with the left side of an object
			 */
			else if(player_y + char_height - 1 > current_item->y &&
					player_y < current_item->y + current_item->height - 1 &&
					player_x < current_item->x) {

				player_x = current_item->x - char_width;
			}

			/*
			 * Checks if the player has collided with the right side of an object
			 */
			else if(player_y + char_height - 1 > current_item->y &&
					player_y < current_item->y + current_item->height - 1 &&
					player_x + char_width - 1 > current_item->x + current_item->width - 1) {

				player_x = current_item->x + current_item->width;
			}
		}
	}
}


/*
 * This should always be running
 */
void movement::calculate_fall() {
	movement_y = (1.0/update_speed) * velocity;
	velocity += (1.0/update_speed) * gravity;

	if(movement_y > 1200.0/update_speed) {
		movement_y = 1200.0/update_speed;
	}
}


void movement::draw_character(Display *display) {
	display->draw_bitmap(al_create_sub_bitmap(character, pos_sprite[dir][num_sprite], dir*43, 35, 43), player_x, player_y);
	if(al_get_time() - prev_time > .0005 * update_speed) {
		prev_time = al_get_time();
		num_sprite++;
	}

	if(num_sprite > 9) {
		num_sprite = 0;
	}
}

void movement::set_update_speed(float new_speed) {
	update_speed = new_speed;
	set_direction(dir);
}


int movement::get_x() {
	return player_x;
}

int movement::get_y() {
	return player_y;
}


movement::~movement() {

}
