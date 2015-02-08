#include "shoot.h"

bullets_data::bullets_data() {
	hypotenuse = 0;
	traj_x = 0;
	traj_y = 0;

	bullet_start_x = 40/5;
	bullet_start_y = 20;

	bullet_bit = al_load_bitmap("sprites/bullet.png");
}


void bullets_data::add_bullet(float player_x, float player_y, float cursor_x, float cursor_y) {
	new_bullet.x1 = player_x + 8;
	new_bullet.y1 = player_y + 8;
	new_bullet.x2 = player_x + 13;
	new_bullet.y2 = player_y + 13;
	calculate_trajectory(player_x, player_y, cursor_x, cursor_y);
	calculate_angle(cursor_x - player_x, player_y, cursor_y);
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


//Calculates the speed and direction of the bullet
void bullets_data::calculate_trajectory(float player_x, float player_y, float cursor_x, float cursor_y) {
	traj_x = (cursor_x - player_x);
	traj_y = (cursor_y - player_y);


	hypotenuse = (traj_x)*(traj_x) + (traj_y)*(traj_y);
	hypotenuse = sqrt(hypotenuse);


	if(traj_x != 0) {
		traj_x = traj_x/hypotenuse;
	}

	if(traj_y != 0) {
		traj_y = traj_y/hypotenuse;
	}


	new_bullet.direction_x = traj_x*.4;
	new_bullet.direction_y = traj_y*.4;
}


void bullets_data::calculate_direction() {
	if(bullets.size() > 0) {
		bullet_iter = bullets.begin();
		while(bullet_iter != bullets.end()) {
			bullet_iter->x1 += bullet_iter->direction_x;
			bullet_iter->y1 += bullet_iter->direction_y;
			bullet_iter->x2 += bullet_iter->direction_x;
			bullet_iter->y2 += bullet_iter->direction_y;

			if(bullet_iter->x1 > 640 || bullet_iter->y1 > 480|| bullet_iter->x2 < 1 || bullet_iter->y2 < 1) {
				remove_bullet(bullet_iter);
			} else {
				bullet_iter++;
			}
		}
	}
}


void bullets_data::calculate_angle(float adjacent, float player_y, float cursor_y) {

	float cos = adjacent/hypotenuse;
	new_bullet.angle = acos(cos);
	std::cout << new_bullet.angle << std::endl;

	/*
	 * If the angle is in the top two quadrants, nothing needs to be changed
	 * If the angle is in the bottom two quadrants, the angle needs to become a minus
	 */
	if(cursor_y < player_y) {
		std::cout << "Test" << std::endl;
		new_bullet.angle *= -1;
		std::cout << new_bullet.angle << std::endl;
	}
}


int bullets_data::get_size() {
	return bullets.size();
}


void bullets_data::draw_to_screen(ALLEGRO_DISPLAY&) {
	if(bullets.size() > 0) {
		bullet_iter = bullets.begin();
		while(bullet_iter != bullets.end()) {
			al_draw_rotated_bitmap(bullet_bit, 8, 5, bullet_iter->x1, bullet_iter->y1, bullet_iter->angle, 0);
			bullet_iter++;
		}
	}
}


bullets_data::~bullets_data() {

}
