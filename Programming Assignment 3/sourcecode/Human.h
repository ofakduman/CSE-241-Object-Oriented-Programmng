#include<iostream>
#include<string>
#include"Creature.h"
using namespace std;


#ifndef HUMAN_H
#define HUMAN_H

class Human: public Creature
{
public:
	Human();
	Human(int newStrength, int newHit);
	Human(const Human& nHuman);
	string getSpecies()const;
	int getDamage()const;
};



#endif //Human