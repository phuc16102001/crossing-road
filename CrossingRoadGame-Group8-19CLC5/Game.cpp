#include "Game.h"

Game::Game() {
	srand(time(NULL));
	console.init();

	player = new Player;
	player->setAlive(false);
}

Game::~Game() {
	clearGarbage();
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

void Game::levelUp() {
	level++;
	nObjects++;

	levelRow += rowLevelUp;
	playerScore += scoreLevelUp;

	createLevel();
}

bool Game::menu() {
	int choice = getMenuChoice();

	switch (choice) {
		case (0): {
			string newName = getNewPlayerName();
			
			player->setRow(0);
			player->setCol(maxCol / 2);
			player->setName(newName);
			player->setAlive(true);
			
			level = 1;
			playerScore = 0;
			levelRow = 5;
			nObjects = 1;

			createLevel();
			break;
		}
		case (1): {
			//Load game
			break;
		}
		case (2): {
			//Setting
			break;
		}
		case (3): {
			//drawInfo();
			menu();
			break;
		}
		case (4): {
			exit(0);
			break;
		}
	}

	if (choice == 0 || choice == 1) return true;
	return false;
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

void Game::createLevel() {
	clearGarbage();
	for (int iRow = 1; iRow < levelRow - 1; iRow++) {
		bool toRight = rand() % 2;
		int type = rand() % 5;

		Light* light = nullptr;
		if (type > 2) {
			light = new Light(iRow);
			listLight.push_back(light);
		}

		if (type != constantNull) {
			for (int j = 0; j < nObjects; j++) {

				int row = iRow;
				int col = j * maxCol / (1 + nObjects) + 1;
				if (!toRight) {
					col = maxCol - col;
				}

				Movable* enemy = nullptr;
				switch (type) {
				case (constantBat):
					enemy = new Bat(row, col);
					break;
				case (constantDuck):
					enemy = new Duck(row, col);
					break;
				case (constantTruck):
					enemy = new Truck(row, col, light);
					break;
				case (constantBicycle):
					enemy = new Bicycle(row, col, light);
					break;
				}

				enemy->setToRight(toRight);
				listEnemy.push_back(enemy);
			}
		}
	}
	player->setRow(0);
}

void Game::updateMoving(char moving) {
	switch (moving) {
	case ('W'): {
		player->move(UP);
		break;
	}
	case ('S'): {
		player->move(DOWN);
		break;
	}
	case ('A'): {
		player->move(LEFT);
		break;
	}
	case ('D'): {
		player->move(RIGHT);
		break;
	}
	}
	updateMinRow();
}


void Game::updateMovable() {
	for (int i = 0; i < listEnemy.size(); i++) {
		listEnemy[i]->update();
	}
	for (int i = 0; i < listLight.size(); i++) {
		listLight[i]->update();
	}
}

void Game::clearGarbage() {
	for (int i = 0; i < listEnemy.size(); i++) {
		delete listEnemy[i];
	}
	for (int i = 0; i < listLight.size(); i++) {
		delete listLight[i];
	}
	listEnemy.clear();
	listLight.clear();
}

void Game::gameOver() {

	player->setAlive(false);
	int row = player->getRow();
	int col = player->getCol();

	for (int i = 0; i < 20; i++) {
		drawBorder(i);
		drawLegend(i);
		Sleep(100);
	}

	console.setTextColor(colorWhite);
	console.clrscr();
	fstream GameOver("GameOverFile.txt", ios::in);
	console.drawTextFromFile(GameOver, gameOverX, gameOverY);
	GameOver.close();
	Sleep(3000);

	//drawScoreBoard();
	Sleep(3000);
}


void Game::draw() {
	//Clear screen and draw border, legend, object (player + enemy + lights)
	console.clrscr();
	drawBorder(colorMint);
	drawLegend(colorWhite);
	drawObject();
	
	//For easier to see
	console.gotoXY(0, gameWindowY + 1);
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

void Game::drawLegend(int color) {
	console.setTextColor(color);
	console.gotoXY(playerNameX, playerNameY);
	cout << "Player name: " << player->getName();

	console.gotoXY(levelX, levelY);
	cout << "Level: " << level;

	console.gotoXY(scoreX, scoreY);
	cout << "Score: " << playerScore;

	console.gotoXY(nObjectX, nObjectY);
	cout << "Object: " << nObjects;
}

void Game::drawObject() {
	int sizeOfLanes = (gameWindowY - nLanes) / nLanes;

	//Draw player
	int col = player->getCol();
	int row = player->getRow();
	row = (row - minRow) * (sizeOfLanes + 1) + (sizeOfLanes / 2);
	console.drawString(player->getImgString(), col, row, false);

	//Draw enemy
	for (int i = 0; i < listEnemy.size(); i++) {
		Movable* enemy = listEnemy[i];
		col = enemy->getCol();
		row = enemy->getRow();

		if (row >= minRow && row < minRow + nLanes) {
			row = (row - minRow) * (sizeOfLanes + 1) + (sizeOfLanes / 2);
			console.drawString(enemy->getImgString(), col, row, !enemy->getToRight());
		}
	}

	//Draw light
	for (int i = 0; i < listLight.size(); i++) {
		Light* light = listLight[i];
		row = light->getRow();
		bool state = light->getState();

		vector<string> lightImg;
		lightImg.push_back({ char(219) });
		if (row >= minRow && row < minRow + nLanes) {
			if (state) {
				console.setTextColor(colorGreen);
			}
			else {
				console.setTextColor(colorRed);
			}

			col = 1;
			row = (row - minRow) * (sizeOfLanes + 1) + 1;
			console.drawString(lightImg, col, row, false);
		}
	}

	//Draw finish line
	if (minRow == levelRow - nLanes) {
		for (int i = 0; i < sizeOfLanes; i++) {
			for (int j = 1; j < gameWindowX * 3 / 4 - 1; j++) {
				console.gotoXY(j, (nLanes - 1) * (sizeOfLanes + 1) + 1 + i);
				console.setTextColor(colorGreen);
				cout << char(219);
			}
		}
	}
}


void Game::updateMinRow() {
	//int row = player row;
	//If row == levelRow-1 then {levelUp();}
	//
	//lowBound = max(0,row - 1)
	//minRow = min(levelRow-nLanes,lowBound)
}

vector<Movable*> Game::getListEnemy() {
	//Return list enemy;
}
