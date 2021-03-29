#include <iostream>
#include "Ant.h"

using namespace std;

#ifndef POISONOUSANT_H
#define POISONOUSANT_H


class PoisonousAnt: public Ant{
public:
    PoisonousAnt();//default constructor
    PoisonousAnt(char nSymbol, int nRow, int nColoumn, int stepToBreed);//parameter constructor
    
    //void mutation();
    //Polymorphism
    virtual void die();
    virtual void isBreed(Organism* gameSpace[numOfRows][numOfColumns],PoisonousAnt []); 
    
    virtual void move(Organism* gridArray[numOfRows][numOfColumns],Organism emptyAreas[numOfRows][numOfColumns],Ant [], Ant* pPAnt[], PoisonousAnt []);
};

#endif//PoisonousAnt