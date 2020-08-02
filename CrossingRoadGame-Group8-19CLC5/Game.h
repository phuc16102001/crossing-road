#ifndef _GAME_
#define _GAME_

#include "Constant.h"
#include "Console.h"  

class Game {
private:
	Console console;
public:
	Game();
	~Game();
	void drawLogo(int x, int y);
};

#endif