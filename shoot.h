#ifndef SHOOT_H
#define SHOOT_H

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class shoot {
public:
	shoot(ALLEGRO_BITMAP *ext_bitmap);
	virtual ~shoot();
	void fire_line();

private:
	ALLEGRO_BITMAP	*foreground	=	NULL;
	ALLEGRO_BITMAP  *bullet		=	NULL;

	float line_x;
	float line_y;

protected:
};

#endif // SHOOT_H
