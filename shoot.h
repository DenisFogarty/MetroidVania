#ifndef SHOOT_H
#define SHOOT_H

#include <iostream>
#include <list>
#include "main.h"

#include <allegro5/allegro.h>


class bullet {
	friend class bullets_data;
private:
	float x1, y1, x2, y2;
	float direction_x, direction_y;		//Directions should also control speed
};


class bullets_data {			//Deals with adding, removing and storing bullets
public:
	void add_bullet(float ext_x1, float ext_y1, float ext_x2, float ext_y2, float player_x, float player_y, float cursor_x, float cursor_y);
	void remove_bullet(uint pos);
	void remove_bullet(std::list<bullet>::iterator bullet);
	void calculate_trajectory();
	void calculate_direction();
	void draw_to_screen(ALLEGRO_DISPLAY&);
	int get_size();

	bullets_data();
	~bullets_data();

private:
	bullet new_bullet;
	std::list <bullet> bullets;
	std::list<bullet>::iterator bullet_iter;
protected:
};

#endif // SHOOT_H
