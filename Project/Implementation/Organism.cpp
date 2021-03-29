#include <iostream>
#include "Organism.h"
using namespace std;

Organism::Organism():symbol('-'), row(-1), column(-1), breed(false), isAlive(false), surviveStepToBreed(0){}

Organism::Organism(char nSymbol, int nRow, int nColoumn):symbol(nSymbol), row(nRow), column(nColoumn), breed(true), isAlive(true),surviveStepToBreed(0){}

void Organism::setRow(int nRow){
    row = nRow; 
}

void Organism::setColoumn(int nColoumn){
    column = nColoumn;
}

void Organism::setSymbol(char nSymbol){
    symbol = nSymbol;
}

void Organism::setSurviveStepToBreed(int nStep){
    surviveStepToBreed = nStep;
}

void Organism::setAlive(bool aliveOrNot){
    isAlive = aliveOrNot;
}

void Organism::setPosinous(bool posinous){
    isPosinous = posinous;
}
void Organism::move(Organism* gridArray[numOfRows][numOfColumns],Organism emptyAreas[numOfRows][numOfColumns]){
}

void Organism::isBreed(){
}