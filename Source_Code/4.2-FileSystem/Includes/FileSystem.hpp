//
// Created by Ben on 2023-08-25.
//

#ifndef WEBSERVER_FILESYSTEM_HPP
#define WEBSERVER_FILESYSTEM_HPP

#include <map>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <filesystem>

class FileSystem
{
public:

    FileSystem();
    ~FileSystem();

    static bool isFile(const std::string & path);
    static bool isExec(std::string & path);
    static bool removeFile(std::string & path);

    static bool isDirectory(const std::string & path);
    static bool removeDirectory(std::string & path);

    static bool extractFileToFd(const std::string & path, int fd, std::size_t & contentLength);
};

#endif //WEBSERVER_FILESYSTEM_HPP
