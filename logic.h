#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class logic {
public:
	logic(ALLEGRO_DISPLAY *ext_display);
	virtual ~logic();

private:
	ALLEGRO_EVENT_QUEUE	*game_logic;
	ALLEGRO_TIMER		*logic_timer;

protected:
};

#endif /* LOGIC_H_ */
