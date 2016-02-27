#include <iostream>
#include <string>
#include "cell.h"
#include "item.h"
#include "character.h"

using namespace std;

cell::cell(char symbol, int row, int col): symbol(symbol){
	cord[0]=row;
	cord[1]=col;
	if(symbol == '.') {
		chamber = 0;
	}else{
		chamber = -1;
	}
	i = NULL;
	p = NULL;
}

cell::~cell(){
	if(i) delete i;
	if(p) {
		if(p->getSymbol() != '@') delete p;
		p = NULL;
	}
	i = NULL;

}

char cell::getSymbol() { return symbol;}

int cell::getRow() {return cord[0];}

int cell::getCol(){ return cord[1];}
	
int cell::getChamber(){return chamber;}
	
string cell::getType(){return type;}
	
character *cell::getCharacter(){ return p;}
	
item *cell::getItem(){ return i;}



void cell::setSymbol(char s){
	symbol = s;
}

void cell::setChamber(int num){
	chamber = num;
}

void cell::setType(string typ){
	type = typ;
}
void cell::setCharacter(character *plyr){
	p = plyr;
}

void cell::setItem(item *it){
	i = it;
}



