#include <iostream>
#include <string>
#include <sstream>
//#include <cmath>
#include "player.h"
#include "floor.h"
#include "map.h"
//#include "character.h"

using namespace std;

player::player(string race, floor *f): character(f,'.'), race(race), gold(0){
	hp = 125;
	atk = 25;
	def = 25;
	agi = 30;
	acc = 0;
	crt = 0;
	level = 1;
	totalGold = 0;
	exp = 0;
	maxExp = 15;
	symbol = '@';
	if(race == "Drow"){
		hp = hp + 25;
		def = def - 10;
		maxHp = hp;
	}else if(race == "Vampire"){
		maxHp = 0;
		hp = hp - 75;
	}else if(race == "Troll"){
		hp = hp - 5;
		def = def -10;
		maxHp = hp;
	}else if(race == "Goblin"){
		hp = hp - 15;
		atk = atk - 10;
		def = def -5;
		maxHp = hp;
	}else if(race == "Shade"){
		maxHp = hp;
	}
	actualAtk = atk;
	actualDef = def;
}

void player::setCord(int i, int j){
	//cout << "cord" << endl;
	cord[0]=i;
	cord[1]=j;
}

void player::move(string dir){
	int row = cord[0];
	int col = cord[1];
	char nextStep = f->playerMove(dir);
	if(nextStep == '.' || nextStep == '+' || nextStep == '#'){
		stand = nextStep;
		if(dir == "no"){
			row = row - 1;
		}else if(dir == "so"){
			row = row + 1;
		}else if(dir == "ea"){
			col = col + 1;
		}else if(dir == "we"){
			col = col - 1;
		}else if(dir == "ne"){
			row = row - 1;
			col = col + 1;
		}else if(dir == "nw"){
			row = row - 1;
			col = col - 1;
		}else if(dir == "se"){
			row = row + 1;
			col = col + 1;
		}else if(dir == "sw"){
			row = row + 1;
			col = col - 1;
		}
		cord[0]=row;
		cord[1]=col;
	}
	if(f->checkAround(this,NULL,'P') != NULL){
		f->setSeen(" and sees an unknown potion");
	}
	cout << row << "::" << col << endl;
}

string player::getRace(){return race;}

int player::getGold(){return gold;}

int player::getActualAtk(){return actualAtk;}

int player::getActualDef(){return actualDef;}
	
void player::setACtualAtk(int var){
	if(actualAtk + var >= 0){
		actualAtk = actualAtk + var;
	}else{
		actualAtk = 0;
	}
}

void player::setACtualDef(int var){
	if(actualDef + var >= 0) {
		actualDef = actualDef + var;
	}else{
		actualDef = 0;
	}
}

void player::addGold(int var){
	gold = gold + var;
	totalGold = totalGold + var;
}



int player::getMaxHp(){return maxHp;}

bool player::getMoved(){return true;}

void player::attack(character *tar){
	//int enemyAtk = tar->getAtk();
	int enemyDef = tar->getDef();
	int enemyGold = tar->getGold();
	int enemyExp = tar->getExp();
	//int enemyHp = tar->getHp();
	stringstream ss;
	int damage = (actualAtk * 100)/(enemyDef+100);
	if((enemyDef+100) * damage < actualAtk * 100) damage++;
	//cout << "before damage" << endl;
	if(race == "Vampire"){ // vampire gain its blood
		int diff = 2 + 3*level;
		if(tar->getSymbol() == 'W'){
			hp = hp - diff;
		}else{
			hp = hp + diff;
		}
	}
	//handling the player miss
	int miss = 1;
	int mult = 1;

	if(tar->missCombat(this)) miss = 0;
	if(this->isCritical()) mult = 2;

	damage = damage * miss * mult;

	tar->varyHp(damage,"attack");
	if(damage == 0){
		ss << "PC misses";
	}else{
		ss << "PC deals " << damage << " damage to " << tar->getSymbol() << " (" << tar->getHp() << ")";
	}
	f->setAct(ss.str());
	//cout << "before judge" << endl;
	if(tar->getHp() <= 0){
		gold = gold + enemyGold;
		totalGold = totalGold + enemyGold;
		exp = exp + enemyExp;
		//cout << "after get gold" << endl;
		if(race == "Goblin") {
			gold = gold + 5;
			totalGold = totalGold + 5;
		}
		f->mobDead(tar);
	}
}

void player::varyHp(int var, string type){
	if(type == "potion"){
		if (hp + var > 0){
			hp = hp + var;
			if(hp > maxHp && maxHp != 0) hp = maxHp;
		}else{
			hp = 0;
		}
	}else if(type == "attack"){
		hp = hp - var;
		if(hp < 0) hp = 0;
	}
}

