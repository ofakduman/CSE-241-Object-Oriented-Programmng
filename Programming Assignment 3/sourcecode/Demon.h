#include<iostream>
#include<string>
using namespace std;
#include"Creature.h"

#ifndef DEMON_H
#define DEMON_H

class Demon:public Creature
{
public:
	Demon();
	Demon(int ntype,int newStrength, int newHit);
	Demon(const Demon& nDemon);
	string getSpecies()const;
	int getDamage()const;
};

#endif //Demon