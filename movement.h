#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "collision.h"
#include "items.h"

#define left 		0
#define right		1
#define up			2
#define down		3
#define stop_x		4
#define stop_y		5
#define stop_jump	6

class movement {
public:
	movement();
	virtual ~movement();

	void set_direction(int direction);
	void calculate_movement();
	void calculate_fall();
	void draw_character(ALLEGRO_DISPLAY &display);
	int get_x();
	int get_y();

private:
	ALLEGRO_BITMAP *character;

	uint dir;
	enum dir_sprite {STOP_RIGHT, RIGHT, STOP_LEFT, LEFT};
	float pos_sprite[4][10] = {{0}, {0, 35, 70, 105, 140, 175, 210, 245, 280, 315}, {0}, {0, 35, 70, 105, 140, 175, 210, 245, 280, 315}};
	uint num_sprite;
	float move_speed;

	float prev_time;

	float velocity;
	float gravity;

	float player_x, player_y;
	float movement_x;
	float movement_y;
	float char_height, char_width;
	bool jump;
	bool ground;
	collision detect_collision;
	std::vector<item>* p_items;
	item current_item;
	uint i;
};

#endif /* MOVEMENT_H_ */
