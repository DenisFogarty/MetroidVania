#ifndef SHOOT_H
#define SHOOT_H

#include <iostream>
#include <list>
#include "main.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class bullet {
private:
	float x1, y1, x2, y2;
	bullet(float ext_x1, float ext_y1, float ext_x2, float ext_y2, float direction_x, float direction_y);	//direction values also control speed
	~bullet();
};


class bullets_data {			//Deals with adding, removing and storing bullets
public:
	void add_bullet(float ext_x1, float ext_x2, float ext_y1, float ext_y2, float player_x, float player_y, float cursor_x, float cursor_y);

private:
	bullets_data();

	std::list <bullet> bullets;
	void calculate_position();

protected:
};

#endif // SHOOT_H
