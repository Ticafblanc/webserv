cmake_minimum_required(VERSION 3.23.2)
project(websrev)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS #[["-Wall -Wextra -Werror"]])
include_directories(SYSTEM ./)

add_executable(webserv Sources/0-main.cpp Sources/1-init.cpp Sources/server.class.cpp)
