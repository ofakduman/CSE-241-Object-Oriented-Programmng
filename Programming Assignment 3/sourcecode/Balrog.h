#include<iostream>
#include<string>
using namespace std;
#include"Demon.h"


#ifndef BALROG_H
#define BALROG_H

class Balrog:public Demon
{
public:
	Balrog();
	Balrog(int newStrength, int newHit);
	Balrog(const Balrog& nBalrog);
	string getSpecies()const;
	int getDamage()const;
};

#endif //Cyberdemon