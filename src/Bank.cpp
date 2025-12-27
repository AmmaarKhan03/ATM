#include "Bank.h"

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
	ensureAccount(balances, username);
	const long long withdrawCents = dollars * 100;
	if (withdrawCents > balances[username]) {
		return false;
	}
	balances[username] -= withdrawCents;
	return true;
}
