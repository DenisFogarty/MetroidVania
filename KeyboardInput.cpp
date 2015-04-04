/*
 * KeyboardInput.cpp
 *
 *  Created on: 2 Apr 2015
 *      Author: denis2
 */

#include "KeyboardInput.h"

KeyboardInput::KeyboardInput() {
	uppercase = false;
}

char KeyboardInput::keyboard(ALLEGRO_EVENT *event) {
	switch(event->keyboard.keycode){

	case ALLEGRO_KEY_A:
		if(!uppercase) {
			return 'a';
		}
		else {
			return 'A';
		}

		break;

	case ALLEGRO_KEY_B:
		if(!uppercase) {
			return 'b';
		}
		else {
			return 'B';
		}

		break;

	case ALLEGRO_KEY_C:
		if(!uppercase) {
			return 'c';
		}
		else {
			return 'C';
		}

		break;

	case ALLEGRO_KEY_D:
		if(!uppercase) {
			return 'd';
		}
		else {
			return 'D';
		}

		break;

	case ALLEGRO_KEY_E:
		if(!uppercase) {
			return 'e';
		}
		else {
			return 'E';
		}

		break;

	case ALLEGRO_KEY_F:
		if(!uppercase) {
			return 'f';
		}
		else {
			return 'F';
		}

		break;

	case ALLEGRO_KEY_G:
		if(!uppercase) {
			return 'g';
		}
		else {
			return 'G';
		}

		break;

	case ALLEGRO_KEY_H:
		if(!uppercase) {
			return 'h';
		}
		else {
			return 'H';
		}

		break;

	case ALLEGRO_KEY_I:
		if(!uppercase) {
			return 'i';
		}
		else {
			return 'I';
		}

		break;

	case ALLEGRO_KEY_J:
		if(!uppercase) {
			return 'j';
		}
		else {
			return 'J';
		}

		break;

	case ALLEGRO_KEY_K:
		if(!uppercase) {
			return 'k';
		}
		else {
			return 'K';
		}

		break;

	case ALLEGRO_KEY_L:
		if(!uppercase) {
			return 'l';
		}
		else {
			return 'L';
		}

		break;

	case ALLEGRO_KEY_M:
		if(!uppercase) {
			return 'm';
		}
		else {
			return 'M';
		}

		break;

	case ALLEGRO_KEY_N:
		if(!uppercase) {
			return 'n';
		}
		else {
			return 'N';
		}

		break;

	case ALLEGRO_KEY_O:
		if(!uppercase) {
			return 'o';
		}
		else {
			return 'O';
		}

		break;

	case ALLEGRO_KEY_P:
		if(!uppercase) {
			return 'p';
		}
		else {
			return 'P';
		}

		break;

	case ALLEGRO_KEY_Q:
		if(!uppercase) {
			return 'q';
		}
		else {
			return 'Q';
		}

		break;

	case ALLEGRO_KEY_R:
		if(!uppercase) {
			return 'r';
		}
		else {
			return 'R';
		}

		break;

	case ALLEGRO_KEY_S:
		if(!uppercase) {
			return 's';
		}
		else {
			return 'S';
		}

		break;

	case ALLEGRO_KEY_T:
		if(!uppercase) {
			return 't';
		}
		else {
			return 'T';
		}

		break;

	case ALLEGRO_KEY_U:
		if(!uppercase) {
			return 'u';
		}
		else {
			return 'U';
		}

		break;

	case ALLEGRO_KEY_V:
		if(!uppercase) {
			return 'v';
		}
		else {
			return 'V';
		}

		break;

	case ALLEGRO_KEY_W:
		if(!uppercase) {
			return 'w';
		}
		else {
			return 'W';
		}

		break;

	case ALLEGRO_KEY_X:
		if(!uppercase) {
			return 'x';
		}
		else {
			return 'X';
		}

		break;

	case ALLEGRO_KEY_Y:
		if(!uppercase) {
			return 'y';
		}
		else {
			return 'Y';
		}

		break;

	case ALLEGRO_KEY_Z:
		if(!uppercase) {
			return 'z';
		}
		else {
			return 'Z';
		}

		break;

	case ALLEGRO_KEY_1:
		return '1';

		break;

	case ALLEGRO_KEY_2:
		return '2';

		break;

	case ALLEGRO_KEY_3:
		return '3';

		break;

	case ALLEGRO_KEY_4:
		return '4';

		break;

	case ALLEGRO_KEY_5:
		return '5';

		break;

	case ALLEGRO_KEY_6:
		return '6';

		break;

	case ALLEGRO_KEY_7:
		return '7';

		break;

	case ALLEGRO_KEY_8:
		return '8';

		break;

	case ALLEGRO_KEY_9:
		return '9';

		break;

	case ALLEGRO_KEY_0:
		return '0';

		break;

	case ALLEGRO_KEY_FULLSTOP:
		return '.';

		break;

	default:
		return ' ';
	}
}

void KeyboardInput::change_case(std::string letter_case) {
	if(letter_case == "lower") {
		uppercase = false;
	}
	else if(letter_case == "upper"){
		uppercase = true;
	}
}

KeyboardInput::~KeyboardInput() {

}

