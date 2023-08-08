cmake_minimum_required(VERSION 3.22.1)
project(config_lib)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

option(DOCKER "Build config test programs" OFF)

if(DOCKER)
    message(STATUS "Compiling in container Docker...")
    add_definitions(-DDOCKER)
endif()

option(BUILD_TESTS "Build config test programs" OFF)

set(SOURCES_CODE Sources/Config.cpp)

add_library(CONFIG_LIB STATIC ${SOURCES_CODE})

if(BUILD_TESTS)
    add_subdirectory(../5-Log)
    add_definitions(-DTESTMODE)
    add_executable(CONFIG_TEST main.cpp)
    target_link_libraries(CONFIG_TEST PRIVATE CONFIG_LIB LOG_LIB ${CMAKE_DL_LIBS})
endif()

