#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <curses.h>

#include "floor.h"
#include "map.h"
#include "player.h"
#include "character.h"

using namespace std;

int main(int argc, char const *argv[]){
	srand(time(NULL));
	//srand(1000);
	string in = "";
	string arg1 = "";
	string arg2 = "";
	if(argc >= 2) arg1 = argv[1];
	if(argc >= 3) arg2 = argv[2];
	char curIn = 0;
	stringstream ss1;
	stringstream ss2;
	if(arg1 == "-c"){
		// curse and bonus operation
		curse = true;
		initscr();
		noecho();
		keypad(stdscr, TRUE);
		while(curIn != 'q'){
			clear();
			ss1 << "choose your race:" << endl;
			ss1 << 
			"s: shade that has starting stats (125 HP, 25 Atk, 25 Def).\n" << 
			"d: drow (150 HP, 25 Atk , 15 Def, all potions have their effect magnified by 1.5),\n" <<
			"v: vampire (50 HP, 25 Atk, 25 Def, gains 5 HP every attack and has no maximum HP),\n" <<
			"t: troll (120 HP, 25 Atk, 15 Def, regains 5 HP every turn; HP is capped at 120 HP),\n" <<
			"g: goblin (110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy)." << endl;
			printw(ss1.str().c_str());

			curIn = getch();
			while(curIn != 's' && curIn != 'd' && curIn != 'v' && curIn != 't' && curIn != 'g'){
				clear();
				ss2 << "please enter valid command" << endl;
				printw(ss1.str().c_str());
				printw(ss2.str().c_str());
				curIn = getch();
				ss2.str("");
			}
			string race = "Shade";
			if(curIn == 'd') race = "Drow";
			if(curIn == 'v') race = "Vampire";
			if(curIn == 't') race = "Troll";
			if(curIn == 'g') race = "Goblin";

			floor *game[5];
			int level = 1;
			//cout << "player new" << endl;
			player *p = new player(race, NULL);
			p->Cplayer();
			floor *currentFloor;
			int currentLevel;

			while(level <= 5){
				//cout << "floor" << endl;
				floor *f = new floor(NULL,level);
				
				game[level-1] = f;
				/*floor *f = new floor(p, 2);
				p->setFloor(f);*/

				if(arg2 == ""){
					//cout << "here0" << endl;
					f->spawnPlayer(p);
					//cout << "player" << endl;
					f->spawnPotion();
					//cout << "potion" << endl;
					f->spawnGold();
					//cout << "gold" << endl;
					f->spawnMobs();
					//cout << "mob" << endl;
				}else{
					string sourse = argv[2];
					//cout << "read" << endl;
					f->readin(sourse, p);
				}
				level++;
			}

			currentLevel = 1;
			currentFloor = game[0];

			cell *initial = currentFloor->findPlayer();
			p->setCord(initial->getRow(),initial->getCol());
			p->setFloor(currentFloor);

			isHostail = false;

			clear();
			currentFloor->CprintMap();

			string cheatCode; // record cheating
			
			while(true){
				curIn = getch();
				clear();
				ss1.str("");
				ss2.str("");

				// set the cheat			
				ss2 << curIn;
				cheatCode = cheatCode + ss2.str();
				if(cheatCode.length() >= 14) {
					cheatCode = cheatCode.substr(cheatCode.length()-13);
				}
				if(cheatCode.length() == 13){
					if(cheatCode.substr(2) == "wwssadadba\n") p->cheat(3);
					if(cheatCode == "whosyourdaddy") p->cheat(4);
					if(cheatCode.substr(6) == "hesoyam") p->cheat(1);
					if(cheatCode.substr(4) == "helpmeout") p->cheat(2);
				}
				//finish cheating
				//printw("hereadfasdfasdfasdfasdfasdf");

				if(curIn == 'q'){
					break;
				}else if(curIn == 'r'){
					ss1 << "Enter y to confirm restart:" << endl;
					printw(ss1.str().c_str());
					curIn = getch();
					ss2.str(""); // clear
					ss2 << curIn;
					cheatCode = cheatCode + ss2.str();
					ss2.str(""); //clear
					if (curIn == 'y'){
						break;
					}else{
						ss2 << "Game continue" << endl;
						printw(ss2.str().c_str());
						continue;
					}
				}else{
					if(curIn == 'w'){
						p->Cmove("no");
					}else if(curIn == 'a'){
						p->Cmove("we");
					}else if(curIn == 's'){
						p->Cmove("so");
					}else if(curIn == 'd'){
						p->Cmove("ea");
					}
				}
				p->recover(1); // troll recover
				p->lvlup();
				currentFloor->moveMobs();
				//insert go uptairs
				if(goUpStair){
					currentLevel++;
					ss1.str("");
					ss2.str("");
					if(currentLevel > 5){ // let's end this game
						clear();
						ss1 << "You have reached the void floor! You win!" << endl;
						ss1 << "Your score is: "<< endl;
						int score = p->getTotal();
						if(p->getRace() == "Shade") score = (score*3)/2;
						ss1 << score << endl << endl;
						ss1 << "Restart the game? if yes, type y; if no, type any other characters." << endl;
						printw(ss1.str().c_str());
						curIn = getch();
						if(curIn != 'y') curIn = 'q';
						break;
					}else{
						currentFloor = game[currentLevel-1];
						initial = currentFloor->findPlayer();
						p->setCord(initial->getRow(),initial->getCol());
						p->setFloor(currentFloor);
						p->restore();
					}
					goUpStair = false;
				}

				if(nearM){
					p->buy(curIn);
					nearM = false;
					currentFloor->merchantSale();
				}
				//clear();
				currentFloor->CprintMap();
				//printw(cheatCode.c_str());

				if(p->getHp() <= 0){
					clear();
					ss1.str("");
					ss2.str("");
					ss1 << "You are dead." << endl;
					ss1 << "Your score is: "<< endl;
					int score = p->getGold();
					if(p->getRace() == "Shade") score = (score*3)/2;
					ss1 << score << endl << endl;
					ss1 << "Restart the game? if yes, type y; if no, type any other characters." << endl;
					printw(ss1.str().c_str());
					curIn = getch();
					if(curIn != 'y') curIn = 'q';
					clear();
					break;
				}
			}
			delete game[1];
			delete game[2];
			delete game[3];
			delete game[4];
			delete game[0];
			delete p;
			currentFloor = NULL;
			p = NULL;
		} // end while
		endwin();

	}else{
		// non curse
		while(in != "q" && !cin.eof()){
			cout << "choose your race:" << endl;
			cout << 
			"s: shade that has starting stats (125 HP, 25 Atk, 25 Def).\n" << 
			"d: drow (150 HP, 25 Atk , 15 Def, all potions have their effect magnified by 1.5),\n" <<
			"v: vampire (50 HP, 25 Atk, 25 Def, gains 5 HP every attack and has no maximum HP),\n" <<
			"t: troll (120 HP, 25 Atk, 15 Def, regains 5 HP every turn; HP is capped at 120 HP),\n" <<
			"g: goblin (110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy)." << endl;

			cin >> in;
			while(in != "s" && in != "d" && in != "v" && in != "t" && in != "g" && !cin.eof()){
				cout << "please enter valid command" << endl;
				cin >> in;
			}
			string race = "Shade";
			if(in == "d") race = "Drow";
			if(in == "v") race = "Vampire";
			if(in == "t") race = "Troll";
			if(in == "g") race = "Goblin";

			floor *game[5];
			int level = 1;
			//cout << "player new" << endl;
			player *p = new player(race, NULL);
			floor *currentFloor;
			int currentLevel;

			while(level <= 5){
				//cout << "floor" << endl;
				floor *f = new floor(NULL,level);
				
				game[level-1] = f;
				/*floor *f = new floor(p, 2);
				p->setFloor(f);*/

				if(argc == 1){
					//cout << "here0" << endl;
					f->spawnPlayer(p);
					//cout << "player" << endl;
					f->spawnPotion();
					//cout << "potion" << endl;
					f->spawnGold();
					//cout << "gold" << endl;
					f->spawnMobs();
					//cout << "mob" << endl;
				}else if(argc == 2){
					string sourse = argv[1];
					//cout << "read" << endl;
					f->readin(sourse, p);
				}
				level++;
			}

			currentLevel = 1;
			currentFloor = game[0];

			cell *initial = currentFloor->findPlayer();
			p->setCord(initial->getRow(),initial->getCol());
			p->setFloor(currentFloor);

			isHostail = false;

			currentFloor->printMap();
			
			
			while(cin>>in){
				if(in == "u"){
					cin >> in;
					//cout << "hereuse" << endl;
					currentFloor->usePotion(in);
					p->move(in);
				}else if(in == "q"){
					break;
				}else if(in == "a"){
					cin >> in;
					//cout << "hereattack" << endl;
					currentFloor->playerAtk(in);
				}else if(in == "r"){
					cout << "Enter y to confirm restart:" << endl;
					cin >> in;
					if (in == "y"){
						break;
					}else{
						cout << "Game continue" << endl;
					}
				}else{
					//cout << "heremove" << endl;
					p->move(in);
				}
				p->recover(5); // troll recover
				//cout << "here2" << endl;
				currentFloor->moveMobs();
				//cout << "here3" << endl;
				//insert go uptairs
				if(goUpStair){
					currentLevel++;
					if(currentLevel > 5){ // let's end this game
						cout << "You have reached the void floor! You win!" << endl;
						cout << "Your score is: "<< endl;
						int score = p->getGold();
						if(p->getRace() == "Shade") score = (score*3)/2;
						cout << score << endl << endl;
						cout << "Restart the game? if yes, type y; if no, type any other characters." << endl;
						cin >> in;
						if(in != "y") in = "q";
						break;
					}else{
						currentFloor = game[currentLevel-1];
						initial = currentFloor->findPlayer();
						p->setCord(initial->getRow(),initial->getCol());
						p->setFloor(currentFloor);
						p->restore(); // reset potion stat
					}
					goUpStair = false;
				}

				currentFloor->printMap();

				if(p->getHp() <= 0){
					cout << "You are dead." << endl;
					cout << "Your score is: "<< endl;
					int score = p->getGold();
					if(p->getRace() == "Shade") score = (score*3)/2;
					cout << score << endl << endl;
					cout << "Restart the game? if yes, type y; if no, type any other characters." << endl;
					cin >> in;
					if(in != "y") in = "q";
					break;
				}
			}
			delete game[1];
			delete game[2];
			delete game[3];
			delete game[4];
			delete game[0];
			delete p;
			currentFloor = NULL;
			p = NULL;
		} // end while
	}//end if
}

