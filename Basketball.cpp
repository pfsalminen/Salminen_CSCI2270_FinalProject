//Paul Salminen
//Final Project

#include <iostream>
#include <fstream>
#include "Basketball.h"
using namespace std;

//Initializer
Basketball::Basketball() {
	head = NULL;	//Initially make Team's list null
	lead = NULL;	//Initially make game list null
}

//Add a new game to the linked list
void Basketball::addGame(string team1, int score1, string team2, int score2) {
	Game *n = new Game;
	n->teamOne = team1;
	n->scoreOne = score1;
	n->teamTwo = team2;
	n->scoreTwo = score2;
	n->next = lead;
	lead = n;
}

//Function to find raw team data from games
void Basketball::findTeamInfo() {
	bool newOne = true;	//To see if team one already exists
	bool newTwo = true;	//See if team two exists
	bool winOne, winTwo;	//Win loss info from game
	while(lead) {	//Determing win loss information for each team
		if(lead->scoreOne > lead->scoreTwo) {	//Determine win lose info
			winOne = true;
			winTwo = false;
		} else {
			winTwo = true;
			winOne = false;
		}

		while(head) {	//See if team already exists
			if(head->name == lead->teamOne) {	//If team one exists
				newOne = false;	//Team is found
				head->games++;		//Update team information
				head->points = head->points + lead->scoreOne;
				if (winOne)
					head->wins++;
				else
					head->losses++;
			}else if(head->name == lead->teamTwo) {	//If team two exists
				newTwo = false;	//Team is found
				head->games++;	//Update team information
				head->points = head->points + lead->scoreTwo;
				if (winTwo)
					head->wins++;
				else
					head->losses++;
			}
			head = head->next;
		}

		if (newOne)	//If team one isnt found, add a new team
			addTeam(lead->teamOne, lead->scoreOne, winOne);
		if(newTwo)	//If team two isnt found, add a new team
			addTeam(lead->teamTwo, lead->scoreTwo, winOne);

		lead = lead->next;
	}

	findTeamRatio();
}

//Add a new team to the linked list
void Basketball::addTeam(string name, int score, bool win) {
	Team *temp = new Team;
	temp->name = name;
	temp->games = 1;
	temp->ranking = -1;
	temp->points = score;
	if (win) {
		temp->wins = 1;
		temp->losses = 0;
	} else {
		temp->wins = 0;
		temp->losses = 1;
	}
	temp->next = head;
	head = temp;
}

void Basketball::findTeamRatio() {
	while(head) {
		head->ratio = (head->wins / head->games) * 100;
		head = head->next;
	}
}


void Basketball::printAllTeams() {
	while(head) {
		cout << head->name << head->ratio << head->points << endl;
		head = head->next;
	}
}

void Basketball::printTeamInfo(string teamName) {
	while(head) {
		if(head->name == teamName) {
			cout << "Team Name " << head->name << endl
				<< "Games played " << head->games << endl
				<< "Games won " << head->wins << endl
				<< "Games lost " << head->losses << endl
				<< "Win/lose ratio " << head->ratio << endl
				<< "Total Points scored " << head->points << endl;
			if(head->ranking != -1)
				cout << "Team Ranking " << head->ranking << endl;
		}
		head = head->next;
	}
}

//Rank all teams based on win/lose ratio
void Basketball::rankTeams() {
	//
}

//Function to print all team names in order of rank
void Basketball::printRankings() {
	for (int i=1; i<=30; i++) {
		while(head) {
			if(head->ranking == i)
				cout << i << ". " << head->name << endl;
		}
	}
}






































