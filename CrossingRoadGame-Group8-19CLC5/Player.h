#ifndef _PLAYER_
#define _PLAYER_

#include <iostream>
#include "Movable.h"
#include "Animal.h"
using namespace std;

class Player : public Movable {
private:
	string name = "";
	bool alive = false;
public:
	Player();

	void setName(string name);
	void setAlive(bool alive);
	string getName();
	bool isAlive();

	Movable* isTouch(vector<Movable*> listEnemy);

	vector<string> getImgString();
};

#endif