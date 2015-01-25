/*
 * classlist.h
 *
 *  Created on: 23 Jan 2015
 *      Author: denis2
 */

#ifndef CLASSLIST_H_
#define CLASSLIST_H_

#include <iostream>
#include "main.h"

class class_list {
public:
	class_list();
	virtual ~class_list();

	struct node {
		node* prev;
		template <class T> class data;
		node* next;
	};

	void add_class(const SHOOT& data);
	void remove_class(int position);
	int size();

private:
	int num_nodes;
	node* a;
	node* temp;
	node* b;
};

#endif /* CLASSLIST_H_ */
