cmake_minimum_required(VERSION 3.22.1)
project(log_lib)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

set(LOG_DIRECTORY "${CMAKE_SOURCE_DIR}/.webserv/log")

option(DOCKER "Build log test programs" OFF)

if(DOCKER)
    message(STATUS "Compiling in container Docker...")
    add_definitions(-DDOCKER)
elseif(NOT EXISTS ${LOG_DIRECTORY})
        file(MAKE_DIRECTORY ${LOG_DIRECTORY})
endif()

if (UNIX AND NOT APPLE)
    message(STATUS "Compiling on Linux...")
    add_definitions(-DLINUX)
elseif (APPLE)
    message(STATUS "Compiling on macOS...")
    add_definitions(-DMAC)
elseif (WIN32)
    message(FATAL_ERROR "Windows doesn't work")
endif()

option(BUILD_TESTS "Build log test programs" OFF)

set(SOURCES_CODE Sources/Log.class.cpp
        ../4-Utils/Sources/Utils.cpp)

add_library(LOG_LIB STATIC ${SOURCES_CODE})

if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(LOG_TEST main.cpp)
    target_link_libraries(LOG_TEST PRIVATE LOG_LIB ${CMAKE_DL_LIBS})
endif()

