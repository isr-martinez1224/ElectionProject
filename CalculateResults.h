//Cheng Sam Cheang
/* This class performs main operations to read and calulate the results of the 
selected election poll
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "PollManagement.h"

using namespace std;

class Results
{
public:
	Results();

	vector<int> CalculateResults();
	void ReadResults();
	void setPollSelection();

private:

	vector<string> pollCandidates;
	vector<int> pollVotes;
	string selectedPoll;
	PollManagement poll = PollManagement();
};


//Constructor
Results::Results() {

}

//Setter for poll selection, admin chooses which closed poll they want to print a report for
void Results::setPollSelection() {
	//display the closed polls first
	poll.getClosedPolls();
	cout << "Closed Polls - Ready for Reports\n" << endl;
	for (int i = 0; i < poll.getClosedPolls().size(); i++) {
		cout << "Poll " << (i + 1) << ": " << poll.getClosedPolls()[i] << endl;
	}

	bool invalid = true;
	while (invalid) {
		cout << "\nWhich poll do you want to print a report for? Please write the name with .txt" << endl;
		cin >> selectedPoll;

		for (int i = 0; i < poll.getClosedPolls().size(); i++) {
			if (selectedPoll == poll.getClosedPolls()[i]) {
				invalid = false;
				break;
			}
		}
		if (invalid) {
			cout << "Not a valid poll selection! Try again" << endl;
		}
	}

}


//Call read results to gather the results of selected poll, the calculate the winner of the election
vector<int> Results::CalculateResults() {
	system("cls");

	if (poll.getClosedPolls().empty()) {
		cout << "No polls to print a report!" << endl;
	}
	else {
		setPollSelection();
		ReadResults();
		cout << endl;
		cout << "POLL REPORT" << endl;
		//sam code
		unordered_map<string, float> pollPercentageMap;
		int sumvote=0;
		for(int i=0; i<pollVotes.size();i++){
			sumvote+=pollVotes[i];
		}
		for(int i=0; i<pollVotes.size();i++){
			float percentage = (static_cast<float>(pollVotes[i]) / sumvote)*100;
			pollPercentageMap.insert({pollCandidates[i], percentage});
			cout << "Candidate:\t" << pollCandidates[i] << " and their vote percentages is " << percentage << "%" << " with "  << pollVotes[i]  << " votes" << endl;
		}
		float highest = 0.0;
		string winner;
        for (const auto& pair : pollPercentageMap) {
            if (pair.second > highest) {
                highest = pair.second;
                winner = pair.first;
            }
        }
        cout << "\nWinner is " << winner << " and their vote Percentage is " << highest << "% !" << endl;
	}
	pollVotes.clear();
	pollCandidates.clear();

	system("pause");
	return pollVotes;
}


//read the poll data from the file, get the list of candidates of the poll and their votes into 2 vectors (candidates,votes)
void Results::ReadResults() {

	ifstream pollFile;

	pollFile.open(selectedPoll);
	string line;
	int lineCounter = 1;

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
					pollCandidates.push_back(candidateName);
					candidateName = "";
				}
			}
			pollVotes.resize(pollCandidates.size());
			fill(pollVotes.begin(), pollVotes.end(), 0);
		}
		//get all the votes into a vector of integers, update the votes while doing so
		else if (lineCounter >= 4) {
			line = line.substr(9);
			string vote;

			for (int i = 0; i < line.length(); i++) {
				if (line.at(i) != '\t') {
					vote += line.at(i);
				}
				//once we gather the vote, find the candidate in the other vector and add total vote to same position
				else if (line.at(i) == '\t') {
					int canPosition;
					for (int j = 0; j < pollCandidates.size(); j++) {
						if (pollCandidates[j] == vote) {
							pollVotes[j]++;
							break;
						}
					}
				}
			}

		}

		lineCounter++;
	}
	pollFile.close();
}
