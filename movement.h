#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <iostream>
#include <allegro5/allegro.h>

#define left 0
#define right 1

class movement {
public:
	movement();
	virtual ~movement();

	void set_direction(int direction);
	int get_x();
	int get_y();

private:
	float player_x, player_y;
	float movement_speed;
};

#endif /* MOVEMENT_H_ */
