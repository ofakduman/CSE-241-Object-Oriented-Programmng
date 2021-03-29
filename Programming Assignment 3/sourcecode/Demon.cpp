#include<string>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;

#include "Creature.h"
#include "Demon.h"

Demon::Demon():Creature(Creature(1,10,10)){}

Demon::Demon(int nType ,int newStrength, int newHit):Creature(nType, newStrength, newHit){}

Demon::Demon(const Demon& nDemon):Creature(nDemon){}

string Demon::getSpecies()const{return "Demon";}

int Demon::getDamage()const{	
	srand((unsigned)time(0)); 

	int damage,random;
	damage = (rand() % strength) + 1;
	random = (rand() % 20);
	if (random == 10)//The chance of the come 10 is equal to %5
		damage+=50;

	return damage;}
