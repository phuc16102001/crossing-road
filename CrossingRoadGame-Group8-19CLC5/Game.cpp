#include "Game.h"

Game::Game() {
	srand(time(NULL));
	console.init();

	player = new Player;
	player->setAlive(false);
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
	string name = "";
	while (name.length() < 1) {
		//Length must be from 1 to 10
		char c;
		while (true) {
			c = _getch();
			if (c == 13) break;
			if (c == 8 || c == 127) {
				//Backspace
				if (name.length() > 0) {
					cout << "\b \b";
					name.erase(name.length() - 1);
				}
			}
			else if (name.length() < maxNameLength) {
				//Other else
				name += string(1, c);
				cout << c;
			}
		}
	}
	return name;
}

void Game::drawBorder(int color) {
	console.setTextColor(color);
	for (int i = 1; i < gameWindowX; i++) {
		console.gotoXY(i, 0);
		cout << char(205);
		console.gotoXY(i, gameWindowY - 1);
		cout << char(205);
		for (int j = gameWindowY / nLanes; j < gameWindowY; j += gameWindowY / nLanes) {
			if (i < gameWindowX * 3 / 4) {
				console.gotoXY(i, j);
				cout << char(205);
			}
		}
	}

	for (int j = 1; j < gameWindowY - 1; j++) {
		console.gotoXY(0, j);
		cout << char(186);
		console.gotoXY(gameWindowX - 1, j);
		cout << char(186);
		console.gotoXY(gameWindowX * 3 / 4, j);
		cout << char(186);
	}

	console.gotoXY(0, 0);
	cout << char(201);
	console.gotoXY(gameWindowX - 1, 0);
	cout << char(187);
	console.gotoXY(gameWindowX - 1, gameWindowY - 1);
	cout << char(188);
	console.gotoXY(0, gameWindowY - 1);
	cout << char(200);
}

void Game::menu() {
	int choice = getMenuChoice();

	switch (choice) {
		case (0): {
			string newName = getNewPlayerName();
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