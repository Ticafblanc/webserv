cmake_minimum_required(VERSION 3.22.1)
project(websrever)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g")
include_directories(SYSTEM ./)

set(WEBSERV Sources/main.cpp Sources/init.cpp Sources/server.class.cpp Sources/data_server.class.cpp Sources/Parser.class.cpp Sources/Route.class.cpp)
set(UNIT_TEST_INIT unitTestLib/Sources/unitTestInit.cpp)
set(UNIT_TEST_LAUNCHER unitTestLib/Sources/unitTestLauncher.cpp)

add_library(webservlib ${WEBSERV})
target_link_libraries(webservlib)

enable_testing()

add_executable(webserv ${WEBSERV})
add_executable(unitTestInit ${UNIT_TEST_INIT})
target_link_libraries(unitTestInit webservlib)
add_executable(unitTestLauncher ${UNIT_TEST_LAUNCHER})
target_link_libraries(unitTestLauncher webservlib)

add_test(NAME initTest COMMAND unitTestInit)
add_test(NAME launcherTest COMMAND unitTestLauncher)
