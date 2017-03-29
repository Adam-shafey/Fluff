/*
 * Tree.h
 *
 *  Created on: Dec 1, 2016
 *      Author: abdo_
 */

#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include "Grid.h"
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>


using namespace std;

class Tree {
public:
	int levels;//how many levels deep do you want to generate this tree?
	vector<Grid> GameTree;
	int TurnAorB; // 1 for A, 2 for B
	int depth; //noOfTurns with the start being 1
	int currentparent; //to control which parent is being used for generating children
	int index; // current index for generation in the vector
	int size; //gridsize
	int totalnumbreofnodes;

	Tree(){
			levels=2;//how many levels deep do you want to generate this tree?
			GameTree.resize(1);
			TurnAorB = 2; // 1 for A, 2 for B
			depth = 1; //noOfTurns with the start being 1
			currentparent = 0; //to control which parent is being used for generating children
			index = 1; // current index for generation in the vector
			size = 3; //gridsize
			totalnumbreofnodes = 1;
	}
	~Tree(){

	}

	void AImove(Grid &currentGame, int TreeLevel){

		clock_t startTime = clock();

		TreeSetFromPreviousGame(currentGame.size,TreeLevel,currentGame);
		GenerateTree();

		clock_t endtime = clock();
		cout << "Time to generate tree: " << endtime - startTime << endl;

		int EvalResult = Evaluate();



		currentGame.move(EvalResult, currentGame.Bloc,currentGame.Bdir, 2);
	}
	void TreeSet(int s, int lvl){//s being size of grid, lvl being how many levels to generate
		levels = lvl;
		size = s;
		totalnumbreofnodes = (pow(3,(lvl+1))-1)/2;
		GameTree.resize(totalnumbreofnodes);
		GameTree[0].GridSet(s);
	}
	void TreeSetFromPreviousGame(int s, int lvl, Grid currentGame){//s being size of grid, lvl being how many levels to generate
			levels = lvl;
			size = s;
			totalnumbreofnodes = (pow(3,(lvl+1))-1)/2;
			GameTree.resize(totalnumbreofnodes);
			GameTree[0] = currentGame;
		}

	void GenerateTree(){
		if (index < totalnumbreofnodes){
			int nodesatdepth = pow(3,depth-1);
			for (int switchturn = 0; switchturn < nodesatdepth; switchturn++){
				for (int i = 1; i<=3; i++){
							GenerateNode(index, TurnAorB,i,currentparent);
							index++;
				}
			currentparent++;
			}
			//to switch players once end of level/depth is reached

			if (TurnAorB == 1) {TurnAorB = 2; }
				else {TurnAorB = 1;}
			//go to the next depth by recursively calling the function generatetree
			depth++;
			GenerateTree();
		}

	}


	void GenerateNode(int index, int player, int move, int parentIndex){//player 1 or 2, move 1, 2, 3, Index of parent to generate child from
		GameTree[index] = GameTree[parentIndex];
		GameTree[index].parentnode = parentIndex;
		GameTree[index].player=player;
		if (player == 1) GameTree[index].move(move, GameTree[index].Aloc,GameTree[index].Adir, player);
		if (player == 2) GameTree[index].move(move, GameTree[index].Bloc,GameTree[index].Bdir, player);
		//GameTree[index].printstate(); cout << endl; //for testing purposes
	}

