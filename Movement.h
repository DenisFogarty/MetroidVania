#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Collision.h"
#include "Items.h"
#include "Display.h"

#define left 		0
#define right		1
#define up			2
#define down		3
#define stop_x		4
#define stop_y		5
#define stop_jump	6

class movement {
	friend class GameScreen;
public:
	movement();

	void set_start_pos(float x, float y);
	void set_width_height(float width, float height);

	void on_up_pressed();
	void on_left_pressed();
	void on_down_pressed();
	void on_right_pressed();

	void on_left_mouse_click();
	void on_right_mouse_click();

	void set_direction(int direction);
	void calculate_movement(std::vector<load_sprite_info> *sprite_info);

	void set_update_speed(float new_speed);

	void calculate_fall();
	void draw_character(Display *display);
	void next_character_sprite();
	int get_x();
	int get_y();

	virtual ~movement();

private:

	ALLEGRO_BITMAP *character_sheet;
	ALLEGRO_BITMAP *character;

	float update_speed;

	uint dir;
	enum dir_sprite {STOP_RIGHT, RIGHT, STOP_LEFT, LEFT};
	float pos_sprite[4][10] = {{0}, {0, 35, 70, 105, 140, 175, 210, 245, 280, 315}, {0}, {0, 35, 70, 105, 140, 175, 210, 245, 280, 315}};
	uint num_sprite;
	float move_speed;

	float prev_time;

	float velocity;
	float gravity;

	float level_width, level_height;

	float player_x, player_y;
	float movement_x;
	float movement_y;
	float char_height, char_width;
	bool jump;
	bool ground;

	std::vector <load_sprite_info> *p_sprites;

	collision detect_collision;
	load_sprite_info *current_item;
	uint i;
};

#endif /* MOVEMENT_H_ */
