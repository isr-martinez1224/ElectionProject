//Written by: Israel Martinez
//Modify by: Emmanuel Portillo
/*This class allows a user to create a login as
a voter, candidate, or admin.
Depending what they chose, their info will be written to the corresponding file
*/

#pragma once

#include <string>
#include <fstream>
#include <limits>

using namespace std;

class CreateLogin 
{
public:
	CreateLogin();

	void CreateUserLogin();
	void WriteToLoginFile(string);


private:

	string name;
	string userType;
	int userID;

};


//Constructor
CreateLogin::CreateLogin() {
	name = "";
	userType = "";
	userID = 0;
}


//Methods
//ask the user for their information
void CreateLogin::CreateUserLogin() {
	system("cls");
	cout << "CREATE USER LOGIN" << endl;
	cout << "\nEnter your first and last name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name);

	bool invalidType = true;
	while (invalidType) {
		cout << "\nEnter what type of user you are registering as (Voter, Candidate, Administrator): ";
		cin >> userType;

		if (userType == "Administrator" || userType == "Voter" || userType == "Candidate") {
			invalidType = false;
		}
		else {
			cout << "Invalid User Type! Please enter a valid user type" << endl;
		}
	}

	//Generate random number id for user
	srand(time(0));
	string numString = "";
	for (int i = 0; i < 8; i++) {
		int num = rand() % 10;
		numString += to_string(num);
	}
	userID = stoi(numString);

	WriteToLoginFile(userType);
	
	cout << "\n--------------------------------" << endl;
	cout << "\nLogin successfully created!" << endl;
	cout << "User Details:" << endl;
	cout << "Name: " << name << endl;
	cout << "User Type: " << userType << endl;
	cout << "User ID #: " << userID << "\n" << endl;

	system("pause");
}

//write the user information to the corresponding type
void CreateLogin::WriteToLoginFile(string type) {
	ofstream LoginFile;

	if (type == "Administrator") {
		LoginFile.open("AdminLogin.txt", ios::app);
		LoginFile << name << "\t" << userID << "\t" << "Administrator" << "\n";
	}
	else if (type == "Voter") {
		LoginFile.open("VoterLogin.txt", ios::app);
		LoginFile << name << "\t" << userID << "\t" << "Voter" << "\n";
	}
	else if (type == "Candidate") {
		LoginFile.open("CandidateLogin.txt", ios::app);
		LoginFile << name << "\t" << userID << "\t" << "Candidate" << "\n";
	}
	LoginFile.close();
}

