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
	if (isMute) {
		mute();
	} 
	else {
		sound(levelUpSound, false);
	}

	level++;
	nObjects++;

	levelRow += (baseNRow + difficulty * deltaNRow);
	playerScore += (baseScore + difficulty * deltaScore);

	createLevel();
}

bool Game::menu() {
	if (isMute) {
		mute();
	} 
	else {
		sound(bgSound, true);
	}

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
			console.clrscr();
			drawBorder(colorMint);
			break;
		}
		case (1): {
			if (load(loadX,loadY)) {
				player->setAlive(true);
				mute();
				console.clrscr();
				drawBorder(colorMint);
				return true;
			}
			break;
		}
		case (2): {
			setting();
			break;
		}
		case (3): {
			clearScoreBoard();
			break;
		}
		case (4): {
			drawInfo();
			break;
		}
		case (5): {
			exit(0);
			break;
		}
	}

	if (choice == 0) {	
		mute();
		return true;
	}
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
	string menu[maxMenuChoice] = { "1. Start game","2. Load game","3. Setting", "4. Clear score board", "5. Information", "6. Exit" };
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
	if (!isMute) {
		if (moving == 'W' || moving == 'S' || moving == 'A' || moving == 'D') {
			player->makeSound();
		}
	}
	updateMinRow();
}
				   
void Game::clearGameScreen() {
	int sizeOfLanes = (gameWindowY - nLanes) / nLanes;
	vector<string> none(sizeOfLanes, string(gameWindowX * 3 / 4-1, ' '));
	for (int i = 1; i < gameWindowY; i += sizeOfLanes + 1) {
		if (!(i >= gameWindowY - (sizeOfLanes + 1) && (minRow + nLanes >= levelRow))) {
			console.drawString(none, 1, i, false);
		}
	}
}

