#include "Auth.h"
#include "Storage.h"
#include "Bank.h"
#include <iostream>
#include <limits>
#include <unordered_map>
using namespace std;





static void printBalance(const BalancesMap &balances, const std::string &user) {
	const long long cents = getBalanceCents(balances, user);
	const long long dollars = cents / 100;
	const long long rem = cents % 100;

	cout << "Balance: $" << dollars << "." << (rem < 10 ? "0" : "") << rem << endl;
}


int main() {

	int option;

	UsersMap users;
	BalancesMap balances;

	loadUsers(users, "data/users.db" );
	loadBalances(balances, "data/accounts.db");

	std::string username, password;
	bool loggedIn = false;
	std::string currentUser = "";

    do {
		cout << "1) Register\n" << "2) Login\n" << "3) Exit\n";
    	cin >> option; cout << endl;
    	// if cin fails, reset cin then discard the bad input and continue back to the top of the loop
    	if (cin.fail()) {
    		cin.clear();
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
    		cout << "invalid input. Please enter a number." << endl;
    		continue;
    	}
    	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    	switch (option) {
    		case 1:
    			cout << "Register selected\n" << "Create a Username: ";
    			cin >> username; cout << endl; cout << "Create a password: " ;
    			cin >> password; cout << endl;
    			if (registerAccount(users, username,password)) {
    				saveUsers(users, "data/users.db");
    				cout << "Account created" << endl;
    			} else {
    				cout << "Username already exists" << endl;
    			}
    			break;
    		case 2:
    			cout << "Login selected" << endl;
    			cout << "Enter your username: ";
    			cin >> username; cout << endl;
    			cout << "Enter your password: ";
    			cin >> password; cout << endl;
    			cin.ignore(numeric_limits<streamsize>::max(), '\n');

    			if (loginAccount(users, username, password)) {
    				cout << "Login Successfully" << endl;
    				currentUser = username;
    				loggedIn = true;

    				ensureAccount(balances, currentUser); //create balance entry if missing


					int option1;
    				do {
    					cout << "1) Balance\n" << "2) Deposit\n" << "3) Withdraw\n" << "4) Logout\n";
    					cin >> option1;
    					if (cin.fail()) {
    						cin.clear();
    						cin.ignore(numeric_limits<streamsize>::max(), '\n');
    						cout << "invalid input. Please enter a number." << endl;
    						continue;
    					}
    					cin.ignore(numeric_limits<streamsize>::max(), '\n');

    					switch (option1) {
    						case 1: {
    							printBalance(balances, currentUser);
    							break;
    						}
    						case 2: {
    							long long dollars;
    							cout << "how much would you like to deposit?" << endl;
    							cout << "Amount: ";
    							cin >> dollars;

    							if (cin.fail()) {
    								cin.clear();
    								cin.ignore(numeric_limits<streamsize>::max(), '\n');
    								cout << "invalid input. Please enter a number." << endl;
    								break;
    							}
    							cin.ignore(numeric_limits<streamsize>::max(), '\n');

    							if (!depositDollars(balances, currentUser, dollars)) {
    								cout << "Invalid deposit amount" << endl;
    								break;
    							}

    							saveBalances(balances, "data/accounts.db");
    							appendTransaction(
    										"data/transaction.db",
											currentUser,
											 "DEPOSIT",
											 dollars * 100,
											 balances[currentUser]
										);
    							cout << "Deposit successful" << endl;
    							break;
    						}
    						case 3: {
    							long long dollars;
    							cout << "how much would you like to withdraw?" << endl;
    							cout << "Withdraw: ";
    							cin >> dollars;

    							if (cin.fail()) {
    								cin.clear();
    								cin.ignore(numeric_limits<streamsize>::max(), '\n');
    								cout << "invalid input. Please enter a number." << endl;
    								break;
    							}
    							cin.ignore(numeric_limits<streamsize>::max(), '\n');


    							if (!withdrawDollars(balances, currentUser, dollars)) {
    								cout << "Insufficient funds or invalid amount" << endl;
    								break;
    							}

    							saveBalances(balances, "data/accounts.db");
    							appendTransaction(
											"data/transaction.db",
												currentUser,
													"WITHDRAW",
												dollars * 100,
											balances[currentUser]
												);
    							cout << "Withdraw successful" << endl;
    							break;
    						}
    						case 4:
    							cout << "Logging out" << endl;
    							break;
						    default:
    							cout << "Error" << endl;
					    }
    				} while (option1 != 4);
    				loggedIn = false;
    				currentUser = "";

    			} else {
    				cout << "Login Failed" << endl;
    			}

    			break;
    		case 3:
    			cout << "Exiting" << endl;
    			break;
    		default:
    			cout << "invalid choice";
    	}


    } while (option !=3);

	return 0;

}