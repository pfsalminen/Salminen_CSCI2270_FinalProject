//Paul Salminen
//Final Project

#include <iostream>
#include <fstream>
using namespace std;

//Initializer
Basketball::Basketball() {
	head = NULL;	//Initially make Team's list null
	lead = NULL;	//Initially make game list null
}

//Add a new game to the linked list
void Basketball::addGame(string team1, int score1, string team1, int score1) {
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
	Team *temp = new team;
	temp->name = name;
	temp->games = 1;
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
		head->ratio = wins / games; 
		head = head->next;
	}
}














































