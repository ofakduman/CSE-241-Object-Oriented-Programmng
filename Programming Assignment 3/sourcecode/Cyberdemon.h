#include<iostream>
#include<string>
using namespace std;
#include"Demon.h"


#ifndef CYBERDEMON_H
#define CYBERDEMON_H

class Cyberdemon:public Demon
{
public:
	Cyberdemon();
	Cyberdemon(int newStrength, int newHit);
	Cyberdemon(const Cyberdemon& Cyberdemon);
	string getSpecies()const;
	int getDamage()const;
};

#endif //Cyberdemon