	int Evaluate(){
		clock_t startTime = clock();

		int realindex = index-1;//because the index doesn't really work like an index in the other functions
		for (int l = 0; l<levels; l++){
			int numberofclustersatdepth = pow(3,depth-1)/3;
			for (int i = 0; i < numberofclustersatdepth; i++){
							int node1val=0;
							int node2val=0;
							int node3val=0;
							if (l<1){

						//	cout << "Current index is:  " << realindex << "  " << endl; // for testing

							node1val=heuristic(GameTree[realindex]);
						//	cout << "I'm node 1, my val is" << node1val << endl; // for testing
							node2val=heuristic(GameTree[--realindex]);
						//	cout << "I'm node 2, my val is" << node2val<< endl; // for testing
							node3val=heuristic(GameTree[--realindex]);
						//	cout << "I'm node 3, my val is" << node3val<< endl; // for testing
							realindex--;
							}
							else {
								//cout << "Current index is:  " << realindex << "  " << endl; // for testing

								node1val = GameTree[realindex].MinMaxVal;
							//	cout << "I'm node 1, my val is" << node1val<< endl; // for testing
								node2val = GameTree[--realindex].MinMaxVal ;
							//	cout << "I'm node 2, my val is" << node2val<< endl; // for testing
								node3val = GameTree[--realindex].MinMaxVal;
							//	cout << "I'm node 3, my val is" << node3val<< endl; // for testing
								realindex--;
								}

							if (TurnAorB==1){ GameTree[GameTree[realindex+3].parentnode].MinMaxVal = maximum(node1val,node2val,node3val);
							//  cout << "max val is : " << maximum(node1val,node2val,node3val) << endl; // for testing
							}
							else if (TurnAorB==2) {GameTree[GameTree[realindex+3].parentnode].MinMaxVal = minimum(node1val,node2val,node3val);
							// cout << "min val is:" << minimum(node1val,node2val,node3val) << endl;// for testing
							}
							// cout << "value passed up is: " << GameTree[GameTree[realindex+3].parentnode].MinMaxVal << endl;// for testing
			}
			if (TurnAorB == 1) {TurnAorB = 2; }
			else {TurnAorB = 1;}
			depth--;
		}
			int MinMax1 = GameTree[1].MinMaxVal;
			int MinMax2 = GameTree[2].MinMaxVal;
			int MinMax3 = GameTree[3].MinMaxVal;
			int maxholder = maximum(MinMax1,MinMax2,MinMax3);

			if (MinMax1 == maxholder){

				if (MinMax2 > MinMax3 && GameTree[0].canMoveForward (GameTree[0].Bloc, GameTree[0].Bdir, 2) == false) return 2;
				else if (MinMax2 < MinMax3 && GameTree[0].canMoveForward (GameTree[0].Bloc, GameTree[0].Bdir, 2) == false) return 3;
				else if (MinMax2 == MinMax3 && GameTree[0].canMoveForward (GameTree[0].Bloc, GameTree[0].Bdir, 2) == false) return 2;

			}
			clock_t endtime = clock();
			cout << "Time to evaluate tree: " << endtime - startTime << endl;
			if (maxholder == MinMax1) return 1;
			else if (maxholder == MinMax2) return 2;
			else if (maxholder == MinMax3) return 3;

	}
	int heuristic(Grid CurrentGame){
//		int Aval=0;
//		int Bval=0;
//		int diff;
//		int tempdfromcenter;
//		for (int i=0; i <CurrentGame.sizesqr; i++ ){
//					if (CurrentGame.GameState[i].isAorBT ==1 || CurrentGame.Aloc == i) {
//						tempdfromcenter = 1+ abs(((CurrentGame.center+1)%CurrentGame.size) - ((i+1)%(CurrentGame.size)));
//						Aval = Aval - tempdfromcenter;
//					}
//					if (CurrentGame.GameState[i].isAorBT == 2 || CurrentGame.Bloc == i) {
//						tempdfromcenter = 1+ abs(((CurrentGame.center+1)%CurrentGame.size) - ((i+1)%(CurrentGame.size)));
//						Bval = Bval - tempdfromcenter;
//					}
//				}
//		diff = Bval - Aval;
//		return diff;

		return CurrentGame.calcdiff();
	}
	int maximum(int x, int y, int z) {
		int max = x; /* assume x is the largest */

		if (y > max) { /* if y is larger than max, assign y to max */
			max = y;
		} /* end if */

		if (z > max) { /* if z is larger than max, assign z to max */
			max = z;
		} /* end if */

		return max; /* max is the largest value */
	} /* end function maximum */

	int minimum(int x, int y, int z) {
		int min = x; /* assume x is the smallest */

		if (y < min) { /* if y is smaller than min, assign y to min */
			min = y;
		} /* end if */

		if (z < min) { /* if z is smaller than min, assign z to min */
			min = z;
		} /* end if */

		return min; /* min is the smallest value */
	} /* end function minimum */



	};
#endif /* TREE_H_ */
