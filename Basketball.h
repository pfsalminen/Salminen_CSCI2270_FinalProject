//Paul Salminen
//Final Project

#ifndef BASKETBALL_H
#define BASKETBALL_H
#include <iostream>
using namespace std;

struct Team {	//Team information
	string name;	//Team Name
	int games;	//Total number of games
	int wins;	//Number of wins
	int losses;
	int points;	//Total points scored
	float ratio;
	Team *next;
};

struct Game {	//Struct to hold info for each game
	string teamOne;	//First team name
	string teamTwo;	//Second team name
	int scoreOne;	//First teams score
	int scoreTwo;	//Second teams score
	Game *next;	//Next game
}

class Baskeball {
	public:	
		Basketball();
		void addGame(string team1, int score1, string team1, int score1);
		void addTeam(string name, int score, bool win);
		void findTeamInfo();
		void findTeamRatio();
	protected:
	private:
		Team *head;
		Game *lead;
};

#endif //Basketball_H
