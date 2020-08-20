#include "Score.h"

Score::Score(string name, int score) {
	this->name = name;
	this->score = score;
}
string Score::getName() const {
	return name;
}
int Score::getScore() const{
	return score;
}

bool compareScore(const Score& scoreA, const Score& scoreB) {
	return (scoreA.getScore() > scoreB.getScore());
}