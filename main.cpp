//Paul Salminen
//main for final project

#include <iostream>
#include <fstream>
#include <sstream>
#include "Basketball.h"
using namespace std;

void input data(char* title) {
	ifstream infile(title);	//Open file
	string inLine;	//Variable to hold each line
	string team1, team2;	//Declare variables for each team in line
	int score1, score2;	//Declare variables for each score in line

	while(!infile_eof()) {
		getline(infile, team1, '\t');	//Get data from each line of file
		getline(infile, score1, '\t');
		getline(infile, team2, '\t');
		getline(infile, score2, '\n');
		bball::addGame(team1, score1, team2, score2);
	}
}

int main(int argc, char * argv[]) {
	char* fileName = argv[1]; 
	Basketball bball;
	//Run options
	cont = true;	//Choice for continuing program
	int choice;	//User input of function to run
	while(cont) {
		mainMenu();	//Print function options
		cin >> choice;	//Input function choice
		switch(choice) {
			case 1:
				break;

			case 2:
				break;

			case 3:
				break;

			case 4:
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

//Function to print operation choices
void mainMenu() {
	cout << "1. " << endl
	<< "2. " << endl
	<< "3. " << endl
	<< "4. " << endl
	<< "5. Quit Program"
}
