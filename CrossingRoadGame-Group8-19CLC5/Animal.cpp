#include "Animal.h"

Animal::Animal() {
	setRow(0);
	setCol(minCol);
}

Animal::Animal(int row, int col) {
	setRow(row);
	setCol(col);
}