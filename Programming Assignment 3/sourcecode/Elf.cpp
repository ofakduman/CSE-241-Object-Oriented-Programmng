#include<string>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;

#include "Creature.h"
#include "Elf.h"

Elf::Elf():Creature(Creature(3,10,10)){}

Elf::Elf( int newStrength, int newHit):Creature(3, newStrength, newHit){}

Elf::Elf(const Elf& nElf):Creature(nElf){}

string Elf::getSpecies()const{return "Elf";}

int Elf::getDamage()const{	
	srand((unsigned)time(0)); 

	int damage,random;
	// All creatures inflict damage which is a
	// random number up to their strength
	damage = (rand() % strength) + 1;

	random = (rand() % 10);
	if (random == 5){//The chance of the come 5 is equal to %10
		damage += damage/10;
	}
	
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	
	return damage;}
