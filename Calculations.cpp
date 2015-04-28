/*
 * calculations.cpp
 *
 *  Created on: 22 Feb 2015
 *      Author: denis2
 */

#include "Calculations.h"

calculations::calculations() {
	traj_x = 0;
	traj_y = 0;

	x = 0;
	y = 0;

	hypotenuse = 0;

	cos = 0;

	angle = 0;
}


float calculations::calculate_hypotenuse(float x1, float y1, float x2, float y2) {
	x = x2 - x1;
	y = y2 - y1;

	hypotenuse = sqrt((x*x) + (y*y));

	return hypotenuse;
}


float calculations::calculate_trajectory_x(float player_x, float cursor_x, float hypotenuse) {
	traj_x = (cursor_x - player_x);

	traj_x = traj_x/hypotenuse;

	return traj_x;
}


float calculations::calculate_trajectory_y(float player_y, float cursor_y, float hypotenuse) {
	traj_y = (cursor_y - player_y);

	traj_y = traj_y/hypotenuse;

	return traj_y;
}


float calculations::calculate_angle(float adjacent, float hypotenuse, float player_y, float cursor_y) {

	cos = adjacent/hypotenuse;
	angle = acos(cos);

	/*
	 * If the angle is in the top two quadrants, nothing needs to be changed
	 * If the angle is in the bottom two quadrants, the angle needs to become a minus
	 */
	if(cursor_y < player_y) {
		angle *= -1;
	}

	return angle;
}


calculations::~calculations() {

}
