/*
 * calculations.h
 *
 *  Created on: 22 Feb 2015
 *      Author: denis2
 */

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include <iostream>
#include <math.h>

class calculations {
public:
	calculations();

	float calculate_hypotenuse(float x1, float y1, float x2, float y2);
	float calculate_trajectory_x(float player_x, float cursor_x, float hypotenuse);
	float calculate_trajectory_y(float player_y, float cursor_y, float hypotenuse);
	float calculate_angle(float adjacent, float hypotenuse, float player_y, float cursor_y);

	virtual ~calculations();

private:
	float traj_x, traj_y;
	float hypotenuse;
	float x, y;

	float cos;
	float angle;

};

#endif /* CALCULATIONS_H_ */
