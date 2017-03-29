/*
 * Grid.h
 *
 *  Created on: Nov 21, 2016
 *      Author: abdo_
 */

#ifndef GRID_H_
#define GRID_H_

#include <iostream>
#include <string>
#include "State.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;


class Grid {
public:
	int size;
	int Aloc;
	int Bloc;
	int Adir;//1-left, 2-up, 3-right, 4-down, 0 is null
	int Bdir;//1-left, 2-up, 3-right, 4-down, 0 is null
	int player=1;
	int Anum;
	int Bnum;
	int diff;
	int MinMaxVal;
	int winAorB; // 1 = A  2 = B
	int sizesqr;
	int parentnode;
	int center;

	vector<State> GameState;
	vector<int> left;
	vector<int> top;
	vector<int> right;
	vector<int> bottom;




	void play(){
		int turn;
		int playagain;
		if (player == 1) cout << "You're player 1, ";
		if (player == 2) cout << "You're player 2, ";
		cout << "Choose a move, 1 for forward, 2 for anti-clockwise, 3 for clockwise, 4 to stop.";
		cin >> turn;
		if (player == 1) {
			move(turn, Aloc, Adir, 1);
			player = 2;
		}
		else if (player == 2) {
			move(turn, Bloc, Bdir, 2);
			player = 1;
		}
		if (turn != 4){
		printstate();
		//calcdiff();
		cout << "Anum is: " << Anum << "Bnum is: " << Bnum <<endl;
		play();
		}


	}
	Grid(){//n = size of grid
		Anum=1;
		Bnum=1;
		diff=0;
		winAorB = 0;
		parentnode = 0;
		MinMaxVal = 0;
		int n = 3;
		size = n;
		sizesqr= pow(size, size);
		center = 0.5*n+0.5  +  n*(0.5*n-0.5);
			Aloc = center-1;
			Bloc = center+1;
			Adir = 1;//1-left, 2-up, 3-right, 4-down, 0 is null
			Bdir = 3 ;//1-left, 2-up, 3-right, 4-down, 0 is null
			left.resize(size);
							top.resize(size);
							right.resize(size);
							bottom.resize(size);
		}
	~Grid(){
	}

	void GridSet(int n){//n = size of grid
			size=n;
			center = 0.5*n-0.5  +  n*(0.5*n-0.5);
				Aloc = center-1;
				Bloc = center+1;
				Adir = 1;//1-left, 2-up, 3-right, 4-down, 0 is null
				Bdir = 3 ;//1-left, 2-up, 3-right, 4-down, 0 is null
				sizesqr = size*size;
				GameState.resize(sizesqr);
				State temparr[sizesqr];
				copy(temparr,temparr+(sizesqr),GameState.begin());
				left.resize(size);
				top.resize(size);
				right.resize(size);
				bottom.resize(size);

				GameState[Aloc].changestate(false,0);
				GameState[Bloc].changestate(false,0);
				for (int i=1;i<=n; i++){//(1 to 9)
					left[i-1] =		(i-1)*n;
					top[i-1] =		i-1;
					right[i-1] =	(n-1)+((i-1)*n);
					bottom[i-1] =	n*(n-1)+i;

				}
				//calcdiff();
			}

	void move(int a, int &loc, int &dir, int player){
		if (a == 1){//try forward
			gridforwardsize(loc, dir, player, size);
		}

		else if (a == 2){//turn left
			dir = turn(dir, a);
		}

		else if (a == 3){//turn right
			dir = turn(dir, a);
		}
		//calcdiff();
		//cout << "diff is" << diff << endl; for testing
		//if (player == 1 ) player = 2;
		//else if (player == 2 ) player = 1;
	}

	int calcdiff(){
		int tempAnum=0;
		int tempBnum=0;
		for (int i=0; i <sizesqr; i++ ){
			if (GameState[i].isAorBT == 1 || Aloc == i) tempAnum++;
			if (GameState[i].isAorBT == 2 || Bloc == i) tempBnum++;
		}
		Anum = tempAnum;
		Bnum = tempBnum;
		diff = Bnum - Anum;
		if (Anum > (sizesqr/2)) winAorB = 1;
		if (Bnum > (sizesqr/2)) winAorB = 2;
		//printstate();//for testing purpose
		return diff;
	}

	bool IsEmpty(int loc, int player){//to ensure that forward step doesn't contain other players trace
		if (player == 1 && GameState[loc].isAorBT == 1) return true;
		if (player == 1 && GameState[loc].isAorBT == 2) return false;
		if (player == 1 && GameState[loc].isfree == 1) return true;
		if (player == 2 && GameState[loc].isAorBT == 1) return false;
		if (player == 2 && GameState[loc].isAorBT == 2) return true;
		if (player == 2 && GameState[loc].isfree == 1) return true;
	}

