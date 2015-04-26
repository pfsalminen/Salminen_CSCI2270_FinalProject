//Paul Salminen
//main for final project

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "Basketball.h"
using namespace std;

void inputData(char* title, Basketball* bball) {
	cout << "Loading 2014-15 Regular Season Game Information..." << endl;
	string inLine;	//Variable to hold each line
	string team1, team2;	//Declare variables for each team in line
	string tempScoreOne, tempScoreTwo;  //Score variables

	ifstream in_stream;
    in_stream.open(title);
    while(!in_stream.eof()) {
		getline(in_stream, team1, '\t');	//Get data from each line of file
		getline(in_stream, tempScoreOne, '\t');
		getline(in_stream, team2, '\t');
		getline(in_stream, tempScoreTwo);
		bball->addGame(team1, atoi(tempScoreOne.c_str()), team2, atoi(tempScoreTwo.c_str()));	//Add game to head;
	}
	in_stream.close();  //Closed command line argument file
	cout << "Complete!" << endl;
}

//Function to print operation choices
void mainMenu() {
	cout << "1. Find Team Information" << endl
	<< "2. Find Team Rankings" << endl
	<< "3. Print All Teams" << endl
	<< "4. Find Team Information" << endl
	<< "5. Print Team Rankings" << endl
	<< "6. Quit Program" << endl;
}

int main(int argc, char * argv[]) {
	char* fileName = argv[1]; 	//Command line argument filename
	Basketball* bball =  new Basketball;	//Create instance of class
	inputData(fileName, bball); //Calls function to input game data

	bool cont = true;	//Choice for continuing program
	int choice;	//User input of function to run
	string input;	//Used for finding further information
	cout << "Option 1 must be the first function run to build information!" << endl;    //Announced necessary program start
	while(cont) {
		mainMenu();	//Print function options
		cin >> choice;  //clear cin
		cin.clear();
        cin.ignore(1000, '\n');	//Input function choice
		switch(choice) {    //Run based on users choice
			case 1:	//Find team info from game info
                cout << "Finding... " << endl;
				bball->findTeamInfo();  //Finds all team info from game info
				cout << "\tTeam information has been found!" << endl;
				break;
			
			case 2:	//Finds ration and points rankings
				cout << "Finding team rankings... " << endl;
				bball->ratioRankTeams();
				bball->makePointsRankList();
				cout << "\tComplete!" << endl;
				break;

			case 3:	//Print all teams and their info
				bball->printAllTeams(); //Brints all teams and their win/games ratio
				break;

			case 4:	//Find Specific Team info
				cout << "Enter team name" << endl;
				getline(cin, input);    //Cin team name to find
				cout << "Searching... " << endl;
				bball->printTeamInfo(input);    //Find team in list and print info
				break;

			case 5:	//Print Ranking lists
				cout << "Enter rank type ('ratios' or 'points')" << endl;
				getline(cin, input);
                bball->printRankings(input); //Prints teams in order of ranking (1-30)
                break;

			case 6:	//Quit Program
				cout << "Goodbye!" << endl;
				cont = false;
				break;

			default:	//Default for answer not 1-5
				cout << "Invalid Choice. True Again: " << endl;
				cin >> choice;
				break;
		}
	}
	return 0;
}
