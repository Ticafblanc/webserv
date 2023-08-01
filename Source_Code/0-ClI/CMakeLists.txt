cmake_minimum_required(VERSION 3.22.1)
project(webserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

option(BUILD_TESTS "Build Cli test programs" OFF)

set(SOURCES_CODE Sources/Cli.class.cpp)

add_library(CLI_LIB STATIC ${SOURCES_CODE})

if(BUILD_TESTS)
    add_executable(CLI_TEST main.cpp main.cpp ../4-Utils/Sources/Utils.cpp)
    target_link_libraries(CLI_TEST PRIVATE CLI_LIB ${CMAKE_DL_LIBS})
endif()

