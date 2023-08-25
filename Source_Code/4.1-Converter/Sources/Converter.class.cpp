//
// Created by Ben on 2023-08-22.
//
#include <Source_Code/4.1-Converter/Includes/Converter.class.hpp>

Converter::Converter() {}
Converter::~Converter() {}

std::string Converter::intToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

std::size_t Converter::hexStringToSizet(const std::string & str) {
    ssize_t size;

    std::istringstream iss(str);
    iss >> std::hex >> size;
    return size;
}

std::string Converter::sizetToHexString(std::size_t size) {
    std::ostringstream oss;
    oss << std::hex << size;
    return oss.str();
}