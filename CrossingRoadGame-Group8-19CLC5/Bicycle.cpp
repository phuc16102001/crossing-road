#include "Bicycle.h"

Bicycle::Bicycle(int row, int col, Light* light) : Car(row, col, light) {

}

vector<string> Bicycle::getImgString() {
	vector<string> img;
	img.push_back({ char(32),char(32),char(194) });
	img.push_back({ char(219),char(223),char(219) });
	img.push_back({ char(48),char(32),char(48) });
	return img;
}

void Bicycle::makeSound() {
	sound(bicycleSound, false);
}

int Bicycle::color() {
	return colorBlue;
}