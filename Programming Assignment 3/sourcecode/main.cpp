#include<iostream>
using namespace std;
#include<string>
#include "headers.h"

int main(int argc, char const *argv[])
{
	Creature creature_human;
	Human human(98,77);
	Elf elf(95,77) ;
	Cyberdemon cyberdemon(22,35);
	Balrog balrog;

	creature_human.getDamage();
	human.getDamage();
	elf.getDamage();
	balrog.getDamage();

	return 0;
}