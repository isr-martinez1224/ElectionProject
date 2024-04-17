//Created by: Israel Martinez
//Modify by: Emmanuel Portillo
/* This class provides main functionality to the
voter user
Main Points: View Potential Candidates, Cast a vote
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "CastVote.h"
#include "PollManagement.h"

using namespace std;



class Voter
{
public: //Methods
	Voter(string, int);

	void setName(string);
	void setUserID(int);
	int getUserID();
	string getName();

	void menu();
	void castVote();
	void viewCandidates();
	void selectPoll();



private: //data
	string name;
	int userID;
	string VoteSelection;
	string PollSelection;
	vector<string> openPolls;

	CastVote vote = CastVote();
	PollManagement poll = PollManagement();
};


//Constructor
Voter::Voter(string n, int id) {
	name = n;
	userID = id;
}


//Getters + Setters
void Voter::setName(string n) {
	name = n;
}
void Voter::setUserID(int id) {
	userID = id;
}
string Voter::getName() {
	return name;
}
int Voter::getUserID() {
	return userID;
}


//Methods
void Voter::menu() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	bool menu = true;
	while (menu) {
		int choice;

		system("cls");
		cout << "Welcome Voter " << name << "!" << endl;
		cout << "----------------------" << endl;
		cout << "\nWhat would you like to do? Please enter a number" << endl;

		cout << "1. View Open Polls" << endl;
		cout << "2. View Potential Candidates" << endl;
		cout << "3. Logout" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			selectPoll();
			break;
		case 2:
			viewCandidates();
			break;
		case 3:
			cout << "Good Bye " << name << "!" << endl;
			menu = false;
			system("pause");
			break;
		default:
			cout << "Invalid choice detected try again please" << endl;
			system("pause");
			break;
		}
	}
}
//View list of open polls, file names, choose which one to add vote in
void Voter::selectPoll() {

	vote.DisplayPolls();
	openPolls = poll.getOpenedPolls();
	cout << "\n" << endl;
	
	bool invalid = true;

	//if there are no polls, display message then go back to menu
	if(openPolls.empty()){
		cout << "No open polls to participate in!" << endl;
		system("pause");
	}
	//else, ask user to select a poll, then select go to select a candidate
	else {
		while (invalid) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Which poll would you like to place a vote for? Please enter the file name with .txt" << endl;

			cin >> PollSelection;
			vote.setPollSelect(PollSelection);
			for (int i = 0; i < openPolls.size(); i++) {
				if (PollSelection == openPolls.at(i)) {
					cout << "Poll successfully selected!" << endl;
					invalid = false;
					break;
				}
				else if (i == (openPolls.size() - 1)) {
					cout << "Invalid choice! Please enter a valid poll choice\n" << endl;
				}
			}

		}

		system("pause");
		//go to cast vote
		castVote();
	}

	
}
//Have option to view list of the candidates
void Voter::viewCandidates() {
	system("cls");
	cout << "Potential Candidates you could vote for:\n" << endl;

	ifstream candFile;
	candFile.open("CandidateLogin.txt");

	string currLine = "";
	while (getline(candFile, currLine)) {
		currLine = currLine.substr(0, currLine.find('\t'));
		cout << currLine << endl;
		
	}
	candFile.close();
	system("pause");
}
//Choose a candidate to submit your vote for, then transfer control to CastVote class
void Voter::castVote() {

	system("cls");
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Here are the candidates for " + PollSelection << endl;
	

	vote.DisplayCandidates();
	vector<string> list = vote.getListOfCandidates();
	cout << endl;

	bool notInPoll = true;
	while (notInPoll) {
		cout << "\nPlease enter the name of the candidate you want to vote for:" << endl;
		getline(cin, VoteSelection);

		for (int i = 0; i < list.size(); i++) {
			if (VoteSelection == list[i]) {
				notInPoll = false;
				break;
			}
			else if (i == (list.size() - 1)) {
				cout << "That is not a candidate choice! Try again\n" << endl;
			}
		}
	}
	vote.WriteVoteToFile(VoteSelection, userID);
	system("pause");	
}
