cmake_minimum_required(VERSION 3.23.2)
project(websrever)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
include_directories(SYSTEM ./)

add_executable(webserver Sources/main.cpp Sources/init.cpp Sources/server.class.cpp Sources/data_server.class.cpp)