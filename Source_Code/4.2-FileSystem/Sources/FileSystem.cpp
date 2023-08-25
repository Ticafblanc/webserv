//
// Created by Ben on 2023-08-25.
//
#include <Source_Code/4.2-FileSystem/Includes/FileSystem.hpp>

bool isFile(const std::string & path) {
    struct stat statbuf = {};
    if (stat(path.c_str(), &statbuf) != 0) {
        return false;
    }
    return S_ISREG(statbuf.st_mode);
}