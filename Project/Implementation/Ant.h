#include <iostream>
#include "Organism.h"

using namespace std;

#ifndef ANT_H
#define ANT_H

class PoisounousAnt;

class Ant: public Organism{
public:
    Ant();//default constructor
    Ant(char nSymbol, int nRow, int nColoumn, int stepToBreed);//parameter constructor
    
    bool mutation();
    //Polymorphism
    virtual void die();
    virtual void move(Organism* gridArray[numOfRows][numOfColumns],Organism emptyAreas[numOfRows][numOfColumns],Ant [], Ant* pPAnt[]);
    virtual void isBreed(Organism* gameSpace[numOfRows][numOfColumns],Ant ant[],Ant* pPAnt[]);
};

#endif//Ant