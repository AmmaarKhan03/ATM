#include "Auth.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {
	int option;
	UsersMap users;
	std::string username, password;
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