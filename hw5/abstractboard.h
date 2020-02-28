#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H


#include <iostream>
#include<fstream>
#include<vector>

using namespace std;

typedef enum {Up, Down, Right, Left}Directions;
class AbstractBoard
{
public:
	virtual void print() = 0;
	virtual void readFromFile(char*argv[],int argc=0) = 0;
	virtual void writeToFile()const = 0;
	virtual void reset() = 0;
	virtual void setSize(int) = 0;
	virtual void move(char) = 0;
	virtual bool isSolved()const = 0;
	virtual	int operator ()(int ,int ) = 0;
	virtual	void solvePuzzle() = 0;

	
	static int NumberOfBoards();
	virtual char lastMove() const =0;
	virtual int numberOfMoves()const = 0;
protected:
	int numberOfallBoard;
};

#endif