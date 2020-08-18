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

int main() {
	char tmp = 0;
	thread threadProcess(subThread);
	while (true) {
		if (!isRunning) {
			isRunning = game.menu();
		}
		else if (game.getPlayer()->isAlive()) {
			tmp = toupper(_getch());	 //Please turn off unikey or else it wont understand 'DD'
			if (tmp == 'P') {
				SuspendThread(threadProcess.native_handle());
			}
			else {
				ResumeThread(threadProcess.native_handle());
				moving = tmp;
			}
		}
	}
}
