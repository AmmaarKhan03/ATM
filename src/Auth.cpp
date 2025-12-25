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


bool registerAccount(UsersMap& users,
					const std::string &username,
					const std::string &password) {

	if (users.find(username) != users.end()) {
		return false;
	}
		std::string salt = generateSalt(username);
		std::string hash = hashPassword(salt, password);

		User newUser;                 // create a struct called newUser
		newUser.username = username;
		newUser.salt = salt;
		newUser.passwordHash = hash;

		users[username] = newUser;  // adding our struct using our username to our unordered map
	return true;
}

bool loginAccount(const UsersMap& users, const std::string &username, const std::string &password) {

	if (users.find(username) == users.end()) {
		return false;
	}


	return true;
}
