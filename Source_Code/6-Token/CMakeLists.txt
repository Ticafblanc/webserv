cmake_minimum_required(VERSION 3.22.1)
project(token_lib)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

option(DOCKER "Build token test programs" OFF)

option(BUILD_TESTS "Build token test programs" OFF)

set(SOURCES_CODE Sources/Token.class.cpp)

add_library(TOKEN_LIB STATIC ${SOURCES_CODE})

if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(TOKEN_TEST main.cpp)
    target_link_libraries(TOKEN_TEST PRIVATE TOKEN_LIB ${CMAKE_DL_LIBS})
endif()

