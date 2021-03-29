#include <iostream>
#include "Ant.h"

using namespace std;


Ant::Ant():Organism(){
    symbol = 'o';
    surviveStepToBreed = 3;
}
Ant::Ant(char nSymbol, int nRow, int nColoumn, int stepToBreed):Organism(nSymbol, nRow, nColoumn){
    surviveStepToBreed = 3;
}

int findValidIdForAnt(Ant ant[]){
    for (int i = 0; i < numOfRows*numOfColumns; ++i)
    {
        if (ant[i].getIsAlive() == false)
            return i;
    }
    
    return -1;
}

int findValidIdForpPAnt(Ant* ant[]){
    for (int i = 0; i < numOfRows*numOfColumns; ++i)
    {
        if (ant[i]->getIsAlive() == false)
            return i;
    }
    
    return -1;
}

void setAntToGrid(Organism* gameSpace[][numOfColumns],Ant ant[], int targetRow, int targetColumn, int id ){
    gameSpace[targetRow][targetColumn] = &ant[id];
    ant[id].setRow(targetRow);
    ant[id].setColoumn(targetColumn);
    ant[id].setAlive(true);
}

void setpPAntToGrid(Organism* gameSpace[][numOfColumns],Ant* pPAnt[], int targetRow, int targetColumn, int id ){
    gameSpace[targetRow][targetColumn] = &(*pPAnt[id])  ;
    pPAnt[id]->setRow(targetRow);
    pPAnt[id]->setColoumn(targetColumn);
    pPAnt[id]->setAlive(true);
}


void Ant::die(){
    setRow(-1);
    setColoumn(-1);
    setAlive(false);
    setSurviveStepToBreed(3);
    setPosinous(false);
}

void Ant::move(Organism* gameSpace[numOfRows][numOfColumns], Organism emptyAreas[numOfRows][numOfColumns], Ant ant[],Ant* pPAnt[]){

    if (isAlive == true)//if ant is not Alive so ant is not in the grid cell so it can not move
    { 
        int direction = rand() % 4;//0 down, 1 up, 2 right, 3 left

        if (direction == 0)//if direction is down
        {
             if (row+1<numOfRows){//if not the boottom of the grid
                 if (gameSpace[row+1][column]->getSymbol() == '-')//means empty area 
                 {
                    gameSpace[row+1][column] = this;
                    gameSpace[row][column] = &emptyAreas[row][column];
                    row++;
                 }
            }
        } 


        else if (direction == 1)
        {
             if (row-1>=0){
                 if (gameSpace[row-1][column]->getSymbol() == '-')//means empty area 
                 {
                    gameSpace[row-1][column] = this;
                    gameSpace[row][column] = &emptyAreas[row][column];
                    row--;
                 }
            }
        }
        else if (direction == 2){
             if (column+1<numOfColumns){
                 if (gameSpace[row][column+1]->getSymbol() == '-')//means empty area 
                 {
                    gameSpace[row][column+1] = this;
                    gameSpace[row][column] = &emptyAreas[row][column];
                    column++;
                 }
            }
        }
        else if (direction == 3){
             if (column-1>=0){
                 if (gameSpace[row][column-1]->getSymbol() == '-')//means empty area 
                 {
                    gameSpace[row][column-1] = this;
                    gameSpace[row][column] = &emptyAreas[row][column];
                    column--;
                 }
            }
        }

        if (getSymbol()=='o')//if ant is not poisonous
            isBreed(gameSpace,ant,pPAnt);
    }
}

void Ant::isBreed(Organism* gameSpace[numOfRows][numOfColumns],Ant ant[],Ant* pPAnt[]){
    
    if (surviveStepToBreed == 0)//time to breed
    {   int id;

        if (!mutation()){//if mutation dont occur  
            id = findValidIdForAnt(ant);

            if (id == -1)//means there is not any valid ant already grid full of ant
                exit(0);

            if (row-1>=0 && gameSpace[row-1][column]->getSymbol() == '-')
                setAntToGrid(gameSpace, ant, row-1, column,id);

            else if (row+1<numOfRows && gameSpace[row+1][column]->getSymbol() == '-')
                setAntToGrid(gameSpace, ant, row+1, column,id);

            else if (column-1>=0 && gameSpace[row][column-1]->getSymbol() == '-')
                setAntToGrid(gameSpace, ant, row, column-1,id);

            else if (column+1<numOfColumns && gameSpace[row][column+1]->getSymbol() == '-')
                setAntToGrid(gameSpace, ant, row, column+1,id);

        }   
        
        else{//mutation is succesfully-new created ant will be mutated-

            id = findValidIdForpPAnt(pPAnt);

            if (id == -1)//means there is not any valid ant already grid full of ant
                exit(0);

            if (row-1>=0 && gameSpace[row-1][column]->getSymbol() == '-')
                setpPAntToGrid(gameSpace, pPAnt, row-1, column,id);

            else if (row+1<numOfRows && gameSpace[row+1][column]->getSymbol() == '-')
                setpPAntToGrid(gameSpace, pPAnt, row+1, column,id);

            else if (column-1>=0 && gameSpace[row][column-1]->getSymbol() == '-')
                setpPAntToGrid(gameSpace, pPAnt, row, column-1,id);

            else if (column+1<numOfColumns && gameSpace[row][column+1]->getSymbol() == '-')
                setpPAntToGrid(gameSpace, pPAnt, row, column+1,id);            
        }

    surviveStepToBreed = 3;

    }
    else
        surviveStepToBreed--;
}

bool Ant::mutation(){
   int posibility = rand() % 10000;

   if (mutationProbability  > posibility)//for example mutationProbability-> 1 = (%0.01) 
        return true;

    return false;
}

