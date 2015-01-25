#include "shoot.h"

bullet::bullet(float ext_x1, float ext_y1, float ext_x2, float ext_y2) {
	x1 = 0;
	x2 = 10;
	y1 = 0;
	y2 = 10;
}


bullets_data::bullets_data() {

}

void bullets_data::add_bullet(float ext_x1, float ext_x2, float ext_y1, float ext_y2, float player_x, float player_y, float cursor_x, float cursor_y) {
	bullet new_bullet;
	bullets.push_back(new_bullet);
	delete new_bullet;
}

void bullets_data::calculate_position() {

}
