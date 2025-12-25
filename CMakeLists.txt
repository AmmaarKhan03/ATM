cmake_minimum_required(VERSION 4.0)
project(ATM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data)
include_directories(src)

add_executable(ATM
        data/accounts.db
        data/users.db
        src/Auth.cpp
        src/Auth.h
        src/Bank.cpp
        src/Bank.h
        src/main.cpp
        src/Storage.cpp
        src/Storage.h)
