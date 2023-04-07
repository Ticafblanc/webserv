cmake_minimum_required(VERSION 3.23.2)
project(websrever)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g")
include_directories(SYSTEM ./)

set(WEBSERV Sources/main.cpp Sources/init.cpp Sources/server.class.cpp Sources/data_server.class.cpp)
set(UNIT_TEST_INIT Unit_test/Sources/unitTestInit.cpp)
set(UNIT_TEST_LAUNCHER Unit_test/Sources/unitTestLauncher.cpp)
set(UNIT_TEST_THROW Unit_test/Sources/unitTestThrow.cpp)

add_library(webservlib ${WEBSERV})
target_link_libraries(webservlib)

enable_testing()

add_executable(webserv ${WEBSERV})
add_executable(unitTestInit ${UNIT_TEST_INIT})
target_link_libraries(unitTestInit webservlib)
add_executable(unitTestLauncher ${UNIT_TEST_LAUNCHER})
target_link_libraries(unitTestLauncher webservlib)
add_executable(unitTestThrow ${UNIT_TEST_LAUNCHER})
target_link_libraries(unitTestThrow webservlib)

add_test(NAME initTest COMMAND unitTestInit)
add_test(NAME launcherTest COMMAND unitTestLauncher)
add_test(NAME throwTest COMMAND unitTestThrow)
