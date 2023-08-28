//
// Created by Ben on 2023-08-23.
//

#include <Source_Code/4.2-FileSystem/Includes/FileSystem.hpp>
#include <fstream>

int main() {
    std::string testFileName = "testFile";
    std::string testDirName = "testDir";
    std::string testExecFile = "FILE_SYSTEM_TEST";

    //function isFile
    std::cout << "\nTest of function isFile" << std::endl;
    std::ofstream testFile(testFileName);
    bool isFileTest = isFile(testFileName);
    if (isFileTest == 0)
        std::cout << "testFile is not a file." << std::endl;
    else
        std::cout << "testFile is a file." << std::endl;

    //function isExec
    std::cout << "\nTest of function isExec" << std::endl;
    if (isExec(testFileName))
        std::cout << "The file:" << " " << testFileName << " " << "can be executed." << std::endl;
    else
        std::cout << "The file:" << " " << testFileName << " " << "can not be executed." << std::endl;
    if (isExec(testExecFile))
        std::cout << "The file:" << " " << testExecFile << " " << "can be executed." << std::endl;
    else
        std::cout << "The file:" << " " << testExecFile << " " << "can not be executed." << std::endl;

    //function removeFile
    std::cout << "\nTest of function removeFile" << std::endl;
    if (removeFile(testFileName) && !isFile(testFileName))
        std::cout << "testFile has been removed." << std::endl;
    else
        std::cout << "Function removeFile has failed." << std::endl;

    //function isDirectory
    std::cout << "\nTest of function isDirectory" << std::endl;
    std::system("mkdir -p testDir");
    bool isDirTest = isDirectory(testDirName);
    if (isDirTest == 0)
        std::cout << "testDir is not a directory." << std::endl;
    else
        std::cout << "testDir is a directory." << std::endl;

    //function removeDirectory
    std::cout << "\nTest of function removeDirectory" << std::endl;
    if (removeDirectory(testDirName) && !isDirectory(testDirName))
        std::cout << "The directory has been removed.";
    else
        std::cout << "The function removeDirectory has failed." << std::endl;
    return(0);
}
//    char currentDir[FILENAME_MAX];
//
//    if (getcwd(currentDir, sizeof(currentDir)) != nullptr) {
//        std::cout << "Current working directory: " << currentDir << std::endl;
//    }
//    if (isDirectory("../../../Source_Code"))
//        std::cout << "is Dir" << std::endl;
//    if (isFile("../../../Source_Code/4.2-FileSystem/main.cpp"))
//        std::cout << "is File" << std::endl;
