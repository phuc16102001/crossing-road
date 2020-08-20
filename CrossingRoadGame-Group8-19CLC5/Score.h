#ifndef _SCORE_
#define _SCORE_
#include <string>
using namespace std;

class Score {
private:
	string name;
	int score;
public:
	Score(string name, int score);
	string getName();
	int getScore() const;
};

bool compareScore(const Score& scoreA, const Score& scoreB);

#endif