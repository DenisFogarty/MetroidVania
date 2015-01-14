#include "shoot.h"

void shoot::calculate_position(float *x1, float *y1, float *x2, float *y2, float speed) {
	*x1 += speed;
	*y1 += speed;
	*x2 += speed;
	*y2 += speed;
}
