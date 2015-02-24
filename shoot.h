#ifndef SHOOT_H
#define SHOOT_H

#include <iostream>
#include <list>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "items.h"
#include "calculations.h"
#include "collision.h"


class bullet : item {
	friend class bullets_data;
private:
	float x2, y2;
	float direction_x, direction_y;		//Directions should also control speed
	float angle;
	float speed;
	float blast_radius;
};


class bullets_data {			//Deals with adding, removing and storing bullets
public:
	void add_rocket(float player_x, float player_y, float cursor_x, float cursor_y);
	void add_basic(float player_x, float player_y, float cursor_x, float cursor_y);
	void remove_bullet(uint pos);
	void remove_bullet(std::list<bullet>::iterator bullet);
	void calculate_movement();
	void draw_to_screen(ALLEGRO_DISPLAY&);
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
	std::list<bullet>::iterator bullet_iter;
	float hypotenuse;
	float traj_x, traj_y;
	float bullet_start_x, bullet_start_y;

	calculations calculate;

	collision detect_collision;

protected:
};

#endif // SHOOT_H
