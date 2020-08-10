#include "Light.h"

Light::Light(int row) {
	this->row = row;
}

int Light::getRow() {
	return row;
}

bool Light::getState() {
	return state;
}

void Light::add(Car* car) {
	listCar.push_back(car);
}

void Light::remove(Car* car) {
	for (int i = 0; i < listCar.size(); i++) {
		if (car == listCar[i]) {
			listCar.erase(listCar.begin() + i);
			return;
		}
	}
}

void Light::update() {
	countStep--;
	if (countStep == 0) {
		state = !state;
		countStep = rand() % 20 + 8;
		notify();
	}
}

void Light::notify() {
	for (int i = 0; i < listCar.size(); i++) {
		listCar[i]->notify(state);
	}
}