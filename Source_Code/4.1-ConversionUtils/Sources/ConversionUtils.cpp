//
// Created by Ben on 2023-08-22.
//
#include <Source_Code/4.1-ConversionUtils/Includes/ConversionUtils.hpp>

std::string intToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}