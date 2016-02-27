#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <string>
#include "character.h"
#include "item.h"
#include "map.h"
#include "cell.h"

using namespace std;

class cell;
class character;
class player;
class mob;
class potion;
class gold;
class item;

class floor {
	/*const int maxMob;
	const int maxItem;
	const int maxGold;*/
	const int level;

	int roomCount;
	int mobCount;

	//mob *mobs[20];
	//item *items[maxItem];
	player *p;

	string playerAct;
	string potionSeen;
	string mobAct;
	string merchantAct;


	cell *map[25][80];

	void setChamber(int row, int col, int cham); // set chamber for map
	cell *randomgen(int chambernum);

public:
	floor();
	floor(player *p, int level);
	~floor();

	void readin(string fname, player *pl);

	void setSeen(string str);
	void setAct(string str);
	void setMobAct(string str);

	void printMap();
	void CprintMap();
	void moveMobs();
	/*void checkPo(); // check if player near any potion
	void checkPl(); // check if mob near the player*/
	cell *checkAround(character *p, cell *c, char symbol);

	void playerAtk(string dir);

	void mobDead(character *m);

	char playerMove(string dir);
	char mobMove(string dir, mob *m);
	void usePotion(string dir);

	void spawnPlayer(player *pler);
	//void spawnStair();
	void spawnPotion();
	void spawnGold();
	void setDragon(gold *g);
	void spawnMobs();

	player getPlayer();
	int getLevel();

	cell *findPlayer();

	void merchantSale();

};


#endif
