#include "Functions.h"
#include <iostream>
#include "Functions.cpp"
#include<fstream>
#include<cstdlib>
#include<ctime>


int main(int argc, char*argv[])
{
	srand(time(NULL));
	
	NPuzzle  puzzle;
	puzzle.menu(argc,argv);

	return 0;
}
