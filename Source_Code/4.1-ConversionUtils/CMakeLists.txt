cmake_minimum_required(VERSION 3.22.1)
project(conversionUtils_lib)

set(CMAKE_CXX_STANDARD 98)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include_directories(SYSTEM ./)

option(DOCKER "Build conversion utils test programs" OFF)

option(BUILD_TESTS "Build conversion utils test programs" OFF)

set(SOURCES_CODE Sources/ConversionUtils.cpp)

add_library(CONVERSION_UTILS_LIB STATIC ${SOURCES_CODE})

#a enlever si je vois que ce n'est pas necessaire
if(BUILD_TESTS)
    add_definitions(-DTESTMODE)
    add_executable(CONVERSION_UTILS_TEST main.cpp)
    target_link_libraries(CONVERSION_UTILS_TEST PRIVATE CONVERSION_UTILS_LIB ${CMAKE_DL_LIBS})
endif()