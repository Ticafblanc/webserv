cmake_minimum_required(VERSION 3.22.1)
project(utils_lib)

set(CMAKE_CXX_STANDARD 98)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include_directories(SYSTEM ./)

option(DOCKER "Build utils test programs" OFF)

option(BUILD_TESTS "Build utils test programs" OFF)

set(SOURCES_CODE Sources/Utils.cpp)

add_library(UTILS_LIB STATIC ${SOURCES_CODE})

#a enlever si je vois que ce n'est pas necessaire
if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(UTILS_TEST main.cpp)
    target_link_libraries(UTILS_TEST PRIVATE UTILS_LIB ${CMAKE_DL_LIBS})
endif()