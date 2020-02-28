/*													**
** 				HW 5 								**
**													**
** Author: 		Omer Faruk AKDUMAN					**
** School number:	1801042094						**
** 		 										 	**
**													**
*/////////////////////////////////////////////////////

#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include<iostream>
#include<fstream>
#include<vector>
#include"abstractboard.h"

using namespace std;




class BoardArray2D : public AbstractBoard
{
public:
	BoardArray2D();
	BoardArray2D(int size);
	BoardArray2D(int length, int width);
	BoardArray2D( BoardArray2D& );						//copy constructor

	int getLength()const{return length;}
	int getWidth()const{return width;}
	static int NumberOfBoards();
	char lastMove()const{return last_move;}
	void setSize(int);
	friend ostream& operator <<(ostream& ,const BoardArray2D&);
	BoardArray2D& operator =(BoardArray2D&);
	int operator ()(int ,int );
	void print();
	void readFromFile(char*argv[],int argc=0);
	void writeToFile()const;
	void move(char);
	void reset();
	bool isSolved()const;
	void moveRandom();
	void shuffle();
	void intellegent();
	void solvePuzzle();
	friend bool operator ==(const BoardArray2D&, const BoardArray2D& );
	int numberOfMoves()const{return moves;}
	void deleteArr();
	void fillWithOrdered();
	void find_location(int [])const;	//finds empty cell in the board
	int total_zeros(int );
	Directions find_direction(int ,int , int , int );
	bool Is_loop(Directions direction);	//when intellegent moves checks whether looping or not


	
	void finds_zeros_in_board();
	~BoardArray2D();




private:
	int **board;
	int width = 0, length = 0;

	int zeros[9][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};			//zeros in the board
	int loop[2]={-1,-1};				//intellegent ta donguye loopa girip girmedigini check ediyor
	static int number_of_boards ;
	int moves = 0;
	char last_move = 'S';

};

int BoardArray2D::number_of_boards = 0;

#endif