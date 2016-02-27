#include <iostream>
#include <string>
#include "item.h"
//#include "floor.h"

using namespace std;

item::item(floor *f, string name): f(f), name(name){
	if(name == "gold"){
		symbol = 'G';
	}else if(name == "potion"){
		symbol = 'P';
	}
}

char item::getSymbol() { return symbol;}

int item::getRow(){ return cord[0];}

int item::getCol(){ return cord[1];}

void item::setCord(int i, int j){
	cord[0]=i;
	cord[1]=j;
}


