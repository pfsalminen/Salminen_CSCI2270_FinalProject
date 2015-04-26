//Paul Salminen
//Final Project

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
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
    Game *gameTemp = new Game;
    gameTemp = lead;
	while(gameTemp) {	//Determing win loss information for each team
		if(gameTemp->scoreOne > gameTemp->scoreTwo) {	//Determine win lose info
			winOne = true;
			winTwo = false;
		} else {
			winTwo = true;
			winOne = false;
		}

        Team *tmp = new Team;
        tmp = head;
		while(tmp) {	//See if team already exists
			if(tmp->name == gameTemp->teamOne) {	//If team one exists
				newOne = false;	//Team is found
				tmp->games++;		//Update team information
				tmp->points = tmp->points + gameTemp->scoreOne;
				if (winOne)
					tmp->wins++;
				else
					tmp->losses++;
            }
			if(tmp->name == gameTemp->teamTwo) {	//If team two exists
				newTwo = false;	//Team is found
				tmp->games++;	//Update team information
				tmp->points = tmp->points + gameTemp->scoreTwo;
				if (winTwo)
					tmp->wins++;
				else
					tmp->losses++;
			}
			tmp = tmp->next;
		}
		if (newOne)	//If team one isnt found, add a new team
			addTeam(gameTemp->teamOne, gameTemp->scoreOne, winOne);
		if(newTwo)	//If team two isnt found, add a new team
			addTeam(gameTemp->teamTwo, gameTemp->scoreTwo, winTwo);

		gameTemp = gameTemp->next;
	}
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
    Team *tmp = new Team;
    tmp = head;
    float tempy;
	while(tmp != NULL) {
        tempy = ((float)tmp->wins / (float)tmp->games) * 100;
        tempy = floor(tempy * 100) / 100;
        tmp->ratios = tempy;
		tmp = tmp->next;
	}
}

void Basketball::printAllTeams() {
    Team *crawler = new Team;
    crawler = head;
	while(crawler->next != NULL) {
		cout << "Team: " << crawler->name << " Win/Lose Ratio: " << crawler->ratios  << "%"<< endl;
		crawler = crawler->next;
	}
}

void Basketball::printTeamInfo(string teamName) {
    Team *printer = new Team;
    printer = head;
	while(printer) {
		if(printer->name == teamName) {
			cout << "Team Name: " << printer->name << endl
				<< "Games played: " << printer->games << endl
				<< "Games won: " << printer->wins << endl
				<< "Games lost: " << printer->losses << endl
				<< "Win/lose ratio: " << printer->ratios << "%" << endl
				<< "Total Points scored: " << printer->points << endl;
			if(head->ranking != -1)
				cout << "Team Ranking: " << printer->ranking << endl;
		}
		printer = printer->next;
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
