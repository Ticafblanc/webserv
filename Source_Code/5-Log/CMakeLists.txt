cmake_minimum_required(VERSION 3.22.1)
project(webserver)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(SYSTEM ./)

option(BUILD_TESTS "Build log test programs" OFF)

set(SOURCES_CODE Sources/Log.class.cpp)

add_library(LOG_LIB STATIC ${SOURCES_CODE})

if(BUILD_TESTS)
    add_executable(LOG_TEST main.cpp)
    target_link_libraries(LOG_TEST PRIVATE LOG_LIB ${CMAKE_DL_LIBS})
endif()

