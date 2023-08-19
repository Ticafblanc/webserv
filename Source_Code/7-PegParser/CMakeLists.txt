cmake_minimum_required(VERSION 3.22.1)
project(peg_parser_lib)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

option(DOCKER "Build peg test programs" OFF)

option(BUILD_TESTS "Build peg test programs" OFF)

set(SOURCES_CODE Template/PegParser.class.tpp)

add_library(PEG_LIB STATIC ${SOURCES_CODE})

set_target_properties(PEG_LIB PROPERTIES LINKER_LANGUAGE CXX)

if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(PEG_TEST main.cpp)
    target_link_libraries(PEG_TEST PRIVATE PEG_LIB ${CMAKE_DL_LIBS})
endif()

