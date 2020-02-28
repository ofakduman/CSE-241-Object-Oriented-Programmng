/*													**
** 				HW 5 								**
**													**
** Author: 		Omer Faruk AKDUMAN					**
** School number:	1801042094						**
** 		 										 	**
**													**
*/////////////////////////////////////////////////////

#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include <iostream>
#include<fstream>
#include<vector>
#include"abstractboard.h"

using namespace std;



class BoardArray1D: public AbstractBoard
{
public:
	BoardArray1D();
	BoardArray1D(int );
	BoardArray1D(int , int );
	
	static int NumberOfBoards();
	int getBoardWidth()const{return width;}
	int getBoardLength()const{return length;}
	int numberOfMoves()const{return moves;}
	char lastMove()const{return last_move;}
	void setSize(int);
	friend ostream& operator <<(ostream& ,const BoardArray1D&);
	void print();
	void readFromFile(char*argv[],int argc=0);
	void writeToFile()const;
	void moveRandom();
	void move(char);
	void shuffle();
	void reset();
	bool isSolved()const;
	int operator ()(int ,int );
	void intellegent();
	void solvePuzzle();
	friend bool operator ==(const BoardArray1D&, const BoardArray1D& );
	void fillWithOrdered();
	bool Is_loop(Directions direction);	//when intellegent moves checks whether looping or not
	int total_zeros(int );
	Directions find_direction(int ,int , int , int );
	int find_location( )const;
	~BoardArray1D();

private:
	int *board;
	int width = 0, length = 0;
	int loop[2]={-1,-1};				//intellegent ta donguye loopa girip girmedigini check ediyor
	static int number_of_boards ;
	int moves = 0;
	char last_move = 'S';
};

int BoardArray1D::number_of_boards = 0;

#endif
