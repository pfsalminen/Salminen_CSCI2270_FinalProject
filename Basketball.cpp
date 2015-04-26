//Paul Salminen
//Final Project

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include "Basketball.h"
using namespace std;

//Initializer to run when creating new class instance
Basketball::Basketball() {
	head = NULL;	//Initially make Team's list null
	ratioHead = NULL; 	//Initialize ratio ranked list null
	pointsHead = NULL;	//Initialize points ranked list null
	lead = NULL;	//Initially make game list null
}

//Deconstructor to end class
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

/*Addsa new game to the linked list
This is called automatically when function starts
it takes in the team names and scores from each game
From there, it will will create a linked list of every game*/
void Basketball::addGame(string team1, int score1, string team2, int score2) {
	Game *n = new Game; //Create temp struct
	n->teamOne = team1; //Set all game info into struct
	n->scoreOne = score1;
	n->teamTwo = team2;
	n->scoreTwo = score2;
	n->next = lead; //But list at end of n (stacks games on top of another)
	lead = n;   //Set list equal to new head
}

/*Add a new team to the linked list
This is run automatically when building the team information
It takes in the team name, the score of each game, and whether it was a win or lose
From this information it will create a new team in the linked list with this initial information*/
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

/*Function to find raw team data from games
 This is run when the user chooses option 1
 There are no real inputs for this
 It uses the linked list of games
 From there, it either creates a new team in the list
 if it has not been created yet, or it updates the existing team
with the information from each game*/
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

/*Finds win/lose ratio for all teams and adds to struct
This is called at the end of building the linked list
It goes through the list of teams and finds the percentage
of games won to two decimal places*/
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

/*Prints the name of all teams in list along with their W/L ratio
This is called when the user chooses option two
There are no inputs for the user to do
It goes through the list and prints every team name and percentage of games won*/
void Basketball::printAllTeams() {
    Team *crawler = new Team;   //Create temp list for printing equal to head
    crawler = head;
	while(crawler->next != NULL) {  //Go through list
		cout << "Team: " << crawler->name << " Win/Lose Ratio: " << crawler->ratios  << "%"<< endl; //Print team names and wl ratios
		crawler = crawler->next;
	}
}

/*Prints all information for a specified team
This is another function a user can directly call
Before it is called, the user is prompted to enter a team name
It must be entered as City Team, each capitalized
From there, it goes through the list to find the team name
Once found, it prints all the information of a given team*/
void Basketball::printTeamInfo(string teamName) {
    Team *printer = new Team;   //Create temp head to go through list
    printer = head;
	bool display = true;
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
			display = false;
		}
		printer = printer->next;
	}
	if(display) {
		cout << "Team not found. Try again!" << endl;
	}
}

/*Rank all teams based on win/lose ratio
This is another function the user can call
It will assign a ranking to every team primarily based on percentage of games one
If this percentage is equal, it will be distiguished by points scored
There are no inputs the user needs to give
After the ranks are found, it calls a function to create 
a linked list in order of decreasing ranks*/
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
        } else if(teamCtr > 1) {	//If more than one team has same ratio, sort by points
            Team *dupes = new Team;	//Create temp pointers to loop through
            Team *duper = new Team;
            Team *dupeList = new Team;
            dupeList = NULL;	//Originall null to build list
            Team *reverser = new Team;
            reverser = NULL;	//Originally null to build list
            int highPoints = 1000000;   //Impossibly high points
            for (int j=0; j<teamCtr; j++) {
                int curPoints = 0;
                dupes = head;
                while(dupes) {	//Loop through list of teams and find current points
                    if (dupes->points > curPoints && dupes->points < highPoints && dupes->ratios == newRatio)
                        curPoints = dupes->points;
                    dupes = dupes->next;
                }

                duper = head;
                while(duper) {	
                    if (duper->points == curPoints && duper->ratios == newRatio) {	//If team has same ratioa and points
                        Team *tmp = new Team;	//Add team to temp list
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
                    highPoints = curPoints;	//Update points ceiling
                    duper = duper->next;
                }
            }

            while(reverser) {	//Reverse list of teams
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

            int k = i;	//Ranking variable
            while (dupeList) {	//Go through the now correct ordered list
                while (finder) {	//Go through all teams
                    if(finder->name == dupeList->name) {'
                        finder->ranking = k;	//Assign team rank
                        k++;	//Increase ranking variable for the next team of same ratio
                    }
                    finder = finder->next;
                }
                dupeList = dupeList->next;
            }
            i = i + (teamCtr - 1);	//Update i to account for multiple teams of same ratio
        }

		highRat = newRatio;	//Update high ratio limit to the one just found
	}

	makeRatioRankList();	//Make linked list in order of ranking
}

/*Creates linked list of teams based on ratio rankings
This is called after ranking information is found
It goes through the available ranks and all teams
and adds each team in order of increasing rank, with #1 first
There are no inputs needed, and it is called automatically*/
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

