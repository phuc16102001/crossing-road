#include "Player.h"

void Player::setName(string name) {
	//Set name
}

string Player::getName() {
	//Get name
}

Player::Player() {
	//Init name = "" and alive = false
}

void Player::setAlive(bool alive) {
	//Set alive
}

bool Player::isTouch(vector<Movable*> listEnemy) {
	//Check all movable*, each one check if the same row and abs(playerRow - objectRow)<3) then return true
	//Otherwise, return false
}

bool Player::isAlive() {
	//Return alive
}

vector<string> Player::getImgString() {
	vector<string> img;
	img.push_back({ char(32),char(234),char(32) });
	img.push_back({ char(218),char(219),char(191) });
	img.push_back({ char(218),char(193),char(191) });
	return img;
}
