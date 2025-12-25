#include "Auth.h"
#include <functional>


// generating a salt
std::string generateSalt(const std::string &username) {

	const std::hash<std::string> hasher;  // creates a hash function object for string

	const std::string hashed = "SALT::" + username; // creates a string with SALT prefix
	const size_t result = hasher(hashed);   // convert the string to an int


	return std::to_string(result);
}


std::string hashPassword(const std::string &salt, const std::string &password) {

	const std::hash<std::string> hasher;
	const std::string hashed = salt + "::" + password;
	const size_t result = hasher(hashed);

	return std::to_string(result);
}


bool registerAccount(const UsersMap& users, const std::string &username, const std::string &password) {

	if () {

	}
	return true;
}
