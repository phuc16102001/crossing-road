#include "Game.h"

Game::Game() {
	console.init();
	srand(time(NULL));
}

Game::~Game() {

}

void Game::drawLogo(int x, int y) {
	//Draw logo
	console.setTextColor(colorMint);

	fstream logo("LogoFile.txt", ios::in);
	
	console.drawTextFromFile(logo, x, y);
	
	logo.close();
}