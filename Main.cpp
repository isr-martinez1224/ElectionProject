//Emmanuel Portillo
#include<iostream>

using namespace std;

#include "ValidLogin.h"
#include "CreateLogin.h"

//Main Menu for the Election System with 3 options
int main() {

	int menuSelect;

	while (true) {
		system("cls");
		cout << "ONLINE ELECTION SYSTEM" << endl;

		cout << "\nPlease enter an option:" << endl;
		cout << "0 - Quit" << endl;
		cout << "1 - Login" << endl;
		cout << "2 - Create Login" << endl;

		cin >> menuSelect;

		//Create objects to allow functions
		ValidLogin userValid = ValidLogin();
		CreateLogin userCreate = CreateLogin();

		switch (menuSelect)
		{
		case 0:
			cout << "Goodbye!" << endl;
			exit(0);
		case 1:
			userValid.LoginInformation();
			break;
		case 2:
			userCreate.CreateUserLogin();
			break;
		default:
			cout << "Not a valid choice!" << endl;
			system("pause");
			break;
		}
	}


	return 0;
}
