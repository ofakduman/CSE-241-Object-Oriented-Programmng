#include<string>
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using namespace std;

#include "Creature.h"
#include "Cyberdemon.h"

Cyberdemon::Cyberdemon():Demon(1,10,10){}

Cyberdemon::Cyberdemon( int newStrength, int newHit):Demon(1, newStrength, newHit){}

Cyberdemon::Cyberdemon(const Cyberdemon& nCyberDemon):Demon(nCyberDemon){}

string Cyberdemon::getSpecies()const{return "Cyberdemon";}

int Cyberdemon::getDamage()const{	
	srand((unsigned)time(0)); 

	int damage = 0,random;
	
	damage = Demon::getDamage();
	cout << getSpecies() << " attacks for " << damage << " points!" << endl;

	return damage;}
