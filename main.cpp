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
		cout << team1 << " " << tempScoreOne << " " << team2 << " " << tempScoreTwo << endl;
		bball->addGame(team1, atoi(tempScoreOne.c_str()), team2, atoi(tempScoreTwo.c_str()));	//Add game to head;
	}
	in_stream.close();
	cout << "Complete!" << endl;
}

//Function to print operation choices
void mainMenu() {
	cout << "1. Find Team Information" << endl
	<< "2. Print all team information" << endl
	<< "3. Find Team information" << endl
	<< "4. Print Team Ranking" << endl
	<< "5. Quit Program" << endl;
}

int main(int argc, char * argv[]) {
	char* fileName = argv[1]; 	//Command line argument filename
	Basketball* bball;	//Create instance of class
	inputData(fileName, bball);

	bool cont = true;	//Choice for continuing program
	int choice;	//User input of function to run
	string input;	//Used for finding team info
	char yn;
	while(cont) {
		mainMenu();	//Print function options
		cin >> choice;	//Input function choice
		switch(choice) {
			case 1:	//Find team info from game info
				bball->findTeamInfo();
				break;

			case 2:	//Print all teams and their info
				bball->printAllTeams();
				break;

			case 3:	//Find Specific Team info
				cout << "Enter team name" << endl;
				getline(cin, input);
				bball->printTeamInfo(input);
				break;

			case 4:	//Rank Teams
				bball->rankTeams();
				cout << "Would you like to view the rankings ('y' or 'n')?" << endl;
				cin >> yn;
				if(yn == 'y')
					bball->printRankings();
				break;

			case 5:	//Quit Program
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
