//
// Created by Ben on 2023-08-23.
//

#include <Source_Code/4.2-FileSystem/Includes/FileSystem.hpp>
#include <fstream>

int main() {
    std::ofstream testFile("testFile");
    bool isFileTest = isFile("testFile");
    std::cout << isFileTest << std::endl;
    remove("testFile");
    return(0);
}