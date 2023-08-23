cmake_minimum_required(VERSION 3.22.1)
project(converter_lib)

set(CMAKE_CXX_STANDARD 98)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include_directories(SYSTEM ./)

option(DOCKER "Build converter test programs" OFF)

option(BUILD_TESTS "Build converter test programs" OFF)

set(SOURCES_CODE Sources/Converter.cpp)

add_library(CONVERTER_LIB STATIC ${SOURCES_CODE})

#a enlever si je vois que ce n'est pas necessaire
if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(CONVERTER_TEST main.cpp)
    target_link_libraries(CONVERTER_TEST PRIVATE CONVERTER_LIB ${CMAKE_DL_LIBS})
endif()