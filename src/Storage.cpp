#include "Storage.h"
#include "Auth.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

bool loadUsers(UsersMap &users, const std::string &filename) {

	// ifstream is reading from a file
	std::ifstream file(filename);  // tries to open file

	if (!file.is_open()) { // checks if its opened
		return true;
	}


	std::string line;
	while (std::getline(file,line)) {  // gets line then moves to the next
		std::stringstream ss(line);
		std::string username, salt, hash;
		std::getline(ss, username, '|');
		std::getline(ss, salt, '|');
		std::getline(ss, hash, '|');
		User u;
		u.username = username;
		u.salt = salt;
		u.passwordHash = hash;
		users[username] = u;
	}


	return true;
}


bool saveUsers(const UsersMap &users, const std::string &filename) {

	// writes to a file
	std::ofstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	for (const auto &entry : users) {
		const User &user = entry.second;
		file << user.username << "|"
			 << user.salt << "|"
		     << user.passwordHash << "\n";
	}
	return true;
}