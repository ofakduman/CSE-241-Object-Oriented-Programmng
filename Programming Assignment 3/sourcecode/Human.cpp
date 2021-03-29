
#include<string>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;

#include "Creature.h"
#include "Human.h"

Human::Human():Creature(Creature()){}

Human::Human(int newStrength, int newHit):Creature(0, newStrength, newHit){}

Human::Human(const Human& nHuman):Creature(nHuman){}

string Human::getSpecies()const{return "Human";}

int Human::getDamage()const{	
	srand((unsigned)time(0)); 

	int damage,random;
	// All creatures inflict damage which is a
	// random number up to their strength
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;

	return damage;}
