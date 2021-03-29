#include<string>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;

#include "Creature.h"
#include "Balrog.h"

Balrog::Balrog():Demon(2,10,10){}

Balrog::Balrog( int newStrength, int newHit):Demon(2, newStrength, newHit){}

Balrog::Balrog(const Balrog& nBalrog):Demon(nBalrog){}

string Balrog::getSpecies()const{return "Balrog";}

int Balrog::getDamage()const{	
	srand((unsigned)time(0)); 

	int damage = 0,random;
	
	damage = Demon::getDamage();

	damage*=2;//balrogs so fast so they atacks twice

	cout << getSpecies() << " attacks for " << damage << " points!" << endl;

	return damage;}
