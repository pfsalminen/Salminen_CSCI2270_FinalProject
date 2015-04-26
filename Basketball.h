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
	int losses; //Number of game losses
	int points;	//Total points scored
	float ratios;   //Teams win lost ratio
	int ranking;    //Teams ranking
	Team *next; //Pointer to next team in list
};

struct Game {	//Struct to hold info for each game
	string teamOne;	//First team name
	string teamTwo;	//Second team name
	int scoreOne;	//First teams score
	int scoreTwo;	//Second teams score
	Game *next;	//Next game
};

class Basketball {
	public:
		Basketball();   //Initializer
		virtual ~Basketball();  //Deconstructor
		void addGame(string team1, int score1, string team2, int score2);   //Used to add a game to the list of games
		void addTeam(string name, int score, bool win); //Used to add a new team to the list of teams
		void findTeamInfo();    //Goes through all games to create list of teams, and add team's season information
		void findTeamRatio();   //Used to find the ratio of games won for each team
		void printAllTeams();   //Prints all teams in list with their win/lose ratio
		void printTeamInfo(string teamName);  //Prints all information for a given team
		void ratioRankTeams();   //Ranks teams based on ratio
		void printRankings(string type);   //Prints teams in order of rankings of given type
		void makeRatioRankList();	//Creates linked list in order of ratio rankings
		void makePointsRankList();	//Creates linked list in order of points rankings
		bool checkHead();	//Function to see if team list has been made
		void compareHeads(string name);
	protected:
	private:
		Team *head; //Pointer to list of teams
		Team *ratioHead;	//Pointer to list of teams ranked by winlose ratio
		Team *pointsHead;	//Pointer to list of teams ranked by points scored
		Game *lead; //Pointer to list of games
};

#endif //Basketball_H
