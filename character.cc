#include <iostream>
#include <string>
#include "character.h"
#include "floor.h"
#include "map.h"

using namespace std;

character::character(floor *f,char stand):f(f), stand(stand){}

character::~character(){}

int character::getAtk(){ return atk;}

int character::getHp(){ return hp;}

int character::getDef(){ return def;}

int character::getRow(){ return cord[0];}

int character::getCol(){ return cord[1];}

char character::getStand() {return stand;}

char character::getSymbol() { return symbol;}

void character::setFloor(floor *fl){ f = fl;}

int character::getExp(){return exp;}

int character::getAgi(){return agi;}

int character::getAcc(){return acc;}

int character::getCrt(){return crt;}

void character::setCrt(int a){ crt = a;}

void character::setAcc(int a){ acc = a;}

void character::setAgi(int a){ agi = a;}

void character::setExp(int e){ exp = e;}

bool character::missCombat(character *tar){
	bool result = true;
	int tester = 30 + agi - tar->getAcc();
	if(tester < 30) tester = 30;
	if(randomRoll(tester) < 30) result = false;
	return result;
}

bool character::isCritical(){
	bool result = false;
	int tester = 100 + crt;
	if(randomRoll(tester) < crt) result = true;
	return result;
}
