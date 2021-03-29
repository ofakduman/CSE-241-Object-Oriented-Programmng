#include <iostream>
#include "Organism.h"

using namespace std;

#ifndef DOODLEBUG_H
#define DOODLEBUG_H


class Doodlebug: public Organism{
public:
    Doodlebug();//default constructor
    Doodlebug(char nSymbol, int nRow, int nColoumn, int stepToBreed);//parameter constructor
    //Getters
    int getLives()const{return live;}
    bool getPosinous()const{return isPosinous;}
    //Setters
    void setLives(int nLives);
    void setPosinous(bool nPosinous);
    //member function
    void eat(char ch);
    virtual void die();
    //Polymorphism
    virtual void move(Organism* gridArray[numOfRows][numOfColumns],Organism emptyAreas[numOfRows][numOfColumns],Doodlebug []);
    virtual void isBreed(Organism* gameSpace[numOfRows][numOfColumns],Doodlebug doodlebugs[]);
private:
    int live;//if a doodlebug hasnot eaten an ant within the last three steps, it will die
};

#endif//Doodlebug
