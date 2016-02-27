#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <curses.h>
#include "floor.h"
#include "player.h"
#include "cell.h"
#include "mob.h"
#include "potion.h"
#include "gold.h"
#include "dragon.h"

using namespace std;

void floor::setChamber(int row, int col, int cham){
	if(map[row][col]->getChamber() == 0){
		map[row][col]->setChamber(cham);
		if(row-1>=0 && map[row-1][col]->getChamber() == 0){
			setChamber(row-1,col,cham);
		}
		if(row+1<25 && map[row+1][col]->getChamber() == 0){
			setChamber(row+1,col,cham);
		}
		if(col-1>=0 && map[row][col-1]->getChamber() == 0){
			setChamber(row,col-1,cham);
		}
		if(col+1<80 && map[row][col+1]->getChamber() == 0){
			setChamber(row,col+1,cham);
		}
	}
}

void floor::setSeen(string str){
	potionSeen = str;
}

void floor::setAct(string str){
	playerAct = str;
}

void floor::setMobAct(string str){
	mobAct = mobAct + str;
}

cell *floor::randomgen(int chambernum){ // select random cell in a chamber
	int row;
	int col;
	bool regen = true;
	while(regen){
		row = randomRoll(25);
		col = randomRoll(80);
		if(map[row][col]->getSymbol() == '.' && map[row][col]->getChamber() == chambernum) {
			regen = false;
		}
	}
	return map[row][col];
}

floor::floor(): /*maxMob(20), maxItem(10),maxGold(10),*/ level(1), mobCount(0){
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			map[i][j] = new cell(gamemap[i][j],i,j);
		}
	}
	roomCount = 0;
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			if(map[i][j]->getChamber() == 0){
				roomCount++;
				setChamber(i,j,roomCount);
			}
		}
	}
	playerAct = "";
	potionSeen = "";
	mobAct = "";
	merchantAct = "";
	//p = new player;
}

floor::floor(player *p, int level): /*maxMob(20), maxItem(10),maxGold(10),*/ p(p), level(level), mobCount(0){
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			map[i][j] = new cell(gamemap[i][j],i,j);
		}
	}
	roomCount = 0;
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			if(map[i][j]->getChamber() == 0){
				roomCount++;
				setChamber(i,j,roomCount);
			}
		}
	}
	playerAct = "";
	potionSeen = "";
	mobAct = "";
	merchantAct = "";
}

floor::~floor(){
	//if(level == 1) delete p;
	for(int i = 0; i < 25; i++){
		for(int j = 0; j<80;j++){
			delete map[i][j];
		}
	}
	/*for(int i = 0; i<mobCount; i++){
		delete mobs[i];
	}*/
}

