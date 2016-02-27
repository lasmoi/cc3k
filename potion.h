#ifndef __POTION_H__
#define __POTION_H__
#include <iostream>
#include <string>
#include "item.h"

using namespace std;

class floor;
class player;
class dragon;

class potion: public item{
	string kind;
	string named;
	//string attr;
	int effect;

public:
	potion(floor *f, string name);

	void use(player *p);

	dragon *getDragon();

	string getName();
};



#endif
