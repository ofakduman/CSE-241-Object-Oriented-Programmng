#include<string>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;

#ifndef ORGANISM_H
#define ORGANISM_H


class Organism{
public:
    Organism();//default constructor
    Organism(char nSymbol, int nRow, int nColoumn);//parameter constructor
    //Getters
    int getRow() const{return row;}
    int getColoumn()const{return column;}
    bool getIsAlive()const{return isAlive;}
    char getSymbol()const{return symbol;}
    int getSurviveStepToBreed()const{return surviveStepToBreed;}
    //Setters
    void setRow(int nRow);
    void setColoumn(int nColoumn);
    void setSymbol(char nSymbol);
    void setSurviveStepToBreed(int nStep);
    void setAlive(bool aliveOrNot);
    void setPosinous(bool posinous);
    //Polymorphism
    virtual void die(){isAlive = false;}
    virtual void move(Organism* gridArray[numOfRows][numOfColumns],Organism emptyAreas[numOfRows][numOfColumns]);
    virtual void isBreed();

protected:
    char symbol;        //every creature has special ascii character
    int row;            
    int column;     
    bool breed;         //to check int this step is creature will breed
    bool isAlive;      
    int surviveStepToBreed;     //for ex. "If an ant survives for time steps"
    bool isPosinous;
};


#endif//Organism