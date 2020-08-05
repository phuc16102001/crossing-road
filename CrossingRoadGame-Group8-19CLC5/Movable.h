#ifndef _MOVABLE_
#define _MOVABLE_

#include "Constant.h"

class Movable {
private:
	int row, col;
	bool toRight = true;
public:
	Movable();
	Movable(int row, int col);

	bool move(MOVE);

	int getRow();
	int getCol();
	bool setCol(int col);
	bool setRow(int row);
	void setToRight(bool toRight);
	bool getToRight();

	virtual vector<string> getImgString() = 0;
	virtual void update();
};

#endif