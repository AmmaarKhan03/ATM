#pragma once
#include <string>
#include <unordered_map>


struct User {
	std::string username;
	std::string salt;
	std::string passwordHash;
};

using UsersMap = std::unordered_map<std::string, User>;

std::string generateSalt(const std::string &username);
std::string hashPassword(const std::string &salt, const std::string &password);

bool registerAccount(const UsersMap& users, const std::string &username, const std::string &password);
bool loginAccount(const UsersMap& users, const std::string &username, const std::string &password);

