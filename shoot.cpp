#include "shoot.h"

bullets_data::bullets_data() {
	sum = 0;
	traj_x = 0;
	traj_y = 0;
}


void bullets_data::add_bullet(float ext_x1, float ext_y1, float ext_x2, float ext_y2, float player_x, float player_y, float cursor_x, float cursor_y) {
	new_bullet.x1 = ext_x1;
	new_bullet.y1 = ext_y1;
	new_bullet.x2 = ext_x2;
	new_bullet.y2 = ext_y2;
	calculate_trajectory(player_x, player_y, cursor_x, cursor_y);
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


	sum = (traj_x)*(traj_x) + (traj_y)*(traj_y);
	sum = sqrt(sum);


	if(traj_x != 0) {
		traj_x = traj_x/sum;
	}

	if(traj_y != 0) {
		traj_y = traj_y/sum;
	}


	traj_x = traj_x*.4;
	traj_y = traj_y*.3;
}


void bullets_data::calculate_direction() {
	if(bullets.size() > 0) {
		bullet_iter = bullets.begin();
		while(bullet_iter != bullets.end()) {
			bullet_iter->x1 += traj_x;
			bullet_iter->y1 += traj_y;
			bullet_iter->x2 += traj_x;
			bullet_iter->y2 += traj_y;

			if(bullet_iter->x1 > 1920 || bullet_iter->y1 > 1080|| bullet_iter->x2 < 1 || bullet_iter->y2 < 1) {
				remove_bullet(bullet_iter);
			} else {
				bullet_iter++;
			}
		}
	}
}


int bullets_data::get_size() {
	return bullets.size();
}


void bullets_data::draw_to_screen(ALLEGRO_DISPLAY&) {
	if(bullets.size() > 0) {
		bullet_iter = bullets.begin();
		while(bullet_iter != bullets.end()) {
			al_draw_line(bullet_iter->x1, bullet_iter->y1, bullet_iter->x2, bullet_iter->y2, al_map_rgb(255, 0, 0), 5);
			bullet_iter++;
		}
	}
}


bullets_data::~bullets_data() {

}
