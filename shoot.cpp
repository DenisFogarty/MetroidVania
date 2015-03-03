#include "shoot.h"

bullets_data::bullets_data() {
	hypotenuse = 0;
	traj_x = 0;
	traj_y = 0;

	bullet_start_x = 13;
	bullet_start_y = 40/5;

	bullet_bit = al_load_bitmap("sprites/bullet.png");
}


void bullets_data::add_rocket(float player_x, float player_y, float cursor_x, float cursor_y) {
	new_bullet.speed = .7;
	new_bullet.damage = 80;
	new_bullet.blast_radius = 10;
	add_bullet(player_x, player_y, cursor_x, cursor_y);
}


void bullets_data::add_basic(float player_x, float player_y, float cursor_x, float cursor_y) {
	new_bullet.speed = 1.2;
	new_bullet.damage = 20;
	new_bullet.blast_radius = 0;
	add_bullet(player_x, player_y, cursor_x, cursor_y);
}


/*
 * After determining the bullet type, this function is called
 */
void bullets_data::add_bullet(float player_x, float player_y, float cursor_x, float cursor_y) {
	new_bullet.x = player_x + bullet_start_x;
	new_bullet.y = player_y + bullet_start_y;

	hypotenuse = calculate.calculate_hypotenuse(player_x, player_y, cursor_x, cursor_y);

	traj_x = calculate.calculate_trajectory_x(player_x, cursor_x, hypotenuse);
	new_bullet.direction_x = traj_x * new_bullet.speed;

	traj_y = calculate.calculate_trajectory_y(player_y, cursor_y, hypotenuse);
	new_bullet.direction_y = traj_y *= new_bullet.speed;

	new_bullet.angle = calculate.calculate_angle(cursor_x - player_x, hypotenuse, player_y, cursor_y);

	new_bullet.width = al_get_bitmap_width(bullet_bit);
	new_bullet.height = al_get_bitmap_height(bullet_bit);

	/*
	 * Top left = x, y
	 * Top right = x2, y2
	 * Bottom left = x3, y3
	 * Bottom right = x4, y4
	 */
	new_bullet.x2 = new_bullet.x + new_bullet.width * cos(new_bullet.angle);
	new_bullet.y2 = new_bullet.y + new_bullet.width * sin(new_bullet.angle);

	new_bullet.x3 = new_bullet.x + new_bullet.height * cos(new_bullet.angle + 1.57);	//1.57 rads = 90 degrees, need to add this for calculation of lower points
	new_bullet.y3 = new_bullet.y + new_bullet.height * sin(new_bullet.angle + 1.57);

	new_bullet.x4 = new_bullet.x2 + new_bullet.height * cos(new_bullet.angle + 1.57);
	new_bullet.y4 = new_bullet.y2 + new_bullet.height * sin(new_bullet.angle + 1.57);

	bullets.push_back(new_bullet);
}


//This should never be used, purely for debugging
void bullets_data::remove_bullet(uint pos) {
	if(bullets.size() > pos) {
		std::list<bullet>::iterator next_bullet = bullets.begin();

		for(uint i = 0; i < pos; i++) {
			next_bullet++;
		}

		bullets.erase(next_bullet);
	}
}


void bullets_data::remove_bullet(std::list<bullet>::iterator bullet) {
	bullet_iter++;		//This iterator is pointing the the same element as parameter 'bullet', need to increment before removal to prevent error
	bullets.erase(bullet);
}


void bullets_data::calculate_movement() {
	if(bullets.size() > 0) {
		bullet_iter = bullets.begin();
		while(bullet_iter != bullets.end()) {
			bullet_iter->x += bullet_iter->direction_x;
			bullet_iter->y += bullet_iter->direction_y;
			bullet_iter->x2 += bullet_iter->direction_x;
			bullet_iter->y2 += bullet_iter->direction_y;
			bullet_iter->x3 += bullet_iter->direction_x;
			bullet_iter->y3 += bullet_iter->direction_y;
			bullet_iter->x4 += bullet_iter->direction_x;
			bullet_iter->y4 += bullet_iter->direction_y;

			if(bullet_iter->x > 1920 || bullet_iter->y > 1080 || bullet_iter->x2 < 0 || bullet_iter->y2 < 0 ||
					detect_collision.detect_collision(bullet_iter->x, bullet_iter->y,
							bullet_iter->x2, bullet_iter->y2,
							bullet_iter->x3, bullet_iter->y3,
							bullet_iter->x4, bullet_iter->y4)) {

				remove_bullet(bullet_iter);

			} else {
				bullet_iter++;
			}
		}
	}
}


void bullets_data::draw_to_screen(ALLEGRO_DISPLAY&) {
	if(bullets.size() > 0) {
		bullet_iter = bullets.begin();
		while(bullet_iter != bullets.end()) {
			al_draw_rotated_bitmap(bullet_bit, 0, 0, bullet_iter->x, bullet_iter->y, bullet_iter->angle, 0);
			bullet_iter++;
		}
	}
}


int bullets_data::get_size() {
	return bullets.size();
}


bullets_data::~bullets_data() {
	al_destroy_bitmap(bullet_bit);
}
