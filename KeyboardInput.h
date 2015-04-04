/*
 * KeyboardInput.h
 *
 *  Created on: 2 Apr 2015
 *      Author: denis2
 */

#ifndef KEYBOARDINPUT_H_
#define KEYBOARDINPUT_H_

#include <allegro5/allegro.h>
#include <string>

class KeyboardInput {
public:
	KeyboardInput();

	char keyboard(ALLEGRO_EVENT *event);
	void change_case(std::string letter_case);

	virtual ~KeyboardInput();

private:
	bool uppercase;

};

#endif /* KEYBOARDINPUT_H_ */
