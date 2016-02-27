#include <iostream>
#include <string>
#include <sstream>
#include "map.h"
#include "dragon.h"
#include "gold.h"

using namespace std;

dragon::dragon(floor *f, gold *hoard): character(f,'.'), hoard(hoard){
	hp = 150;
	atk = 20;
	def = 20;
	exp = randomRoll(2)+10;
	agi = 0;
	acc = 10;
	crt = 20;
	symbol = 'D';
}

void dragon::setCord(int i, int j){
	cord[0]=i;
	cord[1]=j;
}

void dragon::move(string str){}

bool dragon::getMoved(){return true;}

void dragon::varyHp(int var, string type){
	if(type == "attack"){
		hp = hp - var;
		if(hp < 0) hp = 0;
	}
	if(hp <= 0){
		if(hoard) hoard->removeDragon("attack");
	}
}

void dragon::attack(character *tar){
	int enemyDef = tar->getDef();
	//int enemyHp = tar->getHp();
	stringstream ss;
	int damage = (atk * 100)/(enemyDef+100);
	if((enemyDef+100) * damage < atk * 100) damage++;
	tar->varyHp(damage,"attack");
	ss << symbol <<" deals " << damage << " damage to PC.";
	f->setMobAct(ss.str());
}

int dragon::getGold(){return 0;}

string dragon::getRace(){return "Dragon";}


