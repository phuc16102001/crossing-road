#ifndef _ANIMAL_
#define _ANIMAL_

#include "Movable.h"

class Animal : public Movable {
public:
	Animal();
	Animal(int row, int col);
};

#endif