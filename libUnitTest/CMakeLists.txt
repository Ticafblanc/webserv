cmake_minimum_required(VERSION 3.23.2)
project(Unit_test)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
include_directories(SYSTEM ./)

add_executable(Unit_test    Sources/UTmain.cpp
                            Sources/0-constructor.cpp
        ../Sources/serverSocket.class.cpp
        ../Sources/config_webserv.class.cpp)