void floor::readin(string fname, player *pl){
	char symbol;
	int row = 0;
	string line;
	int linenum = 0;
	potion *pot;
	gold *g;
	mob *m;
	dragon *d;
	//player *p;
	if(!p) p = pl;
	ifstream file;
	//string &refName = fname;
	file.open(fname.c_str());
	//cout << "reding before skip" << endl;
	while(linenum < (level-1)*25){ // skip previous location
		getline(file,line);
		linenum++;
	}
	while(linenum<level*25){
		getline(file,line);
		int col = 0;
		istringstream ss(line);
		//cout << "reading each line" << endl;
		ss.get(symbol);
		while(!ss.eof()){
			map[row][col]->setSymbol(symbol);
			//cout << "reading symbol: " << symbol << endl;
			if (symbol=='@'){
				//cout << "s1" << p->getSymbol() << endl;
				p->setCord(row,col);
				//cout << "s1" << endl;
				map[row][col]->setCharacter(p);
				//cout << "s1" << endl;
				map[row][col]->setSymbol('@');
			} else if (symbol=='0'){
				pot = new potion(this,"RH");
				pot->setCord(row,col);
				map[row][col]->setItem(pot);
				map[row][col]->setSymbol('P');
			} else if (symbol=='1'){
				pot = new potion(this,"BA");
				pot->setCord(row,col);
				map[row][col]->setItem(pot);
				map[row][col]->setSymbol('P');
			} else if (symbol=='2'){
				pot = new potion(this,"BD");
				pot->setCord(row,col);
				map[row][col]->setItem(pot);
				map[row][col]->setSymbol('P');
			} else if (symbol=='3'){
				pot = new potion(this,"PH");
				pot->setCord(row,col);
				map[row][col]->setItem(pot);
				map[row][col]->setSymbol('P');
			} else if (symbol=='4'){
				pot = new potion(this,"WA");
				pot->setCord(row,col);
				map[row][col]->setItem(pot);
				map[row][col]->setSymbol('P');
			} else if (symbol=='5'){
				pot = new potion(this,"WD");
				pot->setCord(row,col);
				map[row][col]->setItem(pot);
				map[row][col]->setSymbol('P');
			} else if (symbol=='6'){
				g = new gold(this,"normal");
				g->setCord(row,col);
				map[row][col]->setItem(g);
				map[row][col]->setSymbol('G');
			} else if (symbol=='7'){
				g = new gold(this,"small");
				g->setCord(row,col);
				map[row][col]->setItem(g);
				map[row][col]->setSymbol('G');
			} else if (symbol=='8'){
				g = new gold(this,"merchant");
				g->setCord(row,col);
				map[row][col]->setItem(g);
				map[row][col]->setSymbol('G');
			} else if (symbol=='9'){
				g = new gold(this,"dragon");
				g->setCord(row,col);
				map[row][col]->setItem(g);
				map[row][col]->setSymbol('G');
				g->removeDragon("drown");
			} else if (symbol=='H'){
				m = new mob("Human",this);
				m->setCord(row,col);
				map[row][col]->setCharacter(m);
			} else if (symbol=='W'){
				m = new mob("Dwarf",this);
				m->setCord(row,col);
				map[row][col]->setCharacter(m);
			} else if (symbol=='E'){
				m = new mob("Elf",this);
				m->setCord(row,col);
				map[row][col]->setCharacter(m);
			} else if (symbol=='O'){
				m = new mob("Orc",this);
				m->setCord(row,col);
				map[row][col]->setCharacter(m);
			} else if (symbol=='M'){
				m = new mob("Merchant",this);
				m->setCord(row,col);
				map[row][col]->setCharacter(m);
			} else if (symbol=='L'){
				m = new mob("Halfling",this);
				m->setCord(row,col);
				map[row][col]->setCharacter(m);
			} else if (symbol=='D'){
				d = new dragon(this,NULL);
				d->setCord(row,col);
				map[row][col]->setCharacter(d);
			}
			col++;
			ss.get(symbol);
		}
		row++;
		linenum++;
	}// reading ends

	playerAct = "Map initializing completed";
}

void floor::printMap(){
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			cout << map[i][j]->getSymbol();
			//if(map[i][j]->getCharacter()) cout << '$';
		}
		cout << endl;
	}
	cout << "Race: " << p->getRace() << " " << "Gold: " << p->getGold();
	cout << "                                                Floor: " << level << endl;
	cout << "HP: " << p->getHp() << "/" << p->getMaxHp()<<endl;
	cout << "Atk: " << p->getActualAtk() << endl;
	cout << "Def: " << p->getActualDef() << endl;
	cout << "ACtion: " << playerAct << potionSeen << ". " << mobAct << endl;
	cout << "row: " << p->getRow() << " col: " << p->getCol() << endl;

	playerAct = "";
	potionSeen = "";
	mobAct = "";
}

void floor::CprintMap(){
	stringstream ss;
	stringstream pm;
	char sy;
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			sy = map[i][j]->getSymbol();
			pm << sy;
			printw(pm.str().c_str());
			pm.str("");
			//if(map[i][j]->getCharacter()) cout << '$';
		}
		pm << '\n';
		//printw(pm.str().c_str());
	}
	//printw(pm.str().c_str());
	ss << merchantAct << endl;
	ss << "\nRace: " << p->getRace() << " " << "Gold: " << p->getGold();
	ss << "                                                Floor: " << level << endl;
	ss << "HP: " << p->getHp() << "/" << p->getMaxHp()<<endl;
	ss << "EXP: " << p->getExp() << "/" << p->getMaxExp() << "       level: " << p->getLevel() << endl;
	ss << "Atk: " << p->getActualAtk() << "     Def: " << p->getActualDef() << endl;
	ss << "Agility: " << p->getAgi() << "    Accuracy: " << p->getAcc() << "    Critcal Hit Rate: " << p->getCrt() << endl;
	ss << "ACtion: " << playerAct << potionSeen << ". " << mobAct << endl;
	ss << "row: " << p->getRow() << " col: " << p->getCol() << endl;

	playerAct = "";
	potionSeen = "";
	mobAct = "";
	merchantAct = "";
	printw(ss.str().c_str());
}

void floor::spawnPlayer(player *pler){
	//if(p == pler) cout << "p is real" << endl;
	//if(p) delete p;
	p = pler;
	int playerChamber = randomRoll(5) + 1;
	cell *dest = randomgen(playerChamber);
	// set players cord
	p->setCord(dest->getRow(),dest->getCol());
	//cout << row << ":"<<col << endl;
	dest->setSymbol(p->getSymbol());
	dest->setCharacter(p);

	//cout << "here2" << endl;
	//set stair position
	int stairChamber = (playerChamber + randomRoll(4))%5 + 1;
	dest = randomgen(stairChamber);
	dest->setSymbol('\\');
	playerAct = "Player character has spawned";
}

