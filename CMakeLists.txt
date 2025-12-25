cmake_minimum_required(VERSION 4.0)
project(ATM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data)
include_directories(src)

add_executable(ATM
        src/Auth.cpp
        src/Auth.h
        src/Bank.cpp
        src/Bank.h
        src/main.cpp
        src/Storage.cpp
        src/Storage.h)

add_custom_command(TARGET ATM POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:ATM>/data
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/data/users.db
        $<TARGET_FILE_DIR:ATM>/data/users.db
)

