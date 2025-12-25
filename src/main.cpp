#include <iostream>
#include <limits>
using namespace std;

int main() {
	int option;
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

    	if (option == 1) {
    		cout << "Register selected" << endl;
    	} else if (option == 2) {
    		cout << "Login selected" << endl;
    	} else if (option == 3){
    		cout << "Exiting" << endl;
    	} else {
    		cout << "invalid choice. Try Again" << endl;
    	}


    } while (option !=3);

}