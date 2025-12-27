#include "Storage.h"
#include "Auth.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>




bool loadUsers(UsersMap &users, const std::string &filename) {

	// ifstream is reading from a file
	std::ifstream file(filename);  // tries to open file

	if (!file.is_open()) { // checks if its opened
		return true;
	}


	std::string line;
	while (std::getline(file,line)) {  // gets line then moves to the next
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string username, salt, hash;

		std::getline(ss, username, '|');
		std::getline(ss, salt, '|');
		std::getline(ss, hash, '|');

		// Strip Windows CR if present (CRLF files on /mnt/c)
		if (!hash.empty() && hash.back() == '\r') {
			hash.pop_back();
		}
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

bool loadBalances(std::unordered_map<std::string, long long> &balances, const std::string &filename) {

	std::ifstream file(filename);

	if (!file.is_open()) {
		return true;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string username, balanceStr;

		std::getline(ss, username, '|');
		std::getline(ss,balanceStr,'|');

		if (!balanceStr.empty() && balanceStr.back() == '\r') {
			balanceStr.pop_back();
		}

		if (username.empty() || balanceStr.empty()) continue;

		try {
			long long balance = std::stoll(balanceStr);
			balances[username] = balance;
		} catch (...) {
			// skip malformed line
			continue;
		}
	}

	return true;
}


bool saveBalances(const std::unordered_map<std::string, long long> &balances, const std::string &filename) {

	std::ofstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	for (const auto &bal : balances) {
		file << bal.first << '|' << bal.second << "\n";
	}

	return true;
}

static std::string currentTimestamp() {
	std::time_t now = std::time(nullptr);
	std::tm localTime{};
	localtime_s(&now, &localTime); //

	char buffer[20];
	std::strftime(buffer, sizeof(buffer),
				  "%Y-%m-%d %H:%M:%S",
				  &localTime);

	return std::string(buffer);
}
bool appendTransaction(const std::string &filename, const std::string &username,
						const std::string &type, long long amountCents, long long balanceAfterCents) {
	std::ofstream file(filename, std::ios::app); // std::ios::app, opens file in append mode
	if (!file.is_open()) {
		return false;
	}

	std::string ts = currentTimestamp();

	file << username << '|'
		 << ts << '|'
		 << type << '|'
		 << amountCents
		 << '|'
		 << balanceAfterCents << '\n';

	return true;
}
