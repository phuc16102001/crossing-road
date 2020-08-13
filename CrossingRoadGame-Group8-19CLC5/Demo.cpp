#include "Game.h"
#include "Constant.h"

bool isRunning = false;
char moving = ' ';
Game game;

void subThread() {
//	while (isRunning) {
//		if (game.getPlayer()->isAlive()) {
//			game.updateMoving(moving);
//		}
//		moving = ' ';
//		game.updateMovable();
//		game.draw();
//
//		if (game.getPlayer()->isTouch(game.getListEnemy())) {
//			isRunning = false;
//			game.gameOver();
//		}
//
//		Sleep(delayTimes);
//	}
}

int main() {
	game.menu();

	char tmp = 0;
	thread threadProcess(subThread);
	isRunning = true;
	while (true) {
		tmp = toupper(_getch());	 //Please turn off unikey or else it wont understand 'DD'
		if (game.getPlayer()->isAlive()) {
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
