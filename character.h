#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <iostream>
#include <string>
//#include "floor.h"

using namespace std;

class floor;

class character {
protected:
	int hp;
	int atk;
	int def;
	int exp;
	// dlc
	int agi;//agility
	int acc;//accuracy
	int crt;//critcal hit
	//cld

	int cord[2]; // cordinate on the board
	char symbol; // symbol on the map
	char stand; // place they stand

	floor *f;

public:
	//character();
	character(floor *f, char stand);
	~character();
	int getAtk();
	int getHp();
	int getDef();
	int getRow();
	int getCol();
	char getStand();
	char getSymbol();


//dlc
	int getExp();
	int getAgi();
	int getAcc();
	int getCrt();
	void setCrt(int a);
	void setAcc(int a);
	void setExp(int e);
	void setAgi(int a);

	bool missCombat(character *tar);
	bool isCritical();
//cld

	void setFloor(floor *fl);

	virtual void varyHp(int var, string type) = 0; // effect hp

	//virtual void setStand(char c);
	
	virtual void setCord(int i, int j) = 0;
	virtual void move(string dir) = 0;
	virtual bool getMoved() = 0;
	virtual void attack(character *tar) = 0;
	virtual int getGold() = 0; // get chars gold
	virtual string getRace() = 0;
};


#endif
