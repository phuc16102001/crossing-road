#ifndef _MOVABLE_
#define _MOVABLE_

#include "Constant.h"

class Movable {
private:
	int row = 0, col = 0;
	bool toRight = true;
public:
	Movable();
	Movable(int row, int col);

	int getCol();
	int getRow();
	bool getToRight();
	bool setRow(int row);
	bool setCol(int col);
	void setToRight(bool toRight);

	bool move(MOVE move);

	virtual void getImgString() = 0;
};

#endif