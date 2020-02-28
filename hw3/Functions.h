/*													**
** 				HW 3 								**
**													**
** Author: 		Omer Faruk AKDUMAN					**
** School number:	1801042094						**
** 		 										 	**
**													**
*/////////////////////////////////////////////////////



#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include<fstream>
using namespace std;

typedef enum {Up, Down, Right, Left}Directions;

class Board;

class NPuzzle
{
	
private:
	class Board
	{
	public:
		Board(){size_x=-1; size_y=-1;}
		void setsize();
		void readFromFile(char*argv[],int argc=0);
		void fill_with_minus1();
		bool is_board_not_square()const;
		void print()const;
		void fill_with_ordered();
		int getsize()const;
		bool isSolved()const;
		void move(Directions);
		void find_location(int []);
		void finds_zeros_in_board(int [][2]);
		void writeToFile()const;
		void intellegent(int [],int [][2]);
		int total_zeros(int,int [][2]);
		Directions find_direction(int ,int , int , int );
		bool Is_loop(Directions,int []);
		void moveRandom();
	private:
		int board[9][9];
		int size_x;		//x and y axis
		int size_y;		//if board is square or not loaded from file size_y will be -1
	};
public:
	void print();
	int getsize(const Board& board);
	void setsize();
	void menu(int argc, char*argv[]);
	void shuffle(NPuzzle::Board& );
	void writeToFile(const Board&)const;
	void moveIntelligent(NPuzzle::Board&, int [][2],int []);
	void solvePuzzle(Board& board,int [][2],int [],int& move_counter);
};


#endif