/*Creates linked list of teams based on points rankings
This is also called when the user says to find ranking information
There are no inputs needed. It goes through every team and builds
a list in order of increasing points, by stacking teams, then it
reverses the list to be in the correct order*/
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
		while(pointsFinder) {	//find teams with wanted points for this position
			if (pointsFinder->points == curPoints) {
				Team *tmp = new Team;	//Create temp team to add
				tmp->name = pointsFinder->name;
				tmp->games = pointsFinder->games;
				tmp->wins = pointsFinder->wins;
				tmp->losses = pointsFinder->losses;
				tmp->points = pointsFinder->points;
				tmp->ratios = pointsFinder->ratios;
				tmp->ranking = pointsFinder->ranking;
				tmp->next = reverser;	//Stack to list
				reverser = tmp;
			}

			highPoints = curPoints;	//Update point ceiling
			pointsFinder = pointsFinder->next;
		}
	}

	while(reverser) {	//Reverse stacked list to correct order
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


/*Function to print all team names in order of rank
This will print the ranking order of teams,either by points or ratios
When this function is called, the user will by prompted to enter the 
type of list they wish to see. 
The ratio ranking list shows the rank position, team name, and ratio
The points ranking list shows the rank position, team name, and points scored*/
void Basketball::printRankings(string type) {
	if(type == "ratios") {
		if (ratioHead == NULL) {	//Return if list not yet created
			cout << "Ratio rankings not yet found. Please find them first (Option 2)." << endl;
			return;
		}
    	Team *crawls = new Team;    //Create temp team list from head of ratio ranks
    	crawls = ratioHead;
    	cout << "Ratio Rankings:" << endl;
		while(crawls) {   //Go through all teams
			cout << "\t" << crawls->ranking << ". " << crawls->name << " - " << crawls->ratios << endl;	//Print all teams and rank
            crawls = crawls->next;
		}
		cout << endl;
	} else if (type == "points") {
		if (pointsHead == NULL) {	//Return if list not yet created
			cout << "Points rankings not yet found. Please find them first (Option 2)." << endl;
			return;
		}
		Team *crawls = new Team;	//Create temp list from head of points ranks
		crawls = pointsHead;
		int num = 1;
		cout << "Points Rankings:" << endl;
		while (crawls) {
			cout << "\t" << num << ". " << crawls->name << " - " << crawls->points << " points" << endl;
			crawls = crawls->next;
			num++;
		}
		cout << endl;
	} else {
		cout << "Invalid input. Try Again!" << endl;
		return;
	}

}


/*Function to see if the head of the list of teams is null (If it has not been built)
This is a simply function to see if the list of teams has been built yet or not
It is called before most operations are performed from the main function
It it returns false, it will prevent other functions from running so there are no issues*/
bool Basketball::checkHead() {
	if (head == NULL) {	//If list hasnt been built, quit function
        cout << "Team information not yet loaded. Run find them first (Option 1). " << endl;
		return false;
	} else	//Its built!
		return true;
}

/*Function to compare the two different types of rankings
This is another function the user can choose to perform
It takes in the team name they wish to evaluate entertered as
"City Team", it then finds the ratio and points ranking positions, and displays is
After that, an analysis is done to see which rank is higher, and display the difference*/
void Basketball::compareHeads(string name) {
    Team *tempPoint = new Team;	//temp list ordered by points
    tempPoint = pointsHead;
    Team *tempRatio = new Team;	//temp list ordered by ratio
    tempRatio = ratioHead;
    int diff;	//Difference between ranking position
    int ratRank = 0;	//Declare rank holder
    int pointRank = 0;	//Declare rank holder
    int i = 1;	//Used for finding the point ranking
    while(tempRatio) {
        if(tempRatio->name == name) {	//Find desired ratio rank
            ratRank = tempRatio->ranking;
        }
        tempRatio = tempRatio->next;
    }
    while(tempPoint) {
        if (tempPoint->name == name)	//Find desired point rank
            pointRank = i;
        i++;
        tempPoint = tempPoint->next;
    }
    if (ratRank == 0 || pointRank == 0) {	//If team ranks not found
        cout << "Team not found. Try again" << endl;
        return;
    }
    cout << name << ":\n\t Ratio rank - " << ratRank << "\n\t Point Rank - " << pointRank << endl;	//Print team rankings
    if (ratRank == pointRank)	//If ranks are the same
        cout << "They're the same!" << endl;
    else {
        if (ratRank > pointRank) {	//If Ratio is higher, find difference and display
            diff = ratRank - pointRank;
            cout << name << "'s ratio rank is " << diff << " places higher than their point rank." << endl;
        } else {	//If Point rank is higher, find difference and display
            diff = pointRank - ratRank;
            cout << name << "'s point rank is " << diff << " places higher than their ratio rank." << endl;
        }
    }
}
