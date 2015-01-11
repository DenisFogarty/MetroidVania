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
	shoot(ALLEGRO_BITMAP *ext_bitmap, ALLEGRO_MUTEX *ext_mutex, ALLEGRO_COND *ext_cond, bool *ext_ready);
	virtual ~shoot();
	void fire_line();

private:
	ALLEGRO_BITMAP	*foreground	=	NULL;
	ALLEGRO_BITMAP  *bullet		=	NULL;
	ALLEGRO_MUTEX	*mutex		=	NULL;
	ALLEGRO_COND	*cond		=	NULL;
	bool *READY;

	float line_x;
	float line_y;

protected:
};

#endif // SHOOT_H