void Game::updateMovable() {
	clearGameScreen();
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

void Game::gameOver(Movable* enemy) {

	if (!isMute) {
		enemy->makeSound();
	}

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

	if (!isMute) {
		sound(gameOverSound, false);
	}
	Sleep(3000);

	drawScoreBoard();
	Sleep(3000);
}

void Game::draw() {
	//Clear screen and draw border, legend, object (player + enemy + lights)
	drawLegend(colorWhite);
	drawObject();
	
	//For easier to see
	console.gotoXY(0, gameWindowY + 1);
}

void Game::drawBorder(int color) {
	console.setTextColor(color);
	
	//Rows
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

	//Columns
	for (int j = 1; j < gameWindowY - 1; j++) {
		console.gotoXY(0, j);
		cout << char(186);
		console.gotoXY(gameWindowX - 1, j);
		cout << char(186);
		console.gotoXY(gameWindowX * 3 / 4, j);
		cout << char(186);
	}
						
	//Corner
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

	console.gotoXY(nLanesX, nLanesY);
	cout << "Lanes: " << levelRow;
}

void Game::drawObject() {
	int sizeOfLanes = (gameWindowY - nLanes) / nLanes;

	//Draw player
	console.setTextColor(player->color());
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
			console.setTextColor(enemy->color());
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
	console.setTextColor(colorGreen);
	if (minRow == levelRow - nLanes) {
		vector<string> finish(sizeOfLanes, string(gameWindowX*3/4-1, char(219)));
		console.drawString(finish, 1, (1 + sizeOfLanes) * (nLanes - 1)+1, false);
	}
}

void Game::updateMinRow() {
	int row = player->getRow();
	if (row == levelRow - 1) {
		levelUp();
		//Update row after levelUp
		row = player->getRow();
	}

	int lowBound = max(0, row - 1);
	minRow = min(levelRow - nLanes, lowBound);
}

vector<Movable*> Game::getListEnemy() {
	return listEnemy;
}

void Game::drawInfo() {
	console.clrscr();
	drawLogo(logoX, logoY);

	console.setTextColor(colorWhite);
	fstream info("InformationFile.txt", ios::in);
	console.drawTextFromFile(info, infoX, infoY);
	info.close();
	
	system("pause");
}

void Game::drawScoreBoard() {
	console.clrscr();
	//Get scoreList and update top 9
	vector<Score> listScore = getScoreBoard();

	vector<string> scoreBoard;
	string header = "====== Score Board ======";
	scoreBoard.push_back(header);
	for (int i = 0; i < listScore.size(); i++) {
		string s = "|";
		string name = listScore[i].getName();
		string stringScore = to_string(listScore[i].getScore());

		s += to_string(i + 1) + ". ";
		s += name;
		for (int j = 0; j < header.length() - 5 - name.length() - stringScore.length(); j++) {
			s += ".";
		}
		s += stringScore;
		s += "|";
		scoreBoard.push_back(s);
	}
	string footer(header.length(),'=');
	scoreBoard.push_back(footer);
	console.drawString(scoreBoard, gameWindowX / 2 - header.length() / 2, gameWindowY / 2 - 9, false);
}

vector<Score> Game::getScoreBoard() {
	//Import old score
	vector<Score> listScore;
	fstream fin(scoreBoardPath, ios::in);
	if (fin.is_open()) {
		while (!fin.eof()) {
			string name;
			int score;
			getline(fin, name);
			fin >> score; fin.ignore();
			if (name != "") {
				listScore.push_back(Score(name, score));
			}
		}
	}
	fin.close();

	//Push currentScore
	listScore.push_back(Score(player->getName(), playerScore));

	//Sort
	sort(listScore.begin(), listScore.end(), compareScore);

	//Write top 9 to file
	fstream fout(scoreBoardPath, ios::out);
	if (fout.is_open()) {
		for (int i = 0; i < min(8, listScore.size()); i++) {
			fout << listScore[i].getName() << endl;
			fout << listScore[i].getScore() << endl;
		}
	}
	fout.close();
	return listScore;
}

bool Game::save() {
	draw();

	//Get in path
	string path;
	console.gotoXY(saveX, saveY);
	console.setTextColor(colorWhite);
	cout << "Save file: ";
	getline(cin, path);
	console.gotoXY(saveX, saveY + 1);

	//Open file
	fstream fileSave(saveFolder + path, ios::out);
	if (fileSave.is_open()) {
		//Global variable
		fileSave << level << " " << playerScore << " " << levelRow << " " << nObjects << " " << isMute << " "<< difficulty << " " << fps << endl;
		fileSave << player->getName() << endl;
		fileSave << player->getRow() << endl << player->getCol() << endl;

		//Light list
		fileSave << listLight.size() << endl;
		for (int i = 0; i < listLight.size(); i++) {
			Light* light = listLight[i];
			fileSave << light->getRow() << " " << light->getCount() << " " << light->getState() << endl;
		}

		//Movable list
		vector<string> typeArr;
		typeArr.push_back("");
		typeArr.push_back(typeid(Bat).name());
		typeArr.push_back(typeid(Duck).name());
		typeArr.push_back(typeid(Truck).name());
		typeArr.push_back(typeid(Bicycle).name());

		fileSave << listEnemy.size() << endl;
		for (int i = 0; i < listEnemy.size(); i++) {
			Movable* movable = listEnemy[i];
			string type = typeid(*movable).name();
			for (int i = 0; i < typeArr.size(); i++) {
				if (type == typeArr[i]) {
					fileSave << i << " ";
					break;
				}
			}
			fileSave << movable->getRow() << " " << movable->getCol() << " " << (movable->getToRight() ? 1 : 0) << endl;
		}

		//Successful
		console.setTextColor(colorGreen);
		cout << "Saved successfully";
		fileSave.close();
	}
	else {
		//Fail
		console.setTextColor(colorRed);
		cout << "Saved fail";
	}

	//Ask continue?
	console.gotoXY(saveX, saveY + 2);
	console.setTextColor(colorWhite);
	cout << "Continue (Y/N)?";
	char c = toupper(_getch());
	if (c == 'Y') return true;
	return false;
}

bool Game::load(int x, int y) {
	console.gotoXY(x, y);
	console.setTextColor(colorWhite);

	//Get in path
	string path;
	cout << "File name: ";
	getline(cin, path);
	console.gotoXY(loadX, loadY + 1);
	
	console.gotoXY(x, y);
	cout << string(gameWindowX - 1 - x, ' ');

	//Open file
	fstream fileSave(saveFolder + path, ios::in);
	if (fileSave.is_open()) {
		clearGarbage();
		fileSave >> level >> playerScore >> levelRow >> nObjects >> isMute >> difficulty >> fps;
		fileSave.ignore();

		string name;
		int playerRow, playerCol;
		getline(fileSave, name);
		player->setName(name);

		fileSave >> playerRow;
		fileSave >> playerCol;
		player->setRow(playerRow);
		player->setCol(playerCol);

		//Light
		int nLight;
		fileSave >> nLight;
		for (int i = 0; i < nLight; i++) {
			int row, state, count;
			fileSave >> row >> count >> state;
			listLight.push_back(new Light(row, state, count));
		}

		//Enemy
		int nMovable;
		fileSave >> nMovable;
		Light* light = nullptr;
		for (int i = 0; i < nMovable; i++) {
			int type, row, col, toRight;
			fileSave >> type >> row >> col >> toRight;

			if (type > 2) {
				if (light == nullptr || light->getRow() != row) {
					for (int j = 0; j < listLight.size(); j++) {
						if (listLight[j]->getRow() == row) {
							light = listLight[j];
						}
					}
				}
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

		//Successful
		fileSave.close();
		return true;
	}
	else {
		//Fail
		console.gotoXY(x, y + 1);
		console.setTextColor(colorRed);
		string fail = "Load fail";
		cout << fail;
		_getch();
		console.gotoXY(x, y + 1);
		cout << string(fail.length(), ' ');
		return false;
	}
}

void Game::setting() {
	console.clrscr();
	drawLogo(logoX, logoY);
	int choice = 0;
	char input = 0;

	//Sound
	while (true){
		console.gotoXY(settingX, settingY);
		if (isMute) {
			console.setTextColor(colorRed);
		}
		else {
			console.setTextColor(colorGreen);
		}
		cout << "Music: " << (isMute ? "OFF" : "ON ");
		input = toupper(_getch());
		if (input == 13) {
			break;
		}
		isMute = !isMute;
	}

	//FPS
	while (true) {
		console.gotoXY(settingX, settingY + 1);
		console.setTextColor(colorYellow);
		cout << "FPS: " << fps << " ";
		input = toupper(_getch());
		if (input == 13) {
			break;
		}
		if (input == 'A') fps = max(minFPS, fps - 1);
		if (input == 'D') fps = min(maxFPS, fps + 1);
	}

	//Difficulty
	while (true) {
		console.gotoXY(settingX, settingY + 2);
		if (difficulty < maxDifficulty / 3) {
			console.setTextColor(colorGreen);
		}
		else if (difficulty < 2 * maxDifficulty / 3) {
			console.setTextColor(colorOrange);
		}
		else {
			console.setTextColor(colorRed);
		}
		cout << "Difficulty: " << difficulty << " ";
		input = toupper(_getch());
		if (input == 13) {
			break;
		}
		if (input == 'A') difficulty = max(minDifficulty, difficulty - 1);
		if (input == 'D') difficulty = min(maxDifficulty, difficulty + 1);
	}
}

void Game::clearScoreBoard() {
	fstream scoreBoard(scoreBoardPath, ios::out);
	scoreBoard.close();
}

int Game::getFPS() {
	return fps;
}