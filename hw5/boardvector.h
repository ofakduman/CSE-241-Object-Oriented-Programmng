/*													**
** 				HW 5 								**
**													**
** Author: 		Omer Faruk AKDUMAN					**
** School number:	1801042094						**
** 		 										 	**
**													**
*/////////////////////////////////////////////////////

#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

#include<iostream>
#include<fstream>
#include<vector>
#include"abstractboard.h"

using namespace std;


class BoardVector: public AbstractBoard
{
public:
	BoardVector();
	BoardVector(int size);
	BoardVector(int length, int width);

	int getBoardWidth()const{return width;}
	int getBoardLength()const{return length;}
	static int NumberOfBoards();
	char lastMove()const{return last_move;}
	void setSize(int);
	void print();
	friend ostream& operator <<(ostream& ,const BoardVector&);
	void readFromFile(char*argv[],int argc=0);
	void writeToFile()const;
	void shuffle();
	void moveRandom();
	void move(char);
	void reset();
	bool isSolved()const;
	void intellegent();
	void solvePuzzle();
	friend bool operator ==(const BoardVector&, const BoardVector& );
	int numberOfMoves()const{return moves;}
	int operator ()(int ,int );
	void fillWithOrdered();
	void find_location(int [])const;	//finds empty cell in the board
	void finds_zeros_in_board();
	int total_zeros(int );
	Directions find_direction(int ,int , int , int );
	bool Is_loop(Directions direction);	//when intellegent moves checks whether looping or not

private:
	vector<vector<int>> board;
	int width = 0, length = 0;
	int zeros[9][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};			//zeros in the board
	int loop[2]={-1,-1};				//intellegent ta donguye loopa girip girmedigini check ediyor
	static int number_of_boards ;
	int moves = 0;
	char last_move = 'S';
};
int BoardVector::number_of_boards = 0;

#endif