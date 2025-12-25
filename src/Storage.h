#pragma once
#include <Auth.h>
#include <string>


bool loadUsers(UsersMap &users, const std::string &filename);
bool saveUsers(const UsersMap &users, const std::string &filename);

