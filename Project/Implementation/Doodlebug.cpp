#include <iostream>
#include "Doodlebug.h"
using namespace std;

Doodlebug::Doodlebug():Organism(){
    symbol = 'x';
    surviveStepToBreed = 8;
    live = 4;
    isPosinous = false;
}
Doodlebug::Doodlebug(char nSymbol, int nRow, int nColoumn, int stepToBreed):Organism(nSymbol, nRow, nColoumn){
    surviveStepToBreed = 8;
    live = 4;
    isPosinous = false;
}

void Doodlebug::setLives(int nLives){
    live = nLives;
}

void Doodlebug::setPosinous(bool nPosinous){
    isPosinous = nPosinous;
}

void Doodlebug::eat(char ch){
    
    if (isPosinous == false)
    {
        if (ch == 'o'){//'o' normal ant
            setLives(3);
        }

        else if (ch == 'c'){//'c' posinous ant
            setLives(2);
            setPosinous(true);
        }
    }
}

void Doodlebug::die(){
    setRow(-1);
    setColoumn(-1);
    setAlive(false);
    setSurviveStepToBreed(8);
    setPosinous(false);
    setLives(4);

}
void Doodlebug::move(Organism* gameSpace[numOfRows][numOfColumns], Organism emptyAreas[numOfRows][numOfColumns], Doodlebug doodlebugs[]){

    if (isAlive == true)
    { 
        int direction = rand() % 4;//0 down, 1 up, 2 right, 3 left

        if (direction == 0)
        {
             if (row+1<numOfRows){
                 if (gameSpace[row+1][column]->getSymbol() == '-')//means empty area 
                 {
                    gameSpace[row+1][column] = this;
                    gameSpace[row][column] = &emptyAreas[row][column];
                    row++;
                 }
                 else if (gameSpace[row+1][column]->getSymbol() == 'o' || gameSpace[row+1][column]->getSymbol() == 'c')//o means ant c means 
                {
                    eat(gameSpace[row+1][column]->getSymbol());//symbol represents wich kind of ant
                    gameSpace[row+1][column]->die();
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
                else if (gameSpace[row-1][column]->getSymbol() == 'o' || gameSpace[row-1][column]->getSymbol() == 'c')/*o means ant c means*/ {
                eat(gameSpace[row-1][column]->getSymbol());//symbol represents wich kind of ant
                gameSpace[row-1][column]->die();
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
                else if (gameSpace[row][column+1]->getSymbol() == 'o' || gameSpace[row][column+1]->getSymbol() == 'c')/*o means ant c means*/ {
                eat(gameSpace[row][column+1]->getSymbol());//symbol represents wich kind of ant
                gameSpace[row][column+1]->die();
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
                else if (gameSpace[row][column-1]->getSymbol() == 'o' || gameSpace[row][column+1]->getSymbol() == 'c')/*o means ant c means*/ {
                    eat(gameSpace[row][column-1]->getSymbol());//symbol represents wich kind of ant
                    gameSpace[row][column-1]->die();
                    gameSpace[row][column-1] = this;
                    gameSpace[row][column] = &emptyAreas[row][column];
                    column--;
                }
            }
        }

        live--;
        if (getLives() == 0)
        {
            gameSpace[row][column] = &emptyAreas[row][column];
            die();
        }
        else
            isBreed(gameSpace,doodlebugs);
    }
}
int findValidIdForDoodlebug(Doodlebug doodlebugs[]){
    for (int i = 0; i < numOfRows*numOfColumns; ++i)
    {
        if (doodlebugs[i].getIsAlive() == false)
            return i;
    }
    
    return -1;
}

void setDoodlebugsToGrid(Organism* gameSpace[][numOfColumns],Doodlebug doodlebugs[], int targetRow, int targetColumn, int id ){
    gameSpace[targetRow][targetColumn] = &doodlebugs[id];
    doodlebugs[id].setRow(targetRow);
    doodlebugs[id].setColoumn(targetColumn);
    doodlebugs[id].setLives(4);
    doodlebugs[id].setAlive(true);
}

void Doodlebug::isBreed(Organism* gameSpace[numOfRows][numOfColumns],Doodlebug doodlebugs[]){
    if (surviveStepToBreed == 0)//time to breed
    {
        int id = findValidIdForDoodlebug(doodlebugs);

        if (id == -1)//means there is not any valid ant already grid full of ant
            exit(0);

        if (row-1>=0 && gameSpace[row-1][column]->getSymbol() == '-')
            setDoodlebugsToGrid(gameSpace, doodlebugs, row-1, column,id);

        else if (row+1<numOfRows && gameSpace[row+1][column]->getSymbol() == '-')
            setDoodlebugsToGrid(gameSpace, doodlebugs, row+1, column,id);

        else if (column-1>=0 && gameSpace[row][column-1]->getSymbol() == '-')
            setDoodlebugsToGrid(gameSpace, doodlebugs, row, column-1,id);

        else if (column+1<numOfColumns && gameSpace[row][column+1]->getSymbol() == '-')
            setDoodlebugsToGrid(gameSpace, doodlebugs, row, column+1,id);

         surviveStepToBreed = 8;
    }

    surviveStepToBreed--;

}

