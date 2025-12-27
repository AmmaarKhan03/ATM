#pragma once
#include "Auth.h"
#include "Bank.h"
#include <string>
#include <unordered_map>


bool loadUsers(UsersMap &users, const std::string &filename);
bool saveUsers(const UsersMap &users, const std::string &filename);

bool loadBalances(std::unordered_map<std::string, long long> &balances, const std::string &filename);
bool saveBalances(const std::unordered_map<std::string, long long> &balances, const std::string &filename);

bool appendTransaction(const std::string &filename, const std::string &username,
						const std::string &type, long long amountCents, long long balanceAfterCents);


