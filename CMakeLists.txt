cmake_minimum_required(VERSION 3.22.1)
project(webserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

set(WEBSERV Sources/main.cpp Sources/config_webserv.class.cpp Sources/peg_parser.class.cpp)
set(UNIT_TEST_PEG_PARSER libUnitTest/Sources/unitTestPegParser.cpp)

add_library(webservlib ${WEBSERV})
target_link_libraries(webservlib)

enable_testing()

add_executable(webserv ${WEBSERV})
add_executable(unitTestPegParser ${UNIT_TEST_PEG_PARSER})
target_link_libraries(unitTestPegParser webservlib)

add_test(NAME pegParserTest COMMAND unitTestPegParser)
