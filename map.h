#ifndef __MAP_H__
#define __MAP_H__

extern char gamemap[25][80];
extern const int maxMob;
extern const int maxItem;
extern const int maxGold;

extern bool isHostail;

extern bool goUpStair;

extern bool nearM;

extern bool curse;

int randomRoll(int range);

#endif
