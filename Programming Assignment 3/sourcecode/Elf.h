#include<iostream>
#include<string>
#include"Creature.h"
using namespace std;


#ifndef ELF_H
#define ELF_H

class Elf: public Creature
{
public:
	Elf();
	Elf( int newStrength, int newHit);
	Elf(const Elf& Elf);
	string getSpecies()const;
	int getDamage()const;
};



#endif //ElF