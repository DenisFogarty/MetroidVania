#ifndef SHOOT_H
#define SHOOT_H

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class shoot {
public:
	void calculate_position(float *x1, float *y1, float *x2, float *y2, float speedx, float speedy);

private:

protected:
};

#endif // SHOOT_H
