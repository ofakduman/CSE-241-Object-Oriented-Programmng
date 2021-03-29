
#include<string>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;

#include "Creature.h"

Creature::Creature():type(0), strength(10), hitpoints(10){}
Creature::Creature(int newType, int newStrength, int newHit):type(newType), strength(newStrength),hitpoints(newHit){}

Creature::Creature(const Creature& nCreature){
	strength = nCreature.getStrength();
	hitpoints = nCreature.getHitpoints();
	type = nCreature.getType();
}

string Creature::getSpecies()const
{
	switch (type)
	{
	case 0: return "Human";
	case 1: return "Cyberdemon";
	case 2: return "Balrog";
	case 3: return "Elf";
	}
	return "Unknown";
}

int Creature::getDamage()
{
	srand((unsigned)time(0)); 

	int damage,random;
	// All creatures inflict damage which is a
	// random number up to their strength
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;
	// Demons can inflict damage of 50 with a 5% chance
	if ((type = 2) || (type == 1)){
		random = (rand() % 20);
		if (random == 10)//The chance of the come 10 is equal to %5
			damage+=50;
	}
	// Elves inflict double magical damage with a 10% chance
	if (type == 3)
	{
		random = (rand() % 10);
		if (random == 5){//The chance of the come 5 is equal to %10
			damage += damage/10;
		}
	}
	// Balrogs are so fast they get to attack twice
	if (type == 2)
		damage*=2;

	return damage;
}