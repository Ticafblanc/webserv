//
// Created by Ben on 2023-08-23.
//

#include <Source_Code/4.2-FileSystem/Includes/FileSystem.hpp>

int main() {
    bool isFileTest = isFile("/Users/ben/CLionProject/webserv/Makefile");
    std::cout << isFileTest << std::endl;
    return(0);
}