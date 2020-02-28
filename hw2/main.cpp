#include "Functions.h"
#include <iostream>
#include "Functions.cpp"
#include<fstream>
#include<cstdlib>
#include<ctime>


int main(int argc, char*argv[])
{
	srand(time(NULL));

		
	int board[9][9], size[2]={-1,-1};
	if (argc > 1)						//for command line
		load_board(board,size,argv[1]);

	menu(board,size);


	return 0;
}
