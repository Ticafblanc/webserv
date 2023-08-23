cmake_minimum_required(VERSION 3.22.1)
project(fileSystem_lib)

set(CMAKE_CXX_STANDARD 98)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include_directories(SYSTEM ./)

option(DOCKER "Build conversion utils test programs" OFF)

option(BUILD_TESTS "Build conversion utils test programs" OFF)

set(SOURCES_CODE Sources/FileSystem.cpp)

add_library(FILE_SYSTEM_LIB STATIC ${SOURCES_CODE})

#a enlever si je vois que ce n'est pas necessaire
if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(FILE_SYSTEM_TEST main.cpp)
    target_link_libraries(FILE_SYSTEM_TEST PRIVATE FILE_SYSTEM_LIB ${CMAKE_DL_LIBS})
endif()