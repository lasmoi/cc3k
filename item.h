#ifndef __ITEM_H__
#define __ITEM_H__
#include <iostream>
#include <string>
#include "floor.h"
#include "player.h"

using namespace std;

class floor;
class player;
class dragon;

class item {
protected:
	int cord[2]; // cordinate on the board
	char symbol; // symbol on the map

	floor *f;

	string name;

public:

	item(floor *f, string name);
	char getSymbol();
	int getRow();
	int getCol();

	//virtual void setStand(char c);
	
	void setCord(int i, int j);
	

	virtual void use(player *p) = 0;
	virtual dragon *getDragon() = 0;
	virtual string getName() = 0;
};


#endif
