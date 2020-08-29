#include "Bat.h"

Bat::Bat(int row, int col) : Animal(row, col) {
}

vector<string> Bat::getImgString() {
	vector<string> img;

	img.push_back({ char(32),char(32),char(32) });
	img.push_back({ char(223),char(220),char(223) });
	img.push_back({ char(32),char(32),char(32) });

	return img;
}

void Bat::makeSound() {
	sound(batSound, false);
}

int Bat::color() {
	return colorPurple;
}