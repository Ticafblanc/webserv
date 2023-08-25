//
// Created by Ben on 2023-08-23.
//

#include <Source_Code/4.2-FileSystem/Includes/FileSystem.hpp>
#include <fstream>

int main() {
    std::string testFileName = "testFile";
    std::cout << "Test of function isFile" << std::endl;
    std::ofstream testFile(testFileName);
    bool isFileTest = isFile(testFileName);
    if (isFileTest == 0)
        std::cout << "testFile is not a file." << std::endl;
    else
        std::cout << "testFile is a file." << std::endl;
    if (removeFile(testFileName))
        std::cout << "testFile has been removed.\n" << std::endl;
    else
        std::cout << "Function removeFile has failed.\n" << std::endl;

    std::cout << "Test of function isDirectory" << std::endl;
    std::system("mkdir -p testDir");
    bool isDirTest = isDirectory("testDir");
    if (isDirTest == 0)
        std::cout << "testDir is not a directory.\n" << std::endl;
    else
        std::cout << "testDir is a directory.\n" << std::endl;
    std::system("rmdir testDir");
    return(0);
}