#include "Bank.h"
#include <fstream>
#include <sstream>
#include <ctime>

static std::string currentDate() {
	std::time_t now = std::time(nullptr);
	std::tm localTime{};

#ifdef _WIN32
	localtime_s(&localTime, &now);
#else
	localtime_r(&now, &localTime);
#endif

	char buffer[11]; // YYYY-MM-DD
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
	return std::string(buffer);
}

static long long withdrawnTodayCents(const std::string &username) {
	std::ifstream file("data/transaction");
	if (!file.is_open()) {
		return 0;
	}

	const std::string today = currentDate();
	long long total = 0;


	std::string line;
	while (std::getline(file,line)) {

		std::stringstream ss(line);
		std::string user, timestamp, type, amountStr, balanceStr;
		std::getline(ss, user, '|');
		std::getline(ss, timestamp, '|');
		std::getline(ss, type, '|');
		std::getline(ss, amountStr, '|');
		std::getline(ss, balanceStr, '|');

		if (user != username) continue;
		if (type != "WITHDRAW") continue;
		if (timestamp.substr(0,10) !=today) continue;

		total += std::stoll(amountStr);
	}
	return total;
}


void ensureAccount(BalancesMap& balances, const std::string& username) {
	if (balances.find(username) == balances.end()) {
		balances[username] = 0;
	}
}

long long getBalanceCents(const BalancesMap& balances, const std::string& username) {
	const auto it = balances.find(username);
	if (it == balances.end()) {
		return 0;
	}
	return it->second;
}

bool depositDollars(BalancesMap& balances, const std::string& username, long long dollars) {
	if (dollars < 0) {
		return false;
	}
	ensureAccount(balances, username);
	balances[username] += dollars * 100;
	return true;
}



bool withdrawDollars(BalancesMap& balances, const std::string& username, long long dollars) {
	if (dollars < 0) {
		return false;
	}
	if (dollars < 20) return false;
	if (dollars % 20 != 0) return false;

	ensureAccount(balances, username);

	const long long withdrawCents = dollars * 100;

	const long long dailyLimitCents = 500 * 100;
	long long todayWithdrawn = withdrawnTodayCents(username);


	if (todayWithdrawn + withdrawCents > dailyLimitCents) {
		return false;
	}

	if (withdrawCents > balances[username]) {
		return false;
	}
	balances[username] -= withdrawCents;
	return true;
}
