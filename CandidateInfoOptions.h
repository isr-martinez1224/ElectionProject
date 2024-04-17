//Developed by: Dandrei Bryl Mendoza + Cheng Sam Cheang
/* This class applies the functionality for the 
candidate class. It works with PollManagement to see the open polls
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "PollManagement.h"

using namespace std;

class CandidateInfo
{
public:
	CandidateInfo();

	void DisplayCandidates(string);
	void DisplayPolls();

private:
	PollManagement viewPoll = PollManagement();//change to management
};

//constructor
CandidateInfo::CandidateInfo() {
}

//display the other candidates names only from the login file, reads the login file
void CandidateInfo::DisplayCandidates(string name) {
	cout << "Potential Candidates you could face are:\n" << endl;

	ifstream candFile;
	candFile.open("CandidateLogin.txt");

	string currLine = "";
	while (getline(candFile, currLine)) {
		currLine = currLine.substr(0, currLine.find('\t'));
		if (name != currLine) {
			cout << currLine << endl;
		}
	}
	candFile.close();
}

//display the open polls from the static vector, only for viewing (works with the PollManagement class to do this)
void CandidateInfo::DisplayPolls() {
	cout << "Current Election Polls you may be in the running for:\n" << endl;

	if (viewPoll.getOpenedPolls().empty()) {
		cout << "No open election polls..." << endl;
	}
	else {
		for (int i = 0; i < viewPoll.getOpenedPolls().size(); i++) {
			cout << "Poll " << (i + 1) << ": " << viewPoll.getOpenedPolls().at(i) << endl;
		}
	}

}
