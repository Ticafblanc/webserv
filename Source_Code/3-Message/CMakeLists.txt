cmake_minimum_required(VERSION 3.22.1)
project(message_lib)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

option(DOCKER "Build message test programs" OFF)

option(BUILD_TESTS "Build message test programs" OFF)

set(SOURCES_CODE Sources/HttpHeadersRequest.class.cpp)

add_library(MESSAGE_LIB STATIC ${SOURCES_CODE})

if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(MESSAGE_TEST main.cpp)
    target_link_libraries(MESSAGE_TEST PRIVATE MESSAGE_LIB ${CMAKE_DL_LIBS})
endif()

