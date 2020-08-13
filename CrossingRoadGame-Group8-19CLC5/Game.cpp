#include "Game.h"

Game::Game() {
	console.init();
	srand(time(NULL));
}

Game::~Game() {
	delete player;
}

void Game::menu() {
	int choice = getMenuChoice();

	//Nothing
}

int Game::getMenuChoice() {
	//Clear screen and drawLogo at logoX logoY
	//int choice = 0; initialize
	//run until press enter {
	//drawMenu(menuX,menuY,choice);
	//char input = _getch(); <- convert to upper letter
	//if W -> choice=(choice-1+maxMenuChoice)%maxMenuChoice	//Move up
	//if S -> choice=(choice+1)%maxMenuChoice				//Move down
	//clue: enter = char(13)
	//}
}

Player* Game::getPlayer() {
	return player;
}

void Game::drawMenu(int x, int y, int choice) {
	string menu[maxMenuChoice] = { "1. Start game","2. Load game","3. Setting", "4. Information","5. Exit" };
	for (int i = 0; i < maxMenuChoice; i++) {
		console.gotoXY(x, y + i);
		if (i == choice) {
			console.setTextColor(colorGreen);
		}
		else {
			console.setTextColor(colorWhite);
		}
		cout << menu[i];
	}
}

void Game::drawLogo(int x, int y) {
	//Draw logo
	console.setTextColor(colorMint);

	fstream logo("LogoFile.txt", ios::in);
	
	console.drawTextFromFile(logo, x, y);
	
	logo.close();
}