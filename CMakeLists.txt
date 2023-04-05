cmake_minimum_required(VERSION 3.23.2)
project(websrever)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
include_directories(SYSTEM ./)

set(WEBSERV Sources/main.cpp Sources/init.cpp Sources/server.class.cpp Sources/data_server.class.cpp)
set(UNIT_TEST_CONSTRUCTOR Unit_test/Sources/UTmain.cpp Unit_test/Sources/0-constructor.cpp)

add_library(webserv ${WEBSERV})
target_link_libraries(webserv)

enable_testing()

# add_executable(webserv ${WEBSERV})
add_executable(unitTestConstructor ${UNIT_TEST_CONSTRUCTOR})
target_link_libraries(unitTestConstructor webserv)

add_test(NAME constructorTest COMMAND unitTestConstructor)
