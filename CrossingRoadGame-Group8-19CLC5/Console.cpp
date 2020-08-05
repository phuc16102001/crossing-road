#include "Console.h"

void Console::clrscr() {
	system("cls");
}

void Console::init() {
	//Turn off cursor
	ShowCursor(false);

	//Fix window and handle
	handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	console = GetConsoleWindow();
	LONG style = GetWindowLong(console, GWL_STYLE);
	style = style & (~WS_MAXIMIZEBOX) & (~WS_THICKFRAME);
	SetWindowLong(console, GWL_STYLE, style);
}

void Console::gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console::setTextColor(int color) {
	SetConsoleTextAttribute(handleConsole, color);
}

void Console::drawString(vector<string> s, int x, int y, bool isReverse) {
	for (int i = 0; i < s.size(); i++) {
		gotoXY(x, y + i);
		if (isReverse) {
			for (int j = s[i].length() - 1; j >= 0; j--) {
				cout << s[i][j];
			}
		}
		else {
			cout << s[i];
		}
	}
}

void Console::drawTextFromFile(fstream& fin, int x, int y) {
	fin.seekg(0, ios::beg);
	while (!fin.eof()) {
		gotoXY(x, y);
		string tmp;
		getline(fin, tmp);
		cout << tmp;
		y++;
	}
}