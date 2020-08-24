#ifndef _BAT_
#define _BAT_

#include "Animal.h"

class Bat : public Animal {
public:
	Bat(int row, int col);

	void makeSound();
	vector<string> getImgString();
};

#endif