void floor::spawnPotion(){
	int potionChamber;
	int potionType;
	cell *dest;
	potion *po;
	//cout << "in potion 0" << endl;
	for(int i=0; i < maxItem; i++){
		potionChamber = randomRoll(5) + 1;
		potionType = randomRoll(6);
		dest = randomgen(potionChamber);
		//cout << "in potion 1" << endl;
		if(potionType == 0){
			po = new potion(this, "RH");
			po->setCord(dest->getRow(),dest->getCol());
			dest->setItem(po);
			dest->setSymbol('P');
		}else if(potionType == 1){
			po = new potion(this, "BA");
			po->setCord(dest->getRow(),dest->getCol());
			dest->setItem(po);
			dest->setSymbol('P');
		}else if(potionType == 2){
			po = new potion(this, "BD");
			po->setCord(dest->getRow(),dest->getCol());
			dest->setItem(po);
			dest->setSymbol('P');
		}else if(potionType == 3){
			po = new potion(this, "PH");
			po->setCord(dest->getRow(),dest->getCol());
			dest->setItem(po);
			dest->setSymbol('P');
		}else if(potionType == 4){
			po = new potion(this, "WA");
			po->setCord(dest->getRow(),dest->getCol());
			dest->setItem(po);
			dest->setSymbol('P');
		}else if(potionType == 5){
			po = new potion(this, "WD");
			po->setCord(dest->getRow(),dest->getCol());
			dest->setItem(po);
			dest->setSymbol('P');
		}
	}
}

void floor::spawnGold(){
	int goldChamber;
	int goldType;
	cell *dest;
	gold *g;
	for(int i=0; i < maxItem; i++){
		goldChamber = randomRoll(5) + 1;
		goldType = randomRoll(8);
		dest = randomgen(goldChamber);
		//cout << "in mob 0" << endl;
		if(goldType == 0){
			//cout << "dragon" << endl;
			g = new gold(this, "dragon");
			g->setCord(dest->getRow(),dest->getCol());
			dest->setItem(g);
			dest->setSymbol('G');
			//cout << "dragon set" << endl;
			setDragon(g);
			//cout << "done" << endl;
		}else if(goldType == 1 || goldType == 2){
			g = new gold(this, "small");
			g->setCord(dest->getRow(),dest->getCol());
			dest->setItem(g);
			dest->setSymbol('G');
		}else{
			g = new gold(this, "normal");
			g->setCord(dest->getRow(),dest->getCol());
			dest->setItem(g);
			dest->setSymbol('G');
		}
	}
}

void floor::setDragon(gold *g){
	int dir = randomRoll(4);
	bool regen = true;
	int count = 0;
	int row = g->getRow();
	int col = g->getCol();
	dragon *d;
	while(regen){
		count++;
		if(count == 10) { // if cannot generate a location of a dragon, dragon is falled to fourth dimension
			//g->removeDragon("drown");
			break;
		}
		if(dir == 0 && map[row+1][col]->getSymbol() == '.'){
			d = new dragon(this, NULL);
			d->setCord(row+1,col);
			map[row+1][col]->setSymbol('D');
			map[row+1][col]->setCharacter(d);
			regen = false;
		}else if(dir == 1 && map[row-1][col]->getSymbol() == '.'){
			d = new dragon(this, NULL);
			d->setCord(row-1,col);
			map[row-1][col]->setSymbol('D');
			map[row-1][col]->setCharacter(d);
			regen = false;
		}else if(dir == 2 && map[row][col+1]->getSymbol() == '.'){
			d = new dragon(this, NULL);
			d->setCord(row,col+1);
			map[row][col+1]->setSymbol('D');
			map[row][col+1]->setCharacter(d);
			regen = false;
		}else if(dir == 3 && map[row][col-1]->getSymbol() == '.'){
			d = new dragon(this, NULL);
			d->setCord(row,col-1);
			map[row][col-1]->setSymbol('D');
			map[row][col-1]->setCharacter(d);
			regen = false;
		}
	}
}

