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
	ratioHead = NULL; 	//Initialize ratio ranked list null
	pointsHead = NULL;	//Initialize points ranked list null
	lead = NULL;	//Initially make game list null
}

Basketball::~Basketball() {
    //Delete list of games
    Game* dels = new Game;	//Temp list of games
    dels = lead;
    Game* nexty = new Game;	//To hold next game in list
    while(dels) {	//Go through list of games
        nexty = dels->next;	//Set next pointer to the next game in list
        delete(dels);	//Delete current game in list
        dels = nexty;	//Set current to next to loop through
    }

    //Delete list of teams
    Team* delTems = new Team;	//Temp list of teams
    delTems = head;
    Team* nexter = new Team;	//Hold next team in list
    while(delTems) {	//Go through list of teams
        nexter = delTems->next;	//Set next pointer to next team in list
        delete(delTems);	//Delete current team in list
        delTems = nexter;	//Set current to next to loop through
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
    Game *gameTemp = new Game;	//Temp list of games
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

        Team *tmp = new Team;	//Temp list of teams updated for each game
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



		if (newOne)	//If team one isnt found, add as new team
			addTeam(gameTemp->teamOne, gameTemp->scoreOne, winOne);
		if(newTwo)	//If team two isnt found, add as new team
			addTeam(gameTemp->teamTwo, gameTemp->scoreTwo, winTwo);

		gameTemp = gameTemp->next;
	}
	findTeamRatio();    //Find win/lose ratio for all teams after all teams are created
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
    if (head == NULL) {	//If list hasnt been built, quit function
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
    if (head == NULL) {	//If list hasnt been built, quit function
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
void Basketball::ratioRankTeams() {
	Team *finder = new Team;	//Create temp list of teams
	Team *dupeFinder = new Team;
	Team *ranker = new Team;	//Temp list of teams to go through
	float highRat = 101;	//Highest ratio, to be updated

	for(int i=1; i<=30; i++) {	//Go through all ranks to assign teams
        int teamCtr = 0; //used to see if teams have same ratios
		float newRatio = 0;	//Used to find correct team for rank

		ranker = head;
		while(ranker->next != NULL) {	//Finds highest ratio lower than the highest before it
			if(ranker->ratios > newRatio && ranker->ratios < highRat)
				newRatio = ranker->ratios;
			ranker = ranker->next;
		}

		dupeFinder = head;
		while(dupeFinder) {
            if (dupeFinder->ratios == newRatio)
                teamCtr++;
            dupeFinder = dupeFinder->next;
		}


		finder = head;	//Temp list of teams to assert rank
		if (teamCtr == 1) {
            while(finder) {	//Go through all teams
                if(finder->ratios == newRatio) {	//If we found the correct team
                    finder->ranking = i;	//Set teams rank to current one being found
                }
                finder = finder->next;
            }
        } else if(teamCtr > 1) {
            Team *dupes = new Team;
            Team *duper = new Team;
            Team *dupeList = new Team;
            dupeList = NULL;
            Team *reverser = new Team;
            reverser = NULL;
            int highPoints = 1000000;   //Impossibly high points
            for (int j=0; j<teamCtr; j++) {
                int curPoints = 0;
                dupes = head;
                while(dupes) {
                    if (dupes->points > curPoints && dupes->points < highPoints && dupes->ratios == newRatio)
                        curPoints = dupes->points;
                    dupes = dupes->next;
                }

                duper = head;
                while(duper) {
                    if (duper->points == curPoints && duper->ratios == newRatio) {
                        Team *tmp = new Team;
                        tmp->name = duper->name;
                        tmp->games = duper->games;
                        tmp->wins = duper->wins;
                        tmp->losses = duper->losses;
                        tmp->points = duper->points;
                        tmp->ratios = duper->ratios;
                        tmp->ranking = duper->ranking;
                        tmp->next = reverser;
                        reverser = tmp;
                    }
                    highPoints = curPoints;
                    duper = duper->next;
                }
            }

            while(reverser) {
                Team *temp = new Team;
                temp->name = reverser->name;
                temp->games = reverser->games;
                temp->wins = reverser->wins;
                temp->losses = reverser->losses;
                temp->points = reverser->points;
                temp->ratios = reverser->ratios;
                temp->ranking = reverser->ranking;
                temp->next = dupeList;
                dupeList = temp;
                reverser = reverser->next;
            }

            int k = i;
            while (dupeList) {
                while (finder) {
                    if(finder->name == dupeList->name) {
                        finder->ranking = k;
                        k++;
                    }
                    finder = finder->next;
                }
                dupeList = dupeList->next;
            }
            i = i + (teamCtr - 1);
        }

		highRat = newRatio;	//Update high ratio limit to the one just found
	}

	makeRatioRankList();
}

//Creates linked list of teams based on ratio rankings
void Basketball::makeRatioRankList() {
	Team *ratioMaker = new Team;	//Temp list of teams
	for(int i=30; i>=1; i--) {	//Go backwards through ranks to stack them into list
		ratioMaker = head;	//Set temp list to head each iteration
		while (ratioMaker) {	//Go though temp list
			if (ratioMaker->ranking == i) {	//If node has desired rank
				Team *newb = new Team;	//Create new team struct
				newb->name = ratioMaker->name;	//Set info equal to current team node
				newb->games = ratioMaker->games;
				newb->wins = ratioMaker->wins;
				newb->losses = ratioMaker->losses;
				newb->points = ratioMaker->points;
				newb->ratios = ratioMaker->ratios;
				newb->ranking = i;
				newb->next = ratioHead;	//Set next to ratio rank list
				ratioHead = newb;		//Update list to include new node
			}
			ratioMaker = ratioMaker->next;
		}
	}
}

//Creates linked list of teams based on points rankings
void Basketball::makePointsRankList() {
	Team *pointsMaker = new Team;	//Temp list of teams
	Team *pointsFinder = new Team;
	Team *reverser = new Team;	//Temp used to reverse list after its built backwards
	reverser = NULL;
	int highPoints = 1000000;	//Impossibly high points ceiling
	for (int i=0; i<30; i++) {
		int curPoints = 0;
		pointsMaker = head;
		while(pointsMaker) {	//Go through list of teams to find highest wanted score
			if (pointsMaker->points > curPoints && pointsMaker->points < highPoints)
				curPoints = pointsMaker->points;
			pointsMaker = pointsMaker->next;
		}

		pointsFinder = head;
		while(pointsFinder) {
			if (pointsFinder->points == curPoints) {
				Team *tmp = new Team;
				tmp->name = pointsFinder->name;
				tmp->games = pointsFinder->games;
				tmp->wins = pointsFinder->wins;
				tmp->losses = pointsFinder->losses;
				tmp->points = pointsFinder->points;
				tmp->ratios = pointsFinder->ratios;
				tmp->ranking = pointsFinder->ranking;
				tmp->next = reverser;
				reverser = tmp;
			}

			highPoints = curPoints;
			pointsFinder = pointsFinder->next;
		}
	}

	while(reverser) {
		Team *temp = new Team;
		temp->name = reverser->name;
		temp->games = reverser->games;
		temp->wins = reverser->wins;
		temp->losses = reverser->losses;
		temp->points = reverser->points;
		temp->ratios = reverser->ratios;
		temp->ranking = reverser->ranking;
		temp->next = pointsHead;
		pointsHead = temp;
		reverser = reverser->next;
	}
}


//Function to print all team names in order of rank
void Basketball::printRankings(string type) {
	if(type == "ratios") {
		if (ratioHead == NULL) {	//Return if list not yet created
			cout << "Ratio rankings not yet found. Please find them first" << endl;
			return;
		}
    	Team *crawls = new Team;    //Create temp team list from head of ratio ranks
    	crawls = ratioHead;
		while(crawls) {   //Go through all teams
			cout << crawls->ranking << ". " << crawls->name << endl;	//Print all teams and rank
            crawls = crawls->next;
		}
	} else if (type == "points") {
		if (pointsHead == NULL) {	//Return if list not yet created
			cout << "Points rankings not yet found. Please find them first" << endl;
			return;
		}
		Team *crawls = new Team;	//Create temp list from head of points ranks
		crawls = pointsHead;
		while (crawls) {
			cout << crawls->points << " points for " << crawls->name << endl;
			crawls = crawls->next;
		}
	} else {
		cout << "Invalid input. Come on!" << endl;
		return;
	}

}
