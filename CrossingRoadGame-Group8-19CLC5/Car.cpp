#include "Car.h"

Car::Car(int row, int col, Light* light) : Movable(row, col) {
	//Assign light then add this into Light->add
	light = &Light::Light(row);
	this->light = light;
	Light::add(this->light);
}

void Car::update() {
	//If canMove then Movable::update()
	if (canMove == true) Movable::update();
}

void Car::notify(bool canMove) {
	//Assign this->canMove = canMove
	this->canMove = canMove;
}

Car::~Car() {
	//Call remove this from Light mediator
	Light::remove;
}