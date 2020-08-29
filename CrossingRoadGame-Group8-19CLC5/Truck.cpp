#include "Truck.h"

Truck::Truck(int row, int col, Light* light) : Car(row, col, light) {

}

vector<string> Truck::getImgString() {
	vector<string> img;
	img.push_back({ char(32),char(32),char(32) });
	img.push_back({ char(32),char(244),char(177) });
	img.push_back({ char(219),char(219),char(219) });
	return img;
}

void Truck::makeSound() {
	sound(truckSound, false);
}

int Truck::color() {
	return colorRed;
}