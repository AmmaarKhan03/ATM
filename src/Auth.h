#include <string>


struct User {
	std::string username;
	std::string salt;
	std::string passwordHash;
};