//Paul Salminen
//Final Project

#ifndef BASKETBALL_H
#define BASKETBALL_H
#include <iostream>
using namespace std;

struct Team {
	string name;
	int games;
	int wins;
	int losses;
	Team *next;
};

struct Game {
	string teamOne, teamTwo;
	int scoreOne, scoreTwo;
	Game *next;
};

class Baskeball {
	public:
		int findWinRatio();
		int findLossRatio();
	protected:
	private:
		Team *head;
		Game *lead;
};

#endif //Basketball_H
