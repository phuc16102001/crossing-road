#ifndef _CONSOLE_
#define _CONSOLE_

#include "Constant.h"

class Console {
private:
	HWND console;
	HANDLE handleConsole;
public:
	void clrscr();
	void init();
	void gotoXY(int x, int y);
	void setTextColor(int color);

	void drawTextFromFile(fstream& fin, int x, int y);
	void drawString(vector<string> s, int x, int y, bool isReverse);
};

#endif