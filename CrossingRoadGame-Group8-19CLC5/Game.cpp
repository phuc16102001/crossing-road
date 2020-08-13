#include "Game.h"

Game::Game() {
	console.init();
	srand(time(NULL));
}

Game::~Game() {
	delete player;
}

string Game::getNewPlayerName() {
	system("CLS");
	drawLogo(logoX, logoY);

	console.setTextColor(colorGreen);
	console.gotoXY(newNameX, newNameY);
	cout << "Player name: ";

	console.setTextColor(colorWhite);
	string name;
	getline(cin, name);
	return name;
}

void Game::menu() {
	int choice = getMenuChoice();

	switch (choice) {
		case (0): {
			//string newName = getNewPlayerName();
			//
			//player->setRow(0);
			//player->setCol(maxCol / 2);
			//player->setName(newName);
			//player->setAlive(true);
			//
			//level = 1;
			//playerScore = 0;
			//levelRow = 5;
			//nObjects = 1;

			//createLevel();
			break;
		}
		case (1): {
			//draw();
			break;
		}
		case (2): {
			break;
		}
		case (3): {
			//drawInfo();
			menu();
			break;
		}
		case (4): {
			exit(0);
			return;
		}
	}
}

int Game::getMenuChoice() {
	console.clrscr();
	drawLogo(logoX, logoY);
	int choice = 0;
	char input = 0;

	do {
		drawMenu(menuX, menuY, choice);
		input = toupper(_getch());
		if (input == 'W') {
			choice = (choice - 1 + maxMenuChoice) % maxMenuChoice;
		}
		if (input == 'S') {
			choice = (choice + 1) % maxMenuChoice;
		}
	} while (input != 13);

	return choice;
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