#include <iostream>
#include <string>
#include "potion.h"

using namespace std;

potion::potion(floor *f, string name): item(f, "potion"), named(name){
	if(name == "RH"){
		kind = "hp";
		effect = 10;
	}else if(name == "BA"){
		kind = "atk";
		effect = 5;
	}else if(name == "BD"){
		kind = "def";
		effect = 5;
	}else if(name == "PH"){
		kind = "hp";
		effect = -10;
	}else if(name == "WA"){
		kind = "atk";
		effect = -5;
	}else if(name == "WD"){
		kind = "def";
		effect = -5;
	}
}

void potion::use(player *p){
	if(p->getRace() == "Drow") {
		effect = (effect * 3) / 2;
	}
	if(kind == "atk"){
		p->setACtualAtk(effect);
	}else if(kind == "def"){
		p->setACtualDef(effect);
	}else if(kind == "hp"){
		p->varyHp(effect,"potion");
	}
}

dragon *potion::getDragon(){
	return NULL;
};

string potion::getName(){
	return named;
}



