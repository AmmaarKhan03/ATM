#pragma once
#include <string>
#include <unordered_map>

using BalancesMap = std::unordered_map<std::string, long long>;
using WithDrawnToday = std::unordered_map<std::string, long long>;



void ensureAccount(BalancesMap &balances, const std::string &username);
long long getBalanceCents (const BalancesMap &balances, const std::string &username);
bool depositDollars(BalancesMap &balances, const std::string &username, long long dollars);
bool withdrawDollars(BalancesMap &balances, const std::string &username, long long dollars);