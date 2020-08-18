#ifndef _DUCK_
#define _DUCK_

#include "Animal.h"

class Duck : public Animal {
public:
	Duck(int row, int col);

	vector<string> getImgString();
};

#endif