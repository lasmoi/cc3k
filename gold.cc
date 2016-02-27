#include <iostream>
#include <string>
#include "gold.h"

using namespace std;

gold::gold(floor *f, string type): item(f, "gold"), type(type){
	guard = NULL;
	if(type == "small"){
		amount = 1;
	}else if(type == "normal"){
		amount = 2;
	}else if(type == "merchant"){
		amount = 4;
	}else if(type == "dragon"){
		amount = 6;
		//guard = new dragon(f,this);
	}
}

void gold::use(player *p){
	p->addGold(amount);
}


void gold::removeDragon(string cause){
	if(guard){
		if(cause == "drown"){
			delete guard;
			guard = NULL;
		}else{
			guard = NULL;
		}
	}
}

dragon *gold::getDragon(){
	return guard;
}

string gold::getName(){
	return type;
}
