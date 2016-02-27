#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include "character.h"

using namespace std;

class floor;
class character;

class player: public character{
	int maxHp;
	int actualAtk;
	int actualDef;

	int gold;
	int totalGold;

	//dlc
	int maxExp;
	int level;

	string race;
public:
	player(string race = "Shade", floor *f = 0);
	void setCord(int i, int j); // call to set initial cordinates

	void move(string dir);
	//void use(string dir);
	void Cmove(string dir);

	void attack(character *tar);

	void varyHp(int var, string type);

	string getRace();
	int getGold();
	int getActualAtk();
	int getActualDef();
	void setACtualAtk(int var);
	void setACtualDef(int var);
	void addGold(int var);
	int getMaxHp();
	bool getMoved(); // nothing to do

	void recover(int i);
	void restore();

	//dlc
	int getMaxExp();
	int getLevel();
	int getTotal();

	void setMaxExp(int num);
	void setLevel(int num);

	void lvlup();
	void Cplayer();

	void cheat(int type);

	bool buy(char c);

};


#endif
