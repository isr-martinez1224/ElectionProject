//Created by: Israel Martinez
/* This class provides the main operations to cast a vote as a voter user
There are also some interactions with the PollManagement class in order to 
use other methods such as viewing the candidates and list of open polls
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "PollManagement.h"

using namespace std;



class CastVote 
{
public:
	CastVote();

	void WriteVoteToFile(string, int);
	void listCandidates();
	void DisplayCandidates();
	void DisplayPolls();
	void setPollSelect(string);
	vector<string> getListOfCandidates();

private:

	//int userID;
	PollManagement poll = PollManagement();
	vector<string> listOfCandidates;
	string pollSelect;
};

//Constructor
CastVote::CastVote() {
}

//Methods
//write vote to selected poll file
void CastVote::WriteVoteToFile(string select, int id) {
	ofstream pollFileWrite;
	pollFileWrite.open(pollSelect, ios::app);

	pollFileWrite << id << "\t" << select << "\t\n";

	cout << "Vote successfully submitted!" << endl;
}

//read selected poll file, make a list of candidates based on the second line of the file
void CastVote::listCandidates() {

	//read the poll data from the file
	ifstream pollFile;

	pollFile.open(pollSelect);
	string line;
	int lineCounter = 1;

	//clear list of candidates vector before appending
	listOfCandidates.clear();
	while (getline(pollFile, line)) {
		//get all the candidates into a vector of strings
		if (lineCounter == 2) {
			line = line.substr(12); //candidates:\t 11 then tab
			string candidateName;

			for (int i = 0; i < line.length(); i++) {
				if (line.at(i) != '\t') {
					candidateName += line.at(i);
				}
				else if (line.at(i) == '\t') {
					listOfCandidates.push_back(candidateName);
					candidateName = "";
				}
			}
		}

		lineCounter++;
	}
	

}

//view the list of candidates from the current poll, read the vector
void CastVote::DisplayCandidates() {
	listCandidates();

	cout << "Candidates open for election:" << endl;
	for (int i = 0; i < listOfCandidates.size(); i++) {
		cout << listOfCandidates[i] << "\t";
	}

}

//get the list of polls from the static vector in the PollManagement class
void CastVote::DisplayPolls() {
	poll.ViewPolls();
}

//setter for poll selection
void CastVote::setPollSelect(string poll) {
	pollSelect = poll;
}
//getter for list of candidates in the current poll
vector<string> CastVote::getListOfCandidates() {
	return listOfCandidates;
}