	int turn(int dir, int LorR){//LorR, 2 = left(anti-clockwise), 3 = Right(clockwise)
		if (LorR == 2 && dir != 1) dir-- ;
		else if (LorR == 3 && dir != 4) dir++ ;
		else if (dir == 1 && LorR == 2) dir = 4;
		else if (dir == 4 && LorR == 3) dir = 1;

		return dir;
	}

 	void printstate(){
 		int pos;
 		for (int i = 0; i<size; i++){//row number
 			for (int j = 0; j<size; j++){ // position number
					pos = j+i*size;
 				if (pos == (Bloc)){
 					print(2, pos);
 					cout << "\t";
 				}
 				else{
 					print(1, pos);
 					cout << "\t";
 				}
 			}
			cout << endl;

 		}
 	}
	void print(int player, int loc){//dependent on the grid function of print
		if (GameState[loc].isfree == false) {

			if (Adir == 1 && player == 1) {cout << "x"<< "<";}
			else if (Adir == 2 && player == 1) {cout << "x"<< "^";}
			else if (Adir == 3 && player == 1) {cout << "x"<< ">";}
			else if (Adir == 4 && player == 1) {cout << "x"<< "v";}

			if (Bdir == 1 && player == 2) cout << "<"<< "o";
			else if (Bdir == 2 && player == 2) cout << "^"<< "o";
			else if (Bdir == 3 && player == 2) cout << ">"<< "o";
			else if (Bdir == 4 && player == 2) cout << "v"<< "o";
		}
		else if (GameState[loc].isAorBT == 1 && GameState[loc].isfree == true) {cout << "x";}
		else if (GameState[loc].isAorBT == 2 && GameState[loc].isfree == true) {cout << "o";}
		else if (GameState[loc].isfree == true && GameState[loc].isAorBT == 0) {cout << "-";}
	}
	void gridforwardsize(int &loc, int dir, int player, int n/*size*/){
		int loc1 = loc-1;
		int loc2 = loc-n;
		int loc3 = loc+1;
		int loc4 = loc+n;

		if(isTryingToMoveIntoEdge(loc, dir)==false){
			if(dir==1 && (IsEmpty((loc1), player)) == true) {
						GameState[loc].isAorBT=player;
						GameState[loc].isfree=true;
						loc--;
						GameState[loc].isfree=false;
			}
			if(dir==2 && (IsEmpty((loc2), player)) == true) {
				GameState[loc].isAorBT=player;
				GameState[loc].isfree=true;
				loc=loc-n;
				GameState[loc].isfree=false;
	}
			if(dir==3 && (IsEmpty((loc3), player)) == true) {
				GameState[loc].isAorBT=player;
				GameState[loc].isfree=true;
				loc++;
				GameState[loc].isfree=false;
	}
			if(dir==4 && (IsEmpty((loc4), player)) == true){
				GameState[loc].isAorBT=player;
				GameState[loc].isfree=true;
				loc=loc+n;
				GameState[loc].isfree=false;
	}
		}
	}
	bool isTryingToMoveIntoEdge(int loc, int dir){
		if(find(left.begin(),left.end(),loc) != left.end()  && dir==1) return true;
		else if(find(top.begin(),top.end(),loc) != top.end()  && dir==2) return true;
		else if(find(right.begin(),right.end(),loc) != right.end()  && dir==3) return true;
		else if(find(bottom.begin(),bottom.end(),loc) != bottom.end()  && dir==4) return true;
		else return false;
	}

	bool canMoveForward (int loc, int dir, int player){
				int loc1 = loc-1;
				int loc2 = loc-size;
				int loc3 = loc+1;
				int loc4 = loc+size;

					if(isTryingToMoveIntoEdge(loc, dir)==false){
					if(dir==1 && (IsEmpty((loc1), player)) == true) {
								GameState[loc].isAorBT=player;
								GameState[loc].isfree=true;
								return true;
						}
					if(dir==2 && (IsEmpty((loc2), player)) == true) {
						GameState[loc].isAorBT=player;
						GameState[loc].isfree=true;
						return true;

						}
					if(dir==3 && (IsEmpty((loc3), player)) == true) {
						GameState[loc].isAorBT=player;
						GameState[loc].isfree=true;
						return true;

						}
					if(dir==4 && (IsEmpty((loc4), player)) == true){
						GameState[loc].isAorBT=player;
						GameState[loc].isfree=true;
						return true;

						}
				}
					return false;
			}

};



#endif /* GRID_H_ */
