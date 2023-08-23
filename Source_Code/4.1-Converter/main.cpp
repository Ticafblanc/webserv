//
// Created by Ben on 2023-08-21.
//
#include <iostream>
#include "Includes/Converter.class.hpp"

int main() {
    Converter Converter;
    //basic test for int to string, i need to add more later
    std::string string_test;
    string_test = Converter.intToString(42);
    std::cout << "intToString test" << std::endl;
    std::cout << string_test << '\n' << std::endl;

    //basic test for hex string to sizet, i need to add more later
    size_t size_t_test;
    size_t_test = Converter.hexStringToSizet("42");
    std::cout << "hexStringToSizeT test" << std::endl;
    std::cout << size_t_test << '\n' << std::endl;

    //basic test for size_t to hex string, i need to add more later
    std::string hex_string_test;
    hex_string_test = Converter.sizetToHexString(42);
    std::cout << "sizetToStringHex test" << std::endl;
    std::cout << hex_string_test << std::endl;

    return (0);
}