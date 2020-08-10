#ifndef _LIGHT_
#define _LIGHT_

#include "Constant.h"
#include "Car.h"
#include "Movable.h"

class Car;

class Light {
private:
	int row = -1;
	bool state = false;
	int countStep = 1;
	vector<Car*> listCar;
public:
	Light(int row);
	int getRow();
	bool getState();
	void add(Car* car);
	void remove(Car* car);
	void update();
	void notify();
};

#endif