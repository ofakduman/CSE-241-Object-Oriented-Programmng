/*										**
** 				HW 2 						**
**										**
** Author: 		Omer Faruk AKDUMAN					**
** School number:	1801042094						**
** extra: 		-added execution time in more intellegent		**
**			-optimized with (g++ -c -O3 main.cpp) 			**
**			for use less cpu in more intellegent algorithm  	**
*/////////////////////////////////////////////////////////////////////////////////		



#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include<fstream>
using namespace std;

typedef enum {Up, Down, Right, Left}Directions;

int input_size( );
//gets the size from user

void load_board(int board[9][9], int size[]);		//gets board from file and gets size
void load_board(int board[9][9],int size[2], char* name);
/*overloaded for rule of homework"Your program will accept one optional file name as a command line option."*/
void fill_with_minus1(int board[9][9]);				//fills board with minus 1
void print_board(int board[9][9], int size[]);		//prints board
void save_file(int board[9][9], int size[]);		//saves file
bool is_solved_board(int board[9][9], int size[]);	//checks whether solved or not
void fill_with_ordered(int board[][9],int size[]);	////filling with orded number for example 3x3 1 2 3\n 4 5 6\n 7 8 9

void board_operation(int board[9][9], int size[], bool loaded = false);
/*happens some board operation ,order, shuffle, checks it is solved ornet (before no input)*/
void Mix(int board[9][9], int size[], int time=3);
//mix the board according to the difficulty
void movement(int board[9][9],Directions direction ,int size[]);
//this function provides movement
void find_location(int board[][9], int size[], int location[2]);
//this function find empty cell's location
void menu(int board[][9], int size[]);
//inputs taken here (right, left, up, down,intellegent)
void get_informate();
//showing inputs and informs user
void intellegent(int size[2], int board[][9],int loop[2],int zero_counter[9][2]);
/*Intellegent function*/
void finds_zeros_in_board(int size[2], int board[][9],int zero_counter[9][2]);
int total_zeros(int location_y,int zero_counter[9][2]);	//location y is ekseni
Directions find_direction(int up,int down, int right, int left);
/*compare differences for making intellegent move*/
bool Is_loop(Directions direction,int loop[2]);
/*Checks whether there are loop or not*/








#endif
