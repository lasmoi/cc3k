#ifndef __GOLD_H__
#define __GOLD_H__
#include <iostream>
#include <string>
#include "item.h"
#include "dragon.h"

using namespace std;

class floor;

class dragon;

class player;

class gold: public item{
	string type;

	dragon *guard;
	int amount;



public:
	gold(floor *f, string type);

	void use(player *p);

	void removeDragon(string cause);
	dragon *getDragon();
	string getName();
};



#endif
