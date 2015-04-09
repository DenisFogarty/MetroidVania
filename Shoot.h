#ifndef SHOOT_H
#define SHOOT_H

#include <iostream>
#include <list>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Calculations.h"
#include "Collision.h"
#include "Items.h"
#include "Display.h"


class bullet : item {
	friend class bullets_data;
private:
	float x2, y2, x3, y3, x4, y4;
	float direction_x, direction_y;		//Directions should also control speed
	float angle;
	float speed;
	float blast_radius;
	float width, height;
};


class bullets_data {			//Deals with adding, removing and storing bullets
public:
	void add_rocket(float player_x, float player_y, float cursor_x, float cursor_y);
	void add_basic(float player_x, float player_y, float cursor_x, float cursor_y);
	void remove_bullet(uint pos);
	void remove_bullet(std::list<bullet>::iterator bullet);
	void remove_all_bullets();
	void calculate_movement();
	void draw_to_screen(Display *display);
	void set_level_size(float width, float height);
	int get_size();

	bullets_data();
	~bullets_data();

private:
	void add_bullet(float player_x, float player_y, float cursor_x, float cursor_y);
	void calculate_trajectory(float player_x, float player_y, float cursor_x, float cursor_y);
	void calculate_angle(float adjacent, float hypotenuse, float player_y, float cursor_y);

	ALLEGRO_BITMAP *bullet_bit;

	bullet new_bullet;

	std::list <bullet> bullets;
	std::list <bullet>::iterator bullet_iter;
	float hypotenuse;
	float traj_x, traj_y;
	float bullet_start_x, bullet_start_y;
	float level_width, level_height;

	calculations calculate;

	collision detect_collision;

protected:
};

#endif // SHOOT_H
