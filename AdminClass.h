//Created by: Israel Martinez
//Modify by: Emmanuel Portillo
/* This class provides main functionality to the
administrator user
Main Points: Create/close polls, print reports, view polls, view users, delete users
*/
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "ManageUsers.h"
#include "PollManagement.h"

//#include "CalculateResults.h"
#include "PollReport.h"

using namespace std;

class Admin
{
public: //Methods
	Admin(string, int);

	void setName(string);
	void setUserID(int);
	int getUserID();
	string getName();

	void menu();
	void PrintElectionReport();
	void CreateElectionPoll();
	void CloseElectionPoll();
	void ViewPolls();
	void viewUsers();
	void deleteUser();



private: //data
	string name;
	int userID;
	ManageUsers manage = ManageUsers();
	PollManagement maker = PollManagement();
	//Results results = Results();
	PollReport report = PollReport();
};


//Constructor
Admin::Admin(string n, int id) {
	name = n;
	userID = id;
}


//Getters + Setters
void Admin::setName(string n) {
	name = n;
}
void Admin::setUserID(int id) {
	userID = id;
}
string Admin::getName() {
	return name;
}
int Admin::getUserID() {
	return userID;
}


//Methods
void Admin::menu() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	bool menu = true;
	while(menu){
		int choice;

		system("cls");
		cout << "Welcome Administrator " << name << "!" << endl;
		cout << "----------------------" << endl;
		cout << "\nWhat would you like to do? Please enter a number" << endl;

        cout << "1. Print Election Report" << endl;
		cout << "2. Create Election Poll" << endl;
        cout << "3. Close Election Poll" << endl;
		cout << "4. View Open Polls" << endl;
        cout << "5. View Users" << endl;
        cout << "6. Delete User" << endl;
		cout << "7. Logout" << endl;

		cin >> choice;

		switch (choice) {
            case 1:
                PrintElectionReport();
                break;
            case 2:
                CreateElectionPoll();
                break;
            case 3:
                CloseElectionPoll();
                break;
			case 4:
				ViewPolls();
				break;
            case 5:
                viewUsers();
                break;
            case 6:
                deleteUser();
                break;
			case 7:
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

//print a election report
void Admin::PrintElectionReport() {

	//go to print report class
		//print report goes to results
	//results.CalculateResults();
	report.PrintReport();
}
//create a new poll file
void Admin::CreateElectionPoll() {

	maker.CreatePoll();

}
//close a poll file from being accessed to others
void Admin::CloseElectionPoll() {
	maker.ClosePoll();
}
//view which polls are open
void Admin::ViewPolls() {
	maker.ViewPolls();
}
//view voter or candidate users from the login files
void Admin::viewUsers() {
	manage.SearchUsers();
}
//remove a vote or candidate from the login files
void Admin::deleteUser() {
	manage.RemoveUser();
}
