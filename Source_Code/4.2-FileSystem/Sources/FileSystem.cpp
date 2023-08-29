//
// Created by Ben on 2023-08-25.
//
#include <Source_Code/4.2-FileSystem/Includes/FileSystem.hpp>

FileSystem::FileSystem() {}

FileSystem::~FileSystem() {}

bool FileSystem::isFile(const std::string & path) {
    struct stat statbuf = {};
    if (stat(path.c_str(), &statbuf) != 0) {
        return false;
    }
    return S_ISREG(statbuf.st_mode);
}

bool FileSystem::removeFile(std::string & path){
    if (remove(path.c_str()) != 0)
        return false;
    return true;
}

bool FileSystem::isDirectory(const std::string & path) {
    struct stat statbuf = {};
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISDIR(statbuf.st_mode);
}

bool FileSystem::isExec(std::string & path) {
    struct stat statbuf = {};
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR ||
            statbuf.st_mode & S_IXGRP ||statbuf.st_mode & S_IXOTH);
}

bool FileSystem::removeDirectory(std::string &path){
    DIR* directory = opendir(path.c_str());
    if (!directory)
        return removeFile(path);
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        if (std::string(entry->d_name) != "." || std::string(entry->d_name) != "..") {
            std::string entryPath = path + "/" + std::string(entry->d_name);
            if (isFile(entryPath))
                if (removeFile(entryPath))
                    continue;
        }
    }
    closedir(directory);
    return removeFile(path);
}

//will be use in the cgi
bool FileSystem::extractFileToFd(const std::string & path, int fd, std::size_t & contentLength) {
    std::string buffer;
    std::size_t min = 1024;

    while (!buffer.empty()){
        std::size_t size = std::min(buffer.size(), min);
        std::cout << path << " " << contentLength << " " << buffer.size() <<" " << size << std::endl;
        write(fd, buffer.data(), size);
        buffer.erase(buffer.begin(), buffer.begin() + size);
    }
    std::cout <<"end" <<  path << " " << contentLength << " " << buffer.size()<< std::endl;
    buffer.clear();
    return true;
}