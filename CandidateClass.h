//Created by: Israel Martinez

/* This class provides main functionality to the
candidate user
Main Points: View Potential Opponents, View Open Polls
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "CandidateInfoOptions.h"

using namespace std;

class Candidate
{
public: //Methods
	Candidate(string, int);

	void setName(string);
	void setUserID(int);
	int getUserID();
	string getName();

	void menu();
	void viewPolls();
	void viewOtherCandidates();



private: //data
	string name;
	int userID;
	CandidateInfo options = CandidateInfo();
};


//Constructor
Candidate::Candidate(string n, int id) {
	name = n;
	userID = id;
}


//Getters + Setters
void Candidate::setName(string n) {
	name = n;
}
void Candidate::setUserID(int id) {
	userID = id;
}
string Candidate::getName() {
	return name;
}
int Candidate::getUserID() {
	return userID;
}


//Methods
void Candidate::menu() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	bool menu = true;
	while (menu) {
		int choice;

		system("cls");
		cout << "Welcome Candidate " << name << "!" << endl;
		cout << "----------------------" << endl;
		cout << "\nWhat would you like to do? Please enter a number" << endl;

		cout << "1. View Open Polls" << endl;
		cout << "2. View Potential Candidate Opponents" << endl;
		cout << "3. Logout" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			viewPolls();
			break;
		case 2:
			viewOtherCandidates();
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

//send message to candidateInfo class to get open polls vector
void Candidate::viewPolls() {
	system("cls");
	options.DisplayPolls();
	system("pause");
}
//send message to candidateInfo class in order to view the other candidates in the system for potential opponents
void Candidate::viewOtherCandidates() {
	system("cls");
	options.DisplayCandidates(name);
	system("pause");
}
