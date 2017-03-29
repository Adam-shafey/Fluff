/*
 * State.h
 *
 *  Created on: Nov 21, 2016
 *      Author: abdo_
 */

#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include "Grid.h"

using namespace std;

class State {
public:
	bool isfree; //1 is empty, 0 is occupied with a player
	int isAorBT; // 1 is A, 2 is B trace, 0 is empty
	State(){
		isfree=true;
		isAorBT = 0;
	}
	void changestate(bool a, int c){
		isfree = a;
		isAorBT = c;
	}
	void printstate(){
		cout << "isFree: " << isfree << "isAorBT: " << isAorBT;
	}
	~State(){
	}
};

#endif /* STATE_H_ */
