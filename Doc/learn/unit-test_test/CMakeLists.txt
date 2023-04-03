cmake_minimum_required(VERSION 3.23.2)
set(CMake_CXX_STANDARD 98)
project(basic)
add_compile_options(-lgtest)
enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(basic basic.cpp)

target_link_libraries(
  basic
  GTest::gtest
)

add_test(NAME basic COMMAND basic)