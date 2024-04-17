//Written By: Dandrei Bryl Mendoza
/* This class allows an admin to create a new poll file
and close a poll file by removing it from the static vector
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;


class PollManagement
{
public:
	PollManagement();

	void CreatePoll();
	void ClosePoll();
	void ViewPolls();
	vector<string> getOpenedPolls();
	vector<string> getClosedPolls();
	void displayCandidates();


private:
	//static vectors allow the polls to be viewed by any instance of this object
	static vector<string> OpenPolls;
	static vector<string> ClosedPolls;

};

//Define static vector
vector<string> PollManagement::OpenPolls;
vector<string> PollManagement::ClosedPolls;

//Constructor
PollManagement::PollManagement() {
}

//Create a new poll file with list of candidates and name of poll
void PollManagement::CreatePoll() {
	system("cls");
	string pollName = "";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "What would you like to name the poll? Please add .txt at the end" << endl;
	cin >> pollName;

	ofstream pollFile;
	pollFile.open(pollName, ios::app);
	pollFile << "Poll Name:" << "\t" << pollName << "\n";
	pollFile << "Candidates:" << "\t";

	cout << "How many candidates do you want to add?" << endl;
	int numOfCand;
	cin >> numOfCand;

	displayCandidates();
	cout << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < numOfCand; i++) {
		string currName;
		cout << "Name of Candidate " << (i + 1) << ":" << endl;
		
		getline(cin, currName);
		pollFile << currName << "\t";
	}


	pollFile << "\nVotes:\n";
	pollFile.close();
	//push new open poll to the static vector
	OpenPolls.push_back(pollName);

	cout << "\nPoll succussfully created!" << endl;
	system("pause");
}

//Erase selected open poll from static vector and push name to closed polls vector
void PollManagement::ClosePoll() {
	system("cls");
	string pollName = "";

	//show opened polls
	cout << "Opened Polls:\n";
	for (int i = 0; i < OpenPolls.size(); i++) {
		cout << "Poll " << (i + 1) << ": " << OpenPolls.at(i) << endl;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Which poll would you like to close? Please add .txt at the end" << endl;
	cin >> pollName;

	bool found = false;
	int position;
	//search for selected poll in the open polls vector
	for (int i = 0; i < OpenPolls.size(); i++) {
		if (pollName == OpenPolls.at(i)) {
			found = true;
			position = i;
			break;
		}
	}
	//if else conditions if poll was found
	if (found) {
		cout << "Closing Poll: " + pollName << endl;
		ClosedPolls.push_back(pollName);
		OpenPolls.erase(OpenPolls.begin() + position);
	}
	else {
		cout << pollName + " not found" << endl;
	}

	cout << "\nOpened Polls:\n" << endl;
	for (int i = 0; i < OpenPolls.size(); i++) {
		cout << "Poll " << (i + 1) << ": " << OpenPolls.at(i) << endl;
	}
	cout << endl;
	cout << "\nClosed Polls:\n" << endl;
	for (int i = 0; i < ClosedPolls.size(); i++) {
		cout << "Poll " << (i + 1) << ": " << ClosedPolls.at(i) << endl;
	}
	cout << endl;
	system("pause");
}

//View the list of open polls from the vector
void PollManagement::ViewPolls() {
	system("cls");

	cout << "List of open polls:\n";
	for (int i = 0; i < OpenPolls.size(); i++) {
		cout << "Poll " << (i + 1) << ": " << OpenPolls.at(i) << endl;
	}
	system("pause");
}

//Getters
vector<string> PollManagement::getOpenedPolls() {
	return OpenPolls;
}
vector<string> PollManagement::getClosedPolls() {
	return ClosedPolls;
}

//Display candidates list from login file for admin to see ( this can also be used as a list to enter names for the created poll)
void PollManagement::displayCandidates() {
	ifstream LoginFile;
	string currentLine;

	LoginFile.open("CandidateLogin.txt");

	cout << "List of Candidates\n" << endl;

	while (getline(LoginFile, currentLine)) {
		cout << currentLine << endl;
	}
	LoginFile.close();
}
