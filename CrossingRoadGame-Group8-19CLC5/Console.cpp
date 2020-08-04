#include "Console.h"

void Console::clrscr() {
	system("cls");
}
void Console::init() {
	//Turn off cursor
	ShowCursor(false);

	//Set title
	SetConsoleTitle(APP_NAME);

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
	SetConsoleTextAttribute(console, color);

}

void Console::drawTextFromFile(fstream& fin, int x, int y) {
	gotoXY(x, y);
	string line;
	while (getline(fin, line))
	{
		cout << line << endl;
	}
}
void Console::drawString(vector<string> s, int x, int y, bool isReverse) {

}