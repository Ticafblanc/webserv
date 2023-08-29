cmake_minimum_required(VERSION 3.22.1)
project(setter_lib)

set(CMAKE_CXX_STANDARD 98)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include_directories(SYSTEM ./)

option(DOCKER "Build setter test programs" OFF)

option(BUILD_TESTS "Build setter test programs" OFF)

set(SOURCES_CODE Sources/Setter.cpp)

add_library(SETTER_LIB STATIC ${SOURCES_CODE})

#a enlever si je vois que ce n'est pas necessaire
if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(SETTER_TEST main.cpp)
    target_link_libraries(SETTER_TEST PRIVATE SETTER_LIB ${CMAKE_DL_LIBS})
endif()