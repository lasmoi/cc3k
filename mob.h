#ifndef __MOB_H__
#define __MOB_H__
#include <iostream>
#include <string>
#include "character.h"

using namespace std;

class floor;

class mob: public character{
	int slot; // slot number of this mob on floor.cc

	int gold;
	bool isHostail;
	bool isMoved; // is mob moved this turn
	string race;
public:
	mob(string race, floor *f = 0);
	void setCord(int i, int j); // call to set initial cordinates
	void setSlot(int num);

	void move(string dir);
	//bool mov(string dir);
	void attack(character *tar);

	void varyHp(int var, string type);

	string getRace();
	int getGold();
	bool getMoved();

};


#endif
