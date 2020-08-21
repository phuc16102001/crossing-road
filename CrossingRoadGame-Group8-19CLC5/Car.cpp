#include "Car.h"

Car::Car(int row, int col, Light* light) : Movable(row, col) {
	this->light = light;
	this->canMove = light->getState();
	light->add(this);
}

void Car::update() {
	if (canMove == true) {
		Movable::update();
	}
}

void Car::notify(bool canMove) {
	this->canMove = canMove;
}

Car::~Car() {
	light->remove(this);
}