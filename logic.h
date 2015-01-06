/*
 * logic.h
 *
 *  Created on: 6 Jan 2015
 *      Author: denis
 */

#ifndef LOGIC_H_
#define LOGIC_H_

#include <stdio.h>

#include <allegro5/allegro.h>

class logic {
public:
	logic();
	virtual ~logic();

private:
	ALLEGRO_EVENT_QUEUE	*game_logic;
	ALLEGRO_TIMER		*logic_timer;
};

#endif /* LOGIC_H_ */
