cmake_minimum_required(VERSION 3.22.1)
project(network_lib)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

option(DOCKER "Build network test programs" OFF)

option(BUILD_TESTS "Build network test programs" OFF)

set(SOURCES_CODE Sources/Epoll.class.cpp)

add_library(NETWORK_LIB STATIC ${SOURCES_CODE})

if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(NETWORK_TEST main.cpp)
    target_link_libraries(NETWORK_TEST PRIVATE NETWORK_LIB ${CMAKE_DL_LIBS})
endif()

