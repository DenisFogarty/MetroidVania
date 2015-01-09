#include "shoot.h"

shoot::shoot(ALLEGRO_BITMAP *ext_bitmap) {
    foreground = ext_bitmap;

    al_set_target_bitmap(foreground);

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    //Writes Hello World to the screen
    //ALLEGRO_FONT *this_font = al_load_font("fonts/Universum.ttf", 24, 0);
    //al_draw_text(this_font, al_map_rgb(255, 255, 255), 50, 50, 0, "Hello World");
    al_draw_line(0, 0, 10, 10, al_map_rgb(0, 255, 0), 3);


    line_x = 0;
    line_y = 0;

    fire_line();

    al_rest(5);
}

void shoot::fire_line() {
	while(line_x < 640 || line_y < 480) {
		//al_set_target_bitmap(foreground);
		al_lock_bitmap(foreground, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);
		{
			al_draw_line(line_x, line_y, line_x + 5, line_y + 5, al_map_rgb(255, 0, 0), 3);
		}
		//al_unlock_bitmap(foreground);
		line_x++;
		line_y++;

		//al_flip_display();

		al_rest(1.0/120.0);

		//al_clear_to_color(al_map_rgb(0, 0, 0));
	}
}

shoot::~shoot() {
    al_destroy_bitmap(foreground);
    al_destroy_bitmap(bullet);
}
