#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include "account.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;
using std::getline;
using std::unordered_set;
using std::unordered_map;

void Account::create(void)
{

	cout << "Enter your first name: ";
	cin >> Account::first_name;

	cout << "Enter your last name: ";
	cin >> Account::last_name;

	cout << "Enter your birthday (dd-mm-yyyy): ";
	cin >> Account::dob;

	Account::balance = 0.00;
	
	char correct;

	cout << endl;
	cout << "First Name: " << Account::first_name << endl;
	cout << "Last Name: " << Account::last_name << endl;
	cout << "Date of Birth: " << Account::dob << endl << endl;

	cout << "Create a username: ";
	Account::createUsername();

	cout << "Create a four digit PIN: ";
	Account::createPin();

	cout << "Is this information correct ? (y/n): ";
	cin >> correct;

	if (correct == 'n') {
		Account::create();
	}

	if (correct == 'y') {
		Account::saveAccount();
		cout << "Account successfully created for: " << Account::first_name << " " << Account::last_name << endl;
	}	
}

void Account::saveAccount(void)
{
	string line;
	int lines = 0;

	ifstream file("data/Account.dat");

	ofstream data_file;
	data_file.open("data/Account.dat", ofstream::out | ofstream::app);

	while (getline(file, line)) {
		lines++;
	}

	Account::id = lines + 1;

	data_file << Account::id << "," << Account::first_name <<  "," << Account::last_name << "," << Account::dob << "," << Account::balance << "," << Account::user_name << "," << Account::pin << endl;
	data_file.close();
}

bool Account::login(void)
{
	vector<vector<string>> account_list;
	string username;
	string pin;
	char cont;
	vector <string> account;

	int attempts = 1;
	int remaining = 3;

	cout << "Enter your username: ";
	cin >> username;

	cout << "Enter your PIN: ";
	cin >> pin;

	account_list = Account::getAccounts();

	if (account_list.size() > 0) {
		account = Account::getAccount(account_list, username, pin);

		if (account.size() == 0) {
			cout << "No matching account found.." << endl;
			return false;
		}

		Account::id = stoi(account[0]);
		Account::first_name = account[1];
		Account::last_name = account[2];
		Account::dob = account[3];
		Account::balance = stod(account[4]);
		Account::user_name = account[5];
		Account::pin = account[6];
	}

	return true;
}

vector <vector<string>> Account::getAccounts(void)
{
	string line;
	ifstream file("data/Account.dat");
	vector<vector<string>> accounts;
	vector<string> account_data;
	string account_str;

	int position = 0;
	cin.ignore();

	while (getline(file, line)) {
		for (char i : line) {
			if (i == ',') {
				account_data.push_back(account_str);
				account_str.clear();
			} else {
				account_str += i; 
			}

			if (position + 1 == line.size()) {
				account_data.push_back(account_str);
				account_str.clear();
			}

			position++;
		}

		accounts.push_back(account_data);
		account_data.clear();
		position = 0;
	}

	return accounts;
}

vector<string> Account::getAccount(vector <vector<string>> &accounts, string username, string pin)
{
	vector<string> account = {};
	bool username_matches = false;
	bool pin_matches = false;
	int iterator;
	
	
	for (int i = 0; i < accounts.size(); i++) {
		cout << "PIN: " << accounts[i][6] << endl;
		if (accounts[i][5] == username) {
			username_matches = true;
		}

		if (accounts[i][6] == pin) {
			pin_matches = true;
		}

		if (username_matches == true && pin_matches == true) {
			iterator = i;
			cout << "Matching account found!" << endl;
		}
	}

	if (username_matches == true && pin_matches == true) {
		for (int j = 0; j < accounts[iterator].size(); j++) {
			account.push_back(accounts[iterator][j]);
		}
	}
	
	return account;
}

bool Account::validatePin(void)
{
	if (Account::pin.length() != 4) {
		cout << "Yor PIN must be four digits: ";
		return false;
	}

	unordered_set<char> legalNums = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

	for (char i : pin) {
		if (legalNums.find(i) == legalNums.end()) {
			cout << "Yor PIN must be numeric: ";
			return false;
		}
	}

	return true;
}

void Account::createPin(void)
{
    cin >> Account::pin;

	bool is_valid;

	is_valid = Account::validatePin();

	while (is_valid == false) {
		Account::pin.clear();
		cin >> Account::pin;
		is_valid = Account::validatePin();
	}

	cout << "Successfully created PIN: " << Account::pin << endl << endl;
}

bool Account::validateUsername(void)
{
	unordered_set<char> allowedFirstChars = {
		'a', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
		'j', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	unordered_set<char> allowedChars = {
		'a', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
		'j', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'1', '2', '3', '4', '5', '6', '7', '8',
		'9' };

	if (Account::user_name.length() < 8 || Account::user_name.length() > 16) {
		cout << "Your username must be between 8 and 16 characters: ";
		return false;
	}

	if (allowedFirstChars.find(tolower(Account::user_name[0])) == allowedFirstChars.end()) {
		cout << "Usernames must begin with a letter: ";
		return false;
	}

	if (allowedChars.find(tolower(Account::user_name[0])) == allowedChars.end()) {
		cout << "Usernames can only contain letters and numbers: ";
		return false;
	}

	return true;
}

void Account::createUsername(void)
{
	cin >> Account::user_name;

	bool is_valid;

	is_valid = Account::validateUsername();

	while (is_valid == false) {
		Account::user_name.clear();
		cin >> Account::user_name;
		is_valid = Account::validateUsername();
	}
	
	cout << "Successfully created username: " << Account::user_name << endl << endl;
}

vector <vector<string>> Account::getAccount(Account &account)
{
	string line;
	ifstream file("data/Account.dat");
	vector<string> account_data;
	string account_str;
	vector <vector<string>> account_in_database;
	int position = 0;
	cin.ignore();

	while (getline(file, line)) {
		for (char i : line) {
			if (i == ',') {
				account_data.push_back(account_str);
				account_str.clear();
			} else {
				account_str += i; 
			}

			if (position + 1 == line.size()) {
				account_data.push_back(account_str);
				account_str.clear();
			}

			position++;
		}

		account_in_database.push_back(account_data);
		account_data.clear();
		position = 0;
	}

	return account_in_database;
}

/**
 * @TODO: Update balance in the file
 * the value currently gets lost when
 * the program finishes running
 */
void Account::updateBalance(Account &account)
{
	vector <vector<string>> account_data_old;
	account_data_old = Account::getAccount(account);
	cout << "This didn't break" << endl;
}