#ifndef SHOOT_H
#define SHOOT_H

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class shoot
{
    public:
        shoot(ALLEGRO_DISPLAY *ext_display);
        virtual ~shoot();
        void fire_line();

    private:
		ALLEGRO_DISPLAY *display	=	NULL;
        ALLEGRO_BITMAP  *bullet		=	NULL;

        int imagewidth;
        int imageheight;

		float PLAY_X;
		float PLAY_Y;
		float CUR_X;
		float CUR_Y;
		bool READY;
		bool DRAW_LINE;
		float x1, y1, x2, y2;

    protected:
};

#endif // SHOOT_H
