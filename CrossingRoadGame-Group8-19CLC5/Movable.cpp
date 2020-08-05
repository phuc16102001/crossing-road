#include "Movable.h"

Movable::Movable() {
	row = col = 0;
}

Movable::Movable(int row, int col) {
	this->row = row;
	this->col = col;
}

void Movable::setToRight(bool toRight) {
	this->toRight = toRight;
}

bool Movable::getToRight() {
	return toRight;
}

bool Movable::move(MOVE move) {
	switch (move) {
	case (UP): {
		return setRow(row - 1);
		break;
	}
	case (DOWN): {
		return setRow(row + 1);
		break;
	}
	case (LEFT): {
		return setCol(col - 1);
		break;
	}
	case (RIGHT): {
		return setCol(col + 1);
		break;
	}
	}
}

int Movable::getRow() {
	return row;
}

int Movable::getCol() {
	return col;
}

bool Movable::setCol(int col) {
	if (col < minCol || col >= maxCol) return false;
	this->col = col;
	return true;
}

bool Movable::setRow(int row) {
	if (row < 0) return false;
	this->row = row;
	return true;
}

void Movable::update() {
	if (toRight) {
		if (!move(RIGHT)) {
			setCol(minCol);
		}
	}
	else {
		if (!move(LEFT)) {
			setCol(maxCol - 1);
		}
	}
}