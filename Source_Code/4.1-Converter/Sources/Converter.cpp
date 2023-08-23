//
// Created by Ben on 2023-08-22.
//
#include <Source_Code/4.1-Converter/Includes/Converter.hpp>

std::string intToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

std::size_t hexaStringToSizet(const std::string & str){
    ssize_t size;

    std::istringstream iss(str);
    iss >> std::hex >> size;
    return size;
}