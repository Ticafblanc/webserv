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

bool removeFile(std::string & path){
    if (remove(path.c_str()) != 0)
        return false;
    return true;
}

bool isDirectory(const std::string & path) {
    struct stat statbuf = {};
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISDIR(statbuf.st_mode);
}

bool isExec(std::string & path) {
    struct stat statbuf = {};
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR ||
            statbuf.st_mode & S_IXGRP ||statbuf.st_mode & S_IXOTH);
}