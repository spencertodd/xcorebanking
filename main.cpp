#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <unordered_set>
#include "classes/transaction.h"


// Namespaces
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;
using std::getline;
using std::unordered_set;

int main()
{
	string select;
	unordered_set<string> allowedChoices = {"1", "2"};
	bool loginSuccess;

	cout << endl;
	cout << "Welcome to xCore Banking" << endl << endl;
	cout << "1. Login" << endl;
	cout << "2. Create account" << endl << endl;
	cout << "Select an action: ";
	cin >> select;
	cout << endl;

	while (allowedChoices.find(select) == allowedChoices.end()) {
		cout << "Please select a valid option (1 or 2): ";
		select.clear();
		cin >> select;
	}

	cout << endl;

	if (select == "1") {
		Account existing_account;
		loginSuccess = existing_account.login();

		char tryAgain;

		while (loginSuccess == false) {
			cout << "Would you like to try again? (y/n): " ;
			cin >> tryAgain;

			if (tryAgain == 'y') {
				loginSuccess = existing_account.login();
			}

			if (tryAgain == 'n') {
				cout << "Bye." << endl;
				return 0;
			}
		}

		char subaction;
		
		cout << endl;
		cout << "Welcome, " << existing_account.user_name << endl;
		cout << endl;
		cout << "1. View balance" << endl;
		cout << "2. Deposit" << endl;
		cout << "3. Withdrawal" << endl;
		cout << "4. Transfer" << endl;
		cout << "Select an action: " << endl;
		cin >> subaction;

		switch(subaction) {
			case '1' :
			cout << "Your balance is: " << existing_account.balance << endl;
			break;

			case '2' :
			Transaction transaction;
			transaction.deposit(existing_account);
			break;
			/*
			case '3' :
			Transaction transaction;
			case '4' :
			Transaction transaction;*/
		}

	}

	if (select == "2") {
		Account new_account;
		new_account.create();
	}
	
	return 0;
}