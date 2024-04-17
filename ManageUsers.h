// Cheng Sam Cheang
/* This class lets an admin view the users in the system
and also gives the option to remove a specific user
*/

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class ManageUsers 
{
public:
	ManageUsers();

	void SearchUsers();
	void RemoveUser();

private:

	string name;
	string userType;
	int userID;

};


//Constructor
ManageUsers::ManageUsers(){
	name = "";
	userType = "";
	userID = 0;
}


//Methods
//admin can view the voter or candidate login files by selecting an option (will read the login file)
void ManageUsers::SearchUsers() {
	system("cls");
	cout << "Which file would you like to search? (1-Voters, 2-Candidates)" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	int input;

	cin >> input;
	ifstream LoginFile;
	string currentLine;
	switch(input){
		case 1: //read voter login file
			system("cls");

			LoginFile.open("VoterLogin.txt",ios::in);

			cout << "List of Voters\n" << endl;

			while (getline(LoginFile, currentLine)) {
				cout << currentLine << endl;
			}

			system("pause");
			LoginFile.close();
        	break;
		case 2: //read candidate login file
		    system("cls");
			
		    
			LoginFile.open("CandidateLogin.txt",ios::in);

			cout << "List of Candidates\n" << endl;
			
			while (getline(LoginFile, currentLine)) {
				cout << currentLine << endl;
			}
			
			system("pause");
			LoginFile.close();
		    break;
		default:
			cout << "Please enter a valid number" << endl;
			system("pause");
			break;
	}


}

//ask admin for user information they want to delete
void ManageUsers::RemoveUser() {
	system("cls");
	cout << "What user do you want to remove? Please enter the following information\n" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Name of user: ";
	getline(cin,name);
	cout << "\nVoter or Candidate? ";

	cin >> userType;
	cout << "\nUser ID #: ";
	cin >> userID;
	string id = to_string(userID);

	ifstream userFile;
	ofstream tempFile; //make a temporary file to rewrite data, delete old file, rename temp as a login file
	string deleteline = (name + "\t") + (id + "\t") + userType;
	string line;

	if (userType == "Voter") { //if voter is to be deleted
		userFile.open("VoterLogin.txt");

		tempFile.open("temp.txt");

		while (getline(userFile, line))
		{
			if (line != deleteline) {
				tempFile << line << endl;
			}
		}

		tempFile.close();
		userFile.close();
		remove("VoterLogin.txt");
		rename("temp.txt", "VoterLogin.txt");
	}
	else if (userType == "Candidate") { //if candidate is to be deleted
		userFile.open("CandidateLogin.txt");

		tempFile.open("temp.txt");

		while (getline(userFile, line))
		{
			if (line != deleteline) {
				tempFile << line << endl;
			}
		}

		tempFile.close();
		userFile.close();
		remove("CandidateLogin.txt");
		rename("temp.txt", "CandidateLogin.txt");
	}
	else {
		cout << "Invalid type detected!" << endl;
	}

	
	system("pause");
}

