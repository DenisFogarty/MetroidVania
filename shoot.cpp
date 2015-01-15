#include "shoot.h"

void shoot::calculate_position(float *x1, float *y1, float *x2, float *y2, float speedx, float speedy) {
	*x1 += speedx;
	*y1 += speedy;
	*x2 += speedx;
	*y2 += speedy;
}
