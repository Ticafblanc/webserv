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

bool isFile(const std::string & path);
bool isExec(std::string & path);
bool removeFile(std::string & path);

bool isDirectory(const std::string & path);
bool removeDirectory(std::string & path);

bool extractFileToFd(const std::string & path, int fd, std::size_t & contentLength);

#endif //WEBSERVER_FILESYSTEM_HPP
