#include "Console.h"

void Console::clrscr() {

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

}
void Console::setTextColor(int color) {

}

void Console::drawTextFromFile(fstream& fin, int x, int y) {

}
void Console::drawString(vector<string> s, int x, int y, bool isReverse) {

}