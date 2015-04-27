# CSCI2270 Data Structures Final Project

## Group Members:
Davis Kessler, Paul Salminen

### Project Description:
In this project, we will be creating a class to analyze Basketball information to provide statistics based on the data received. The data we used is a tsv file included in this repo for every game in the 2014-2015 Regular season. However, it is accepted as a command line argument, so you can use any file you like. Each line has each team that played in a game, along with each scores. All files used for this program must be in the form "Team TAB Score TAB Team TAB Score". From this, we will find the wins, losses, win/lose ratio, and number of points scored for each team. This is done by running option one when the program starts. After this, the user can run option 2, which will create lists ranking the teams in both decreasing wins/games ratio, and decreasing points scored during the season. After This is done there are a few options to view about this data. You can ask to view minor information about every team, all information about a specific team, or view the rankings for every team.

This project was completed using multiple linked lists. While this is a simple way to store the data, it is very efficient for going through all the information, which is common in the program. 
It's also worth noting that the tsv file was created based on the following website: http://www.landofbasketball.com/results/2014_2015_scores_full.htm


### How to run:
The information will come from a tsv file, and  will be inputted as a command line arguement. From there, you will be given choices of different kinds of information to find, along with different ways to display it. The documentation for every function is described in detail in the "Basketball.cpp" file.

### System Requirements:
This project was built on Fedora Linux and Mac. However, there should be no requirements to run this program except for a c++ compiler.

#### Contributors
The website "http://landofbasketball.com" for providing the information supplied

#### Dependencies
Nothing specifically. A C++ compiler is a necessity.

#### Open Issues/Bugs
There are no real issues or bugs. Every obvious user issue has been addressed. However, better memory handling woud be very nice (read: beneficial). As for enhancements, just some simple analysis/views have been done, there are limitless more things to find with this data.
