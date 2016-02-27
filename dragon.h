#ifndef __DRAGON_H__
#define __DRAGON_H__
#include <iostream>
#include <string>
#include "character.h"

using namespace std;

class floor;

class gold;

class character;

class dragon: public character{
	gold *hoard;

public:
	dragon(floor *f, gold *hoard);
	void setCord(int i, int j);
	void move(string dir);
	bool getMoved();

	void attack(character *tar);

	void varyHp(int var, string type);

	int getGold();
	string getRace();

};


#endif
