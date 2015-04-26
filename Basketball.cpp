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

Basketball::~Basketball() {
    //Delete list of games
    Game* dels = new Game;
    dels = lead;
    Game* nexty = new Game;
    while(dels) {
        nexty = dels->next;
        delete(dels);
        dels = nexty;
    }

    //Delete list of teams
    Team* delTems = new Team;
    delTems = head;
    Team* nexter = new Team;
    while(delTems) {
        nexter = delTems->next;
        delete(delTems);
        delTems = nexter;
    }
}

//Add a new game to the linked list
void Basketball::addGame(string team1, int score1, string team2, int score2) {
	Game *n = new Game; //Create temp struct
	n->teamOne = team1; //Set all game info into struct
	n->scoreOne = score1;
	n->teamTwo = team2;
	n->scoreTwo = score2;
	n->next = lead; //But list at end of n (stacks games on top of another)
	lead = n;   //Set list equal to new head
}

//Add a new team to the linked list
void Basketball::addTeam(string name, int score, bool win) {
	Team *temp = new Team;  //Create temp team struct
	temp->name = name;  //Set initial info
	temp->games = 1;    //new Team created when found in game, so they start off with one game
	temp->ranking = -1; //Initial ranking, ranking teams comes later
	temp->points = score;
	if (win) {  //Add wins and losses based on initial game info
		temp->wins = 1;
		temp->losses = 0;
	} else {
		temp->wins = 0;
		temp->losses = 1;
	}
	temp->next = head;  //Add list of teams to new team
	head = temp;    //Update the head list
}

//Function to find raw team data from games
void Basketball::findTeamInfo() {
	bool winOne, winTwo;	//Win loss info from game
    Game *gameTemp = new Game;
    gameTemp = lead;
	while(gameTemp) {	//Determing win loss information for each team
        bool newOne = true;	//To see if team one already exists
        bool newTwo = true;	//See if team two exists
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
			if(tmp->name == gameTemp->teamOne) {    //If team one exists
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
	findTeamRatio();    //Find win/lose ratio for all teams after all teams are entered
}

//Finds win/lose ratio for all teams and adds to struct
void Basketball::findTeamRatio() {
    Team *tmp = new Team;   //Create temp list from head
    tmp = head;
    float tempy;
	while(tmp != NULL) {    //Go through linked list
        tempy = ((float)tmp->wins / (float)tmp->games) * 100;   //Set temp float to raw percentage of wins
        tempy = floor(tempy * 100) / 100;   //Function used to make ratio go to 2 decimal points, will make some teams off be .01 of rounding
        tmp->ratios = tempy;    //Set ratio in team struct equal to the temp ratio
		tmp = tmp->next;
	}
}

//Prints the name of all teams in list along with their W/L ratio
void Basketball::printAllTeams() {
    if (head == NULL) {
        cout << "Team information not yet loaded. Run choice (1) first. " << endl;
        return;
    }
    Team *crawler = new Team;   //Create temp list for printing equal to head
    crawler = head;
	while(crawler->next != NULL) {  //Go through list
		cout << "Team: " << crawler->name << " Win/Lose Ratio: " << crawler->ratios  << "%"<< endl; //Print team names and wl ratios
		crawler = crawler->next;
	}
}

//Prints all information for a specified team
void Basketball::printTeamInfo(string teamName) {
    if (head == NULL) {
        cout << "Team information not yet loaded. Run choice (1) first. " << endl;
        return;
    }
    Team *printer = new Team;   //Create temp head to go through list
    printer = head;
	while(printer) {    //Go through list
		if(printer->name == teamName) { //Print all information in teams struct if its the wanted team
			cout << "\nTeam Name: " << printer->name << endl
				<< "Games played: " << printer->games << endl
				<< "Games won: " << printer->wins << endl
				<< "Games lost: " << printer->losses << endl
				<< "Win/lose ratio: " << printer->ratios << "%" << endl
				<< "Total Points scored: " << printer->points << endl;
			if(printer->ranking != -1)  //Print team ranking if rankings have been found
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
    Team *crawls = new Team;    //Create temp team list from head
    crawls = head;
	for (int i=1; i<=30; i++) { //Go through all ranks
		while(crawls) {   //Go through all teams
			if(crawls->ranking == i)    //If teams ranking equal to the wanted rank, print it
				cout << i << ". " << head->name << endl;
            crawls = crawls->next;
		}
	}
}
