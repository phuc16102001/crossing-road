#include "Game.h"
#include "Constant.h"

bool isRunning = false;
char moving = ' ';
Game game;

void subThread() {
	while (true) {
		while (isRunning) {
			if (game.getPlayer()->isAlive() && isRunning) {
				game.updateMoving(moving);
				moving = ' ';
				game.updateMovable();
				game.draw();

				if (game.getPlayer()->isTouch(game.getListEnemy())) {
					game.gameOver();
					isRunning = false;
				}
			}

			Sleep(delayTimes);
		}
	}
}

void getKeyboard() {

}

int main() {
	char tmp = 0;
	thread threadProcess(subThread);
	while (true) {
		if (!isRunning) {
			isRunning = game.menu();
		}
		else if (game.getPlayer()->isAlive()) {
			//Please turn off unikey or else it wont understand 'DD'
			tmp = toupper(_getch());	 

			if (isRunning && game.getPlayer()->isAlive()) {
				if (tmp == 'P') {
					SuspendThread(threadProcess.native_handle());
				}
				else if (tmp == 'L') {
					SuspendThread(threadProcess.native_handle());
					if (!game.save()) {
						isRunning = false;
					}
					else {
						ResumeThread(threadProcess.native_handle());
					}
				}
				else {
					ResumeThread(threadProcess.native_handle());
					moving = tmp;
				}
			}
		}
	}
}
