/*
 * classlist.cpp
 *
 *  Created on: 23 Jan 2015
 *      Author: denis2
 */

#include "classlist.h"

class_list::class_list() {
	num_nodes = 0;
	a = nullptr;
	b = nullptr;
	temp = nullptr;
}


void class_list::add_class(const SHOOT& data) {
	a = new node;
	temp = a;
	b = a;
}


int class_list::size() {
	return 0;
}


class_list::~class_list() {
	std::cout << "Test" << std::endl;
}