void floor::spawnMobs(){
	int mobChamber;
	int mobType;
	cell *dest;
	mob *newMob;
	//cout << "in mob 0" << endl;
	while (mobCount < 20){
		//regen = true;
		mobChamber = randomRoll(5) + 1;
		mobType = randomRoll(18);
		if(mobType == 0 || mobType == 1){
			newMob = new mob("Merchant", this);
		}else if(mobType == 2 || mobType == 3){
			newMob = new mob("Orc", this);
		}else if(mobType == 4 || mobType == 5){
			newMob = new mob("Elf", this);
		}else if(mobType >= 6 && mobType <= 10){
			newMob = new mob("Halfling", this);
		}else if(mobType >= 11 && mobType <= 13){
			newMob = new mob("Dwarf", this);
		}else if(mobType >= 14 && mobType <= 17){
			newMob = new mob("Human", this);
		}
		//cout << "in mob 1" << endl;
		dest = randomgen(mobChamber);
		//cout << mobCount << ":"<< newMob->getRace() << endl;
		newMob->setCord(dest->getRow(),dest->getCol());
		newMob->setSlot(mobCount);
		dest->setSymbol(newMob->getSymbol());
		dest->setCharacter(newMob);
		mobCount++;
	}
}

char floor::mobMove(string dir, mob *m){
	return '0';
}

void floor::moveMobs(){ // includes mobs attack
	int dir;
	int row;
	int col;
	int count;
	character *c;
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			c = map[i][j]->getCharacter();
			if(c && c->getSymbol() !='@' && !c->getMoved()){
				dir = randomRoll(8);
				row = i;
				col = j;
				count = 0;
				while(map[row][col]->getSymbol() != '.'){
					row = i;
					col = j;
					if(dir == 0){// "no"
						row = row - 1;
					}else if(dir == 1){// "so"
						row = row + 1;
					}else if(dir == 2){// "ea"
						col = col + 1;
					}else if(dir == 3){// "we"
						col = col - 1;
					}else if(dir == 4){// "ne"
						row = row - 1;
						col = col + 1;
					}else if(dir == 5){// "nw"
						row = row - 1;
						col = col - 1;
					}else if(dir == 6){// "se"
						row = row + 1;
						col = col + 1;
					}else if(dir == 7){// "sw"
						row = row + 1;
						col = col - 1;
					}
					dir = randomRoll(8);
					
					count++;
					//cout 
					if(count == 30) {
						break;
					}
				}
				//cout << row << ":" << col << endl;

				// attack player or move
				cell *atkTar = checkAround(c,NULL,'@');
				if(atkTar != NULL){ // if player is in the range
					if(c->getSymbol() != 'M'){ //not merchant
						c->attack(atkTar->getCharacter());
						//printw("here");
					}else{
						if(isHostail) c->attack(atkTar->getCharacter());
						nearM = true;
					}
					if(c->getSymbol() == 'E' && atkTar->getCharacter()->getRace() != "Drow") c->attack(atkTar->getCharacter()); // second attack of elf
					//cout << "lable attack: " << atkTar->getSymbol() << endl;
					c->move("move");
				}else{
					map[i][j]->setCharacter(NULL);
					map[i][j]->setSymbol('.');
					map[row][col]->setSymbol(c->getSymbol());
					map[row][col]->setCharacter(c);
					c->setCord(row,col);
					c->move("move");
				}

			} // if normal mobs end
			if(c && c->getSymbol() == 'D'){ // if dragons

				cell *atkTar = checkAround(c,NULL,'@');
				if(atkTar != NULL){ // if player is in the range
					//if(atkTar->getCharacter()) cout << "lable attack: " << atkTar->getCharacter() << endl;
					c->attack(atkTar->getCharacter());
					//cout << "lable attack: " << atkTar->getSymbol() << endl;
				}

			}
		}// for
	}// for
	for(int i = 0; i<25; i++){ // reset isMoved
		for(int j = 0; j<80;j++){
			c = map[i][j]->getCharacter();
			if(c && c->getSymbol() !='@'){
				c->move("");
			}
		}
	}// for
}

