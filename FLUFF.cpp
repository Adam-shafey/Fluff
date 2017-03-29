//============================================================================
// Name        : FLUFF.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "Tree.h"
#include "Game.h"
#include "time.h"



using namespace std;


int main() {
	Game newgame;
	int size;
	int depth;

	cout << "Enter n the size of the grid: " << endl;
	cin >>  size;
	cout << "Enter n the depth of the tree: " << endl;
	cin >>  depth;

	newgame.GameSet(size,depth);
	//Tree newTree;
	//newTree.TreeSet(5,9);
	//newTree.GenerateTree();
	//cout << newTree.Evaluate();
	newgame.start();





	//Grid game;
	//game.GridSet(5);
	//game.play();
	//Tree testTree;
	//testTree.TreeSetFromPreviousGame(5,7, game);
	//testTree.GenerateTree();
	//cout << testTree.Evaluate();
	//game.play();





	return 0;
}
