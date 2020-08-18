#ifndef _BICYCLE_
#define _BICYCLE_

#include "Constant.h"
#include "Car.h"
#include "Light.h"

class Bicycle : public Car {
public:
	Bicycle(int row, int col, Light* light);
	vector<string> getImgString();
};

#endif