// troll's recovery
void player::recover(int i){
	if(race == "Troll"){ 
		hp = hp + i + 2*(level - 1);
		if(hp > maxHp) hp = maxHp;
	}
}

void player::restore(){
	actualAtk = atk;
	actualDef = def;
}

void player::Cmove(string dir){
	int row = cord[0];
	int col = cord[1];
	char nextStep = f->playerMove(dir);
	if(nextStep == '.' || nextStep == '+' || nextStep == '#'){
		stand = nextStep;
		if(dir == "no"){
			row = row - 1;
		}else if(dir == "so"){
			row = row + 1;
		}else if(dir == "ea"){
			col = col + 1;
		}else if(dir == "we"){
			col = col - 1;
		}else if(dir == "ne"){
			row = row - 1;
			col = col + 1;
		}else if(dir == "nw"){
			row = row - 1;
			col = col - 1;
		}else if(dir == "se"){
			row = row + 1;
			col = col + 1;
		}else if(dir == "sw"){
			row = row + 1;
			col = col - 1;
		}
		cord[0]=row;
		cord[1]=col;
	}else if(nextStep == 'P'){
		f->usePotion(dir);
		move(dir);
	}else if(nextStep == '|' || nextStep == '-' || nextStep == ' '){

	}else{
		f->playerAtk(dir);
	}
	if(f->checkAround(this,NULL,'P') != NULL){
		f->setSeen(" and sees an unknown potion");
	}
	//cout << row << "::" << col << endl;
}

//dlc

int player::getMaxExp(){return maxExp;}

int player::getLevel(){return level;}

void player::setMaxExp(int num) {maxExp = num;}

void player::setLevel(int num) {level = num;}

void player::lvlup(){
	if(exp >= maxExp){
		exp = exp - maxExp;
		maxExp = (maxExp * 3) / 2;
		maxHp = (maxHp * 7) / 5;
		restore();
		atk = atk + 5 + 4 * level;
		def = def + 5 + 4 * level;
		actualDef = actualDef + 5 + 4 * level;
		actualAtk = actualAtk + 5 + 4 * level;
		agi = agi + 5 + 5*level;
		acc = acc + 2 + 3*level;
		crt = crt + level;
		level++;

	}
};

void player::cheat(int type){
	if(type == 1){
		hp = maxHp;
		gold = gold + 250;
	}else if(type == 2){
		maxHp = maxHp + 100;
		hp = maxHp;
		atk = atk + 100;
	}else if(type == 3){
		maxHp = maxHp + 10000;
		hp = maxHp;
	}else if(type == 4){
		atk = atk + 10000;
		def = def + 10000;
		agi = agi + 100;
	}
	restore();
}

void player::Cplayer(){
	hp = hp + 100;
	maxHp = hp;
	atk = atk+5;
	def = def+5;
	crt = 1;
	if(race == "Drow"){
		hp = hp + 20;
		crt = 15;
	}else if(race == "Vampire"){
		hp = hp - 10;
		crt = 5;
		agi = 40;
	}else if(race == "Troll"){
		hp = hp - 45;
		agi = 15;
		crt = 10;
	}else if(race == "Goblin"){
		hp = hp - 35;
		agi = 60;
		crt = 0;
	}else if(race == "Shade"){
		acc = 5;
	}
	maxHp = hp;
	restore();
}

bool player::buy(char c){
	bool result = true;
	gold = gold - 1;
	int atkr;
	int defr;

	if(gold < 0){
		gold++;
		return false;
	}

	if(c == '1'){
		atk = atk+2;
		actualAtk = actualAtk + 2;
	}else if(c == '2'){
		def = def+2;
		actualDef = actualDef + 2;
	}else if(c == '3'){
		hp = hp + 10;
		if(hp > maxHp) hp = maxHp;
	}else if(c == '4'){
		agi++;
	}else if(c == '5'){
		acc++;
	}else if(c == '6'){
		crt++;
	}else if(c == '7'){
		gold = gold - 19;
		if(gold < 0){
			gold = gold + 20;
			return false;
		}
		atkr = randomRoll(3);
		defr = randomRoll(3);
		atk = atk + 6 + atkr;
		actualAtk = actualAtk + 6 + atkr;
		def = def + 6 + defr;
		actualDef = actualDef + 6 + defr;
		hp = hp + 20 + randomRoll(6);
		if(hp > maxHp) hp = maxHp;
		agi = agi + 3 + randomRoll(2);
		acc = acc + 3 + randomRoll(2);
		crt = crt + 3 + randomRoll(2);
	}
	return result;
}

int player::getTotal(){ return totalGold;}

