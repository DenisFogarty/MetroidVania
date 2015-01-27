#include "shoot.h"

bullets_data::bullets_data() {

}

void bullets_data::add_bullet(float ext_x1, float ext_x2, float ext_y1, float ext_y2, float player_x, float player_y, float cursor_x, float cursor_y) {
	bullet new_bullet;
	bullets.push_back(new_bullet);
}

void bullets_data::remove_bullet(int pos) {
	if(bullets.size() > 1) {
		std::list<bullet>::iterator next_bullet = bullets.begin();

		for(int i = 0; i < pos; i++) {
			next_bullet++;
		}

		bullets.erase(next_bullet);
	}
}

int bullets_data::get_size() {
	return bullets.size();
}

void bullets_data::calculate_position() {

}
