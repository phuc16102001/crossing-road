#ifndef _CAR_
#define _CAR_

#include "Constant.h"
#include "Movable.h"
#include "Light.h"

class Light;

class Car : public Movable {
private:
	bool canMove = false;
	Light* light = nullptr;
public:
	Car(int row, int col, Light* light);
	~Car();
	void update();
	void notify(bool canMove);
};

#endif