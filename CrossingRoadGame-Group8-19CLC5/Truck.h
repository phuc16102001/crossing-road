#ifndef _TRUCK_
#define _TRUCK_

#include "Constant.h"
#include "Car.h"
#include "Light.h"

class Truck : public Car {
public:
	Truck(int row, int col, Light* light);
	vector<string> getImgString();
	void makeSound();
	int color();
};

#endif