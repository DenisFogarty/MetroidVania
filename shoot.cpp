#include "shoot.h"

shoot::shoot(ALLEGRO_BITMAP *ext_bitmap, ALLEGRO_MUTEX *ext_mutex, ALLEGRO_COND *ext_cond, bool *ext_ready) {
	foreground = ext_bitmap;
	mutex = ext_mutex;
	cond = ext_cond;
	READY = ext_ready;

	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	al_set_target_bitmap(foreground);

	al_clear_to_color(al_map_rgb(0, 0, 0));

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
		al_set_target_bitmap(foreground);
		std::cout << "WORKING ASDLFJAS;D" << std::endl;
		al_lock_mutex(mutex);
		while (!READY) {
			al_wait_cond(cond, mutex);
		}
		*READY = false;

		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_line(line_x, line_y, line_x + 5, line_y + 5, al_map_rgb(255, 0, 0), 3);
		}
		al_unlock_mutex(mutex);
		*READY = true;
		al_broadcast_cond(cond);
		std::cout << "ASDOFAJPOGHSLDFAMSLF" << std::endl;

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
