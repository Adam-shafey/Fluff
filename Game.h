/*
 * Game.h
 *
 *  Created on: Dec 4, 2016
 *      Author: Adam
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include "State.h"
#include "Grid.h"
#include "Tree.h"
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;



class Game {
public:
	Grid CurrentGame;
	int turn; // whose turn is it?
	int mve; // what move? 1, 2 or 3?
	int Size;
	int DecisionTreeDepth;
	int whostarted;
	int ANumOfwins;
	int BNumOfwins;

	Game(){
	turn = 1;
	mve = 0; // move
	whostarted = 1;
	ANumOfwins = 0;
	BNumOfwins = 0;
	}
	~Game(){

	}

	void GameSet(int s, int dTD){
		Size = s;
		DecisionTreeDepth = dTD;
		CurrentGame.GridSet(s);
		CurrentGame.printstate();
	}
	void start(){
		bool replay =true;
		while (replay){
			if ( didsomeonewin(CurrentGame) == 0 ){
								play();
								}
								else if (didsomeonewin(CurrentGame) || didsomeonewin(CurrentGame)) {cout << "Player: " 	<< didsomeonewin(CurrentGame) << " won"<< endl;
								cout << "difference is: " << CurrentGame.calcdiff() << endl;
								switchandReplay();
								}
		}
	}
	void play(){

				if (turn == 1){
					cout << "You're player 1, ";
					cout << "Choose a move, 1 for forward, 2 for anti-clockwise, 3 for clockwise, 4 to stop.";//stop not YET implemented haha
					cin >> mve;
					CurrentGame.move(mve, CurrentGame.Aloc, CurrentGame.Adir, 1);
					turnSwitch();
					CurrentGame.printstate();
					cout << endl;
					}
				else if (turn == 2){

					Tree tempTree;
					tempTree.TreeSet(Size, DecisionTreeDepth);
					tempTree.AImove(CurrentGame, DecisionTreeDepth);
					turnSwitch();
					CurrentGame.printstate();
					Tree EmptyTree;
					tempTree = EmptyTree;
					cout << endl;

				}


	}

	int didsomeonewin(Grid CurrentGame){
		CurrentGame.calcdiff();
		int size1 = CurrentGame.sizesqr/2;
		if (CurrentGame.Anum > size1) {
			ANumOfwins++;
			return 1;
		}
		else if (CurrentGame.Bnum > size1) {
			BNumOfwins++;
			return 2;
		}
		else return 0;
	}
	void turnSwitch(){
		if (turn == 1) turn = 2;
		else if (turn == 2) turn = 1;
	}

	int numberSwitch(int number){
		if (number == 1) return 2;
		if (number == 2) return 1;
	}
	void switchandReplay(){
		cout << "A won: " << ANumOfwins/3  << " times." << endl;
		cout << "B won: " << BNumOfwins/3  << " times." << endl;
		cout << "Play another game? y/n" << endl;
							char decision;
							cin >> decision;
							if (decision == 'y'){
								turn = numberSwitch(turn);
								Grid newGame; newGame.GridSet(Size); newGame.player = numberSwitch(whostarted);
								CurrentGame = newGame;
								whostarted = numberSwitch(whostarted);
								play();
							}
	}

};



#endif /* GAME_H_ */
