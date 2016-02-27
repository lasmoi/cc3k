#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "mob.h"
#include "character.h"
#include "floor.h"
#include "map.h"

using namespace std;

mob::mob(string race, floor *f): character(f,'.'), race(race), isHostail(true), isMoved(false){
	gold = rand()%2+1;
	exp = rand()%2+3;
	agi = 0;
	acc = 0;
	crt = 0;
	if(race == "Human"){
		hp = 140;
		atk = 20;
		def = 20;
		symbol = 'H';
		gold = 4;
	}else if(race == "Dwarf"){
		hp = 100;
		atk = 20;
		def = 30;
		symbol = 'W';
	}else if(race == "Elf"){
		hp = 140;
		atk = 30;
		def = 10;
		symbol = 'E';
	}else if(race == "Orc"){
		hp = 180;
		atk = 30;
		def = 25;
		symbol = 'O';
	}else if(race == "Merchant"){
		hp = 30;
		atk = 70;
		def = 5;
		gold = 0;
		symbol = 'M';
	}else if(race == "Halfling"){
		hp = 100;
		atk = 15;
		def = 20;
		symbol = 'L';
	}
	if(curse){
		hp = hp + (hp * f->getLevel())/2;
		atk = atk + (atk * f->getLevel())/2;
		def = def + (def * f->getLevel())/2;
		agi = 5*(f->getLevel() - 1);
		acc = 5*(f->getLevel() - 1);
		crt = 5*(f->getLevel() - 1);
	}
}

void mob::setCord(int i, int j){
	cord[0]=i;
	cord[1]=j;
}

void mob::setSlot(int num){
	slot = num;
}

void mob::move(string dir){
	if(dir == "move"){
		isMoved = true;
	}else{
		isMoved = false;
	}
}

string mob::getRace(){return race;}

int mob::getGold(){return gold;}

bool mob::getMoved(){return isMoved;}

void mob::varyHp(int var, string type){
	if(type == "attack"){
		hp = hp - var;
		if(hp < 0) hp = 0;
	}
}

void mob::attack(character *tar){
	int enemyDef = tar->getDef();
	//int enemyHp = tar->getHp();

	//determine the miss
	//int notMiss = rand()%2;

	//calculate base damage
	stringstream ss;
	int damage = (atk * 100)/(enemyDef+100);
	if((enemyDef+100) * damage < atk * 100) damage++;

	if(tar->getRace() == "Goblin"){
		damage = (damage * 3)/2;
	}

	int mult = 1;
	if(this->isCritical()) mult = 2;
	
	if(tar->missCombat(this)){
		tar->varyHp(damage,"attack");
		ss << symbol <<" deals " << damage << " damage to PC.";
	}else{
		ss << symbol <<" missed.";
	}
	f->setMobAct(ss.str());
}


