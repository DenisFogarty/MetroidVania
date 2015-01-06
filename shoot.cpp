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
    ALLEGRO_FONT *this_font = al_load_font("fonts/LiberationMono-Bold.ttf", 24, 0);
    al_draw_text(this_font, al_map_rgb(255, 255, 255), 50, 50, 0, "Hello World");

    //Draws a pixel
    al_draw_pixel(200, 200, al_map_rgb(255, 0, 0));

    al_draw_circle(100, 100, 50, al_map_rgb(255, 0, 255), 2);

    al_flip_display();

    al_rest(5);
}

void shoot::fire_line() {

}

shoot::~shoot()
{
    al_destroy_display(display);
    al_destroy_bitmap(bullet);
}
