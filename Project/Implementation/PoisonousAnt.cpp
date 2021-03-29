#include <iostream>
#include "PoisonousAnt.h"
using namespace std;

PoisonousAnt::PoisonousAnt():Ant(){
    setSymbol('c');
    setPosinous(true);
    setSurviveStepToBreed(4);
}
PoisonousAnt::PoisonousAnt(char nSymbol, int nRow, int nColoumn, int stepToBreed):Ant(nSymbol, nRow, nColoumn,4){
    setSurviveStepToBreed(4);
    setPosinous(true);
}

void PoisonousAnt::die(){
    setRow(-1);
    setColoumn(-1);
    setAlive(false);
    setSurviveStepToBreed(4);
    setPosinous(true);//not necessery
}

void PoisonousAnt::move(Organism* gridArray[numOfRows][numOfColumns],Organism emptyAreas[numOfRows][numOfColumns],Ant ant[],Ant* pPAnt[], PoisonousAnt PAnt[]){
	if (getIsAlive()==true)
	{
		Ant::move(gridArray, emptyAreas, ant, pPAnt);																						
		isBreed(gridArray, PAnt);
	}
}

int findValidIdForPAnt(PoisonousAnt PAnt[]){
    for (int i = 0; i < numOfRows*numOfColumns; ++i)
    {
        if (PAnt[i].getIsAlive() == false)
            return i;
    }
    
    return -1;
}

void setPAntToGrid(Organism* gameSpace[][numOfColumns],PoisonousAnt PAnt[], int targetRow, int targetColumn, int id ){
    gameSpace[targetRow][targetColumn]->die();
    gameSpace[targetRow][targetColumn] = &PAnt[id];
    PAnt[id].setRow(targetRow);
    PAnt[id].setColoumn(targetColumn);
    PAnt[id].setAlive(true);
}

void PoisonousAnt::isBreed(Organism* gameSpace[numOfRows][numOfColumns], PoisonousAnt PAnt[]){
    
    if (surviveStepToBreed == 0)//time to breed
    {   int id;

            id = findValidIdForPAnt(PAnt);

            if (id == -1)//means there is not any valid ant already grid full of ant
                exit(0);

            if (row-1>=0 && gameSpace[row-1][column]->getSymbol() == '-')
                setPAntToGrid(gameSpace, PAnt, row-1, column,id);

            else if (row+1<numOfRows && gameSpace[row+1][column]->getSymbol() == '-')
                setPAntToGrid(gameSpace, PAnt, row+1, column,id);

            else if (column-1>=0 && gameSpace[row][column-1]->getSymbol() == '-')
                setPAntToGrid(gameSpace, PAnt, row, column-1,id);

            else if (column+1<numOfColumns && gameSpace[row][column+1]->getSymbol() == '-')
                setPAntToGrid(gameSpace, PAnt, row, column+1,id);

            else if (row-1>=0 && gameSpace[row-1][column]->getSymbol() == 'o')
                setPAntToGrid(gameSpace, PAnt, row-1, column,id);

            else if (row+1<numOfRows && gameSpace[row+1][column]->getSymbol() == 'o')
                setPAntToGrid(gameSpace, PAnt, row+1, column,id);

            else if (column-1>=0 && gameSpace[row][column-1]->getSymbol() == 'o')
                setPAntToGrid(gameSpace, PAnt, row, column-1,id);

            else if (column+1<numOfColumns && gameSpace[row][column+1]->getSymbol() == 'o')
                setPAntToGrid(gameSpace, PAnt, row, column+1,id);             

    	    setSurviveStepToBreed(4);
    }

    else
        surviveStepToBreed--;
}


