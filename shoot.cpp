#include "shoot.h"

shoot::shoot(ALLEGRO_DISPLAY *ext_display)
{
    display = ext_display;

    al_set_target_bitmap(al_get_backbuffer(display));

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    //Writes Hello World to the screen
    ALLEGRO_FONT *this_font = al_load_font("fonts/Universum.ttf", 24, 0);
    al_draw_text(this_font, al_map_rgb(255, 255, 255), 50, 50, 0, "Hello World");

    al_flip_display();

    line_x = 0;
    line_y = 0;

    fire_line();

    al_rest(5);
}

void shoot::fire_line() {
	while(line_x < 640 || line_y < 480) {
		al_draw_line(line_x, line_y, line_x + 5, line_y + 5, al_map_rgb(255, 0, 0), 3);
		line_x++;
		line_y++;

		al_flip_display();

		al_rest(.002);

		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
}

shoot::~shoot()
{
    al_destroy_display(display);
    al_destroy_bitmap(bullet);
}
