#include "Auth.h"
#include "Storage.h"
#include <iostream>
#include <limits>
#include <unordered_map>
using namespace std;

int main() {
	int option;
	UsersMap users;
	std::unordered_map<std::string, long long> balances;
	loadUsers(users, "data/users.db" );
	loadBalances(balances, "data/accounts.db");
	cout << "Loaded users:" << users.size() << endl;
	std::string username, password;
	bool loggedIn = false;
	std::string currentUser = "";

    do {
		cout << "1) Register" << endl;
		cout << "2) Login" << endl;
    	cout << "3) Exit" << endl;
    	cin >> option;
    	cout << endl;

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
    			cout << "Register selected" << endl;
    			cout << "Create a Username: ";
    			cin >> username; cout << endl;
    			cout << "Create a password: " ;
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

    			if (loginAccount(users, username, password)) {
    				cout << "Login Successfully" << endl;
    				currentUser = username;
    				loggedIn = true;
    				if (balances.find(currentUser) == balances.end()) {
    					balances[currentUser] = 0;
    				}
					int option1;
    				do {
    					cout << "1) Balance " << endl;
    					cout << "2) Deposit " << endl;
    					cout << "3) Withdraw " << endl;
    					cout << "4) Logout " << endl;
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
    							cout << "Balance: $";
    							const long long cents = balances[currentUser];
    							const long long dollar = cents / 100;
    							const long long remainingCents = cents % 100;
    							cout << dollar << "." << (remainingCents < 10 ? "0" : "") << remainingCents << endl;
    							break;
    						}
    						case 2: {
    							int dollars;
    							cout << "how much would you like to deposit?" << endl;
    							cout << "Amount: ";
    							cin >> dollars;
    							if (cin.fail()) {
    								cin.clear();
    								cin.ignore(numeric_limits<streamsize>::max(), '\n');
    								cout << "invalid input. Please enter a number." << endl;
    								continue;
    							}
    							balances[currentUser] += (long long)dollars * 100;
    							saveBalances(balances, "data/accounts.db");

    							break;
    						}
    						case 3: {
    							int dollars;
    							cout << "how much would you like to withdraw?" << endl;
    							cout << "Withdraw: ";
    							cin >> dollars;
    							if (cin.fail()) {
    								cin.clear();
    								cin.ignore(numeric_limits<streamsize>::max(), '\n');
    								cout << "invalid input. Please enter a number." << endl;
    								continue;
    							}
    							long long withdrawCents = (long long)dollars * 100;
    							if (withdrawCents > balances[currentUser]) {
    								cout << "Insufficient funds" << endl;
    							} else {
    								balances[currentUser] -= withdrawCents;
    								saveBalances(balances, "data/accounts.db");

    							}
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

}