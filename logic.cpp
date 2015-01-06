/*
 * logic.cpp
 *
 *  Created on: 6 Jan 2015
 *      Author: denis
 */

#include "logic.h"

logic::logic() {
	game_logic = al_create_event_queue();
	if(!game_logic) {
		fprintf(stderr, "Failed to initialise game_logic");
	}

	logic_timer = al_create_timer(1/120);
	if(!logic_timer) {
		fprintf(stderr, "Failed to initialise logic_timer");
		al_destroy_event_queue(game_logic);
	}
}

logic::~logic() {
	al_destroy_event_queue(game_logic);
	al_destroy_timer(logic_timer);
}