char floor::playerMove(string dir){
	int row = p->getRow();
	int col = p->getCol();
	map[row][col]->setSymbol(p->getStand());
	string direction = "nowhere";
	if(dir == "no"){
		row = row - 1;
		direction = "North";
	}else if(dir == "so"){
		row = row + 1;
		direction = "South";
	}else if(dir == "ea"){
		col = col + 1;
		direction = "East";
	}else if(dir == "we"){
		col = col - 1;
		direction = "West";
	}else if(dir == "ne"){
		row = row - 1;
		col = col + 1;
		direction = "Northeast";
	}else if(dir == "nw"){
		row = row - 1;
		col = col - 1;
		direction = "Northwest";
	}else if(dir == "se"){
		row = row + 1;
		col = col + 1;
		direction = "Southeast";
	}else if(dir == "sw"){
		row = row + 1;
		col = col - 1;
		direction = "Southwest";
	}
	char nextStep = map[row][col]->getSymbol();
	if(nextStep == '.' || nextStep == '+' || nextStep == '#'){
		if(playerAct == "") playerAct = "PC moves " + direction;
		map[p->getRow()][p->getCol()]->setCharacter(NULL);
		map[row][col]->setSymbol(p->getSymbol());
		map[row][col]->setCharacter(p);
	}else if(nextStep == 'G'){
		//if gold is guarded by dragon
		if(checkAround(NULL, map[row][col], 'D') != NULL){
			playerAct = "Defeat Dragon before collecting dragon hoard";
			map[p->getRow()][p->getCol()]->setSymbol(p->getSymbol());
		}else{
			playerAct = "PC moves " + direction;
			map[row][col]->getItem()->use(p);
			delete map[row][col]->getItem();
			map[row][col]->setItem(NULL);
			map[row][col]->setSymbol(p->getSymbol());
			map[p->getRow()][p->getCol()]->setCharacter(NULL);
			map[row][col]->setCharacter(p);
			nextStep = '.';
		}
		// end if G
	}else if(nextStep == '\\'){
		goUpStair = true;
		playerAct = "Go upstairs!";

	}else{
		playerAct = "Cannot move " + direction;
		map[p->getRow()][p->getCol()]->setSymbol(p->getSymbol());
	}
	return nextStep;
}

cell *floor::checkAround(character *p, cell *c, char symbol){
	int row;
	int col;
	if(p){
		row = p->getRow();
		col = p->getCol();
	}
	if(c){
		row = c->getRow();
		col = c->getCol();
	}
	cell *result = NULL;
	//cout << "p symbol: " << p->getSymbol() << endl;
	if(map[row-1][col]->getSymbol() == symbol){
		result = map[row-1][col];
	}else if(map[row-1][col-1]->getSymbol() == symbol){
		result = map[row-1][col-1];
	}else if(map[row][col-1]->getSymbol() == symbol){
		result = map[row][col-1];
	}else if(map[row+1][col-1]->getSymbol() == symbol){
		result = map[row+1][col-1];
	}else if(map[row+1][col]->getSymbol() == symbol){
		result = map[row+1][col];
	}else if(map[row+1][col+1]->getSymbol() == symbol){
		result = map[row+1][col+1];
	}else if(map[row][col+1]->getSymbol() == symbol){
		result = map[row][col+1];
	}else if(map[row-1][col+1]->getSymbol() == symbol){
		result = map[row-1][col+1];
	}
	//if (result) cout << "result symbol: " << result->getSymbol() << endl;
	return result;
}

void floor::usePotion(string dir){
	int row = p->getRow();
	int col = p->getCol();
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
	item *i = map[row][col]->getItem();
	if(map[row][col]->getSymbol() == 'P'){
		i->use(p);
		string name = i->getName();
		playerAct = "player uses " + name;
		map[row][col]->setSymbol('.');
		delete i;
		map[row][col]->setItem(NULL);
	}else{
		playerAct = "Nothing to use";
	}
}

void floor::playerAtk(string dir){
	int row = p->getRow();
	int col = p->getCol();
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
	character *c = map[row][col]->getCharacter();
	if(c){
		//cout << "pre attack" << c->getMoved() << endl;
		p->attack(c);
		if(c->getSymbol()=='M' && !isHostail) isHostail = true;
	}else{
		playerAct = "Nothing to attack";
	}
}

void floor::mobDead(character *m){
	int row = m->getRow();
	int col = m->getCol();
	map[row][col]->setSymbol('.');
	map[row][col]->setCharacter(NULL);
	if(m->getSymbol() == 'M'){
		gold *g = new gold(this,"merchant");
		g->setCord(row,col);
		map[row][col]->setSymbol('G');
		map[row][col]->setItem(g);
	}
	delete m;
}


//   multi level handling

cell *floor::findPlayer(){
	cell *result = NULL;
	for(int i = 0; i<25; i++){
		for(int j = 0; j<80;j++){
			if(map[i][j]->getSymbol() == '@'){
				result = map[i][j];
				//return result;
			}
		}
	}
	return result;
}

void floor::merchantSale(){
	stringstream ss;
	ss << "\nMerchant provides the following items(all cost 1 gold except combo):" << endl;
	ss << "(1): 2 atk;  (2): 2 def;  (3): 5 hp;  (4): 1 agi;"<< endl;
	ss << "(5): 1 acc;  (6): 1 crt;  (7): lucky combo for 20." << endl;
	merchantAct = ss.str();
}

int floor::getLevel(){ return level;}


