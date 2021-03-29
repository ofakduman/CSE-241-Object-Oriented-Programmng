#include<iostream>
#include<string>
using namespace std;


#ifndef CREATURE_H
#define CREATURE_H

class Creature
{
protected:
int type;
//a member data which defines the type
int strength;
//a member data which stores the strength
int hitpoints;
//a member data which stores the hitpoints
public:

Creature( );
// Initialize to human, 10 strength, 10 hit points
Creature(int newType, int newStrength, int newHit);
Creature(const Creature& nCreature);//copy constructor
// Initialize creature to new type, strength, hit points
// Also appropriate accessor and mutator functions
int getStrength()const{return strength;}
int getHitpoints()const{return hitpoints;}
int getType()const {return type;}
// for type, strength, and hit points
string getSpecies()const;
//a helper function which returns the creature type
int getDamage();
// Returns amount of damage this creature
// inflicts in one round of combat
};

#endif //Creature