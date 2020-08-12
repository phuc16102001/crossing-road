#ifndef _GAME_
#define _GAME_

#include "Constant.h"
#include "Console.h" 
#include "Player.h"
#include "Animal.h"
#include "Car.h"
#include "Movable.h"

class Game {
private:			  
	Player* player = nullptr;
	vector<Movable*> listEnemy;
	vector<Light*> listLight;
	Console console;

	int level = 1;
	int levelRow = 8;
	int nObjects = 2;
	int minRow = 0;
	int score = 0;
public:
	Game();
	~Game();

	void menu();
	void load();
	void save();
	void gameOver();

	int getMenuChoice();
	string getNewPlayerName();

	Player* getPlayer();
	vector<Movable*> getListEnemy();

	void updateMoving(char moving);
	void updateMinRow();
	void updateMovable();
	void levelUp();
	void createLevel();

	void drawLogo(int x, int y);	   	
	void drawMenu(int x, int y, int choice);
	void draw();
	void drawInfo();
	void drawBorder(int color);
	void drawLegend(int color);
	void drawObject();
	void drawScoreBoard();
};

#endif