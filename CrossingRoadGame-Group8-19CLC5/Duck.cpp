#include "Duck.h"

Duck::Duck(int row, int col) : Animal(row, col) {
}

vector<string> Duck::getImgString() {
	vector<string> img;

	img.push_back({ char(32),char(32),char(32) });
	img.push_back({ char(32),char(219),char(16) });
	img.push_back({ char(223),char(223),char(32) });

	return img;
}

void Duck::makeSound() {
	sound(duckSound, false);
}

int Duck::color() {
	return colorYellow;
}