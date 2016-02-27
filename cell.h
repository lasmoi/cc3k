#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <string>
//#include "character.h"
//#include "item.h"

using namespace std;

class character;
class item;

class cell {
	char symbol;
	string type;
	int chamber;
	int cord[2];

	character *p;
	item *i;

public:
	cell(char symbol, int row, int col);
	~cell();
	char getSymbol();
	int getRow();
	int getCol();
	int getChamber();
	string getType();
	character *getCharacter();
	item *getItem();

	void setSymbol(char s);
	void setChamber(int num);
	void setType(string type);
	void setCharacter(character *p);
	void setItem(item *i);
};


#endif
