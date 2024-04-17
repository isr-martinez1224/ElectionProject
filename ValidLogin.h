//Written by: Israel Martinez

/* This class will allow the user to enter login information
And will also check the corresponding file to validate their information
so that they may continue using the program
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "VoterClass.h"
#include "AdminClass.h"
#include "CandidateClass.h"

using namespace std;

class ValidLogin
{
public:
	ValidLogin();

	void LoginInformation();
	bool CheckUserType(string);
	bool ReadAdminLoginFile();
	bool ReadVoterLoginFile();
	bool ReadCandidateLoginFile();
	void GetLoginInfo(string);
	void CurrentUser();

private:

	string name;
	string userType;
	int userID;
	vector<string> LoginInfo;
};


//Constructor
ValidLogin::ValidLogin() {
	name = "";
	userType = "";
	userID = 0;
}


//Methods
//asks the user to enter their information, validation to make sure they enter a correct type
void ValidLogin::LoginInformation() {
	bool invalid = true;

	while (invalid) {
		system("cls");
		cout << "LOGIN TO SYSTEM" << endl;
		cout << "\nUser Login:\n" << endl;
		cout << "Enter your first and last name: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, name);

		bool invalidType = true;
		while (invalidType) {
			cout << "\nEnter what type of user you are (Voter, Candidate, Administrator): ";
			cin >> userType;

			if (userType == "Administrator" || userType == "Voter" || userType == "Candidate") {
				invalidType = false;
			}
			else {
				cout << "Invalid User Type! Please enter a valid user type" << endl;
			}
		}

		cout << "\nEnter your User ID #: ";
		cin >> userID;
		
		//check if user exists
		invalid = !CheckUserType(userType);
		
		//if user does not exist ask to try again
		if (invalid == true) {
			cout << "Incorrect Login sorry!" << endl;
			cout << "Press y to try again..." << endl;
			char again;
			cin >> again;
			if (again != 'y' && again != 'Y') {
				invalid = false;
			}
		}
		//user does exist, continue to corresponding type
		else if (invalid == false) {
			cout << "Login Successful! Welcome " << name << "!" << endl;
			system("pause");
			CurrentUser();
		}
	}

}
//method to call a specific reading method depending on user type
bool ValidLogin::CheckUserType(string type) {
	bool UserInFile = false;
	if (type == "Administrator") {
		UserInFile = ReadAdminLoginFile();
	}
	else if (type == "Voter") {
		UserInFile = ReadVoterLoginFile();
	}
	else if (type == "Candidate") {
		UserInFile = ReadCandidateLoginFile();
	}
	else {
		cout << "Invalid type detected! Try again..." << endl;
		UserInFile = false;
	}

	return UserInFile;
}

//Check if the user is in the selected file
bool ValidLogin::ReadAdminLoginFile() {
	bool valid = false;
	ifstream LoginFile;

	LoginFile.open("AdminLogin.txt", ios::in);
	
	string currentLine;
	while (getline(LoginFile, currentLine)) {
		GetLoginInfo(currentLine);
		
		if (name == LoginInfo.at(0) && userID == stoi(LoginInfo.at(1)) && userType == LoginInfo.at(2)) {
			valid = true;
		}
		LoginInfo.clear();
	}

	LoginFile.close();
	return valid;
}
bool ValidLogin::ReadVoterLoginFile() {
	bool valid = false;
	fstream LoginFile;

	LoginFile.open("VoterLogin.txt", ios::in);

	string currentLine;
	while (getline(LoginFile, currentLine)) {
		GetLoginInfo(currentLine);
		
		if (name == LoginInfo.at(0) && userID == stoi(LoginInfo.at(1)) && userType == LoginInfo.at(2)) {
			valid = true;
		}
		LoginInfo.clear();
	}

	LoginFile.close();
	return valid;
}
bool ValidLogin::ReadCandidateLoginFile() {
	bool valid = false;
	ifstream LoginFile;

	LoginFile.open("CandidateLogin.txt", ios::in);

	string currentLine;
	while (getline(LoginFile, currentLine)) {
		GetLoginInfo(currentLine);
		
		if (name == LoginInfo.at(0) && userID == stoi(LoginInfo.at(1)) && userType == LoginInfo.at(2)) {
			valid = true;
		}
		LoginInfo.clear();
	}

	LoginFile.close();
	return valid;
}

//Get line from file, store temp information in vector to check if user info matches
void ValidLogin::GetLoginInfo(string n) {
	string currLine = n;
	string nameLine = currLine.substr(0, currLine.find("\t"));
	LoginInfo.push_back(nameLine);

	currLine = currLine.substr(currLine.find("\t") + 1);
	string id = currLine.substr(0, currLine.find("\t"));
	LoginInfo.push_back(id);

	currLine = currLine.substr(currLine.find("\t") + 1);
	string type = currLine.substr(0);
	LoginInfo.push_back(type);
}

//send control message to a user class upon successful login
void ValidLogin::CurrentUser() {
	if (userType == "Administrator") {
		//send control message to admin class
		Admin admin = Admin(name, userID);
		admin.menu();
	}
	else if (userType == "Voter") {
		//send control to voter class
		Voter voter = Voter(name, userID);
		voter.menu();
	}
	else if (userType == "Candidate") {
		//send control message to candidate class
		Candidate candidate = Candidate(name, userID);
		candidate.menu();
	}
}
