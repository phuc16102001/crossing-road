#include "Player.h"

void Player::setName(string name) {
	this->name = name;
}

string Player::getName() {
	return name;
}

Player::Player() {
	name = "";
	alive = false;
}

void Player::setAlive(bool alive) {
	this->alive = alive;
}

Movable* Player::isTouch(vector<Movable*> listEnemy) {
	for (int i = 0; i < listEnemy.size(); i++) {
		int row = listEnemy[i]->getRow();
		int col = listEnemy[i]->getCol();
		if (row == getRow() && abs(col - getCol()) < 3) {
			return listEnemy[i];
		}
	}
	return nullptr;
}

bool Player::isAlive() {
	return alive;
}

vector<string> Player::getImgString() {
	vector<string> img;
	img.push_back({ char(32),char(234),char(32) });
	img.push_back({ char(218),char(219),char(191) });
	img.push_back({ char(218),char(193),char(191) });
	return img;
}
