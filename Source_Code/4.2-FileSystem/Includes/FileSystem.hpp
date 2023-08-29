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

    /**
     * Check if the path passed in parameter is a file or not
     *
     * @param path of the file to check
     * @return bool depending if the path is a file
     */
    static bool isFile(const std::string & path);

    /**
     * Check if the path passed in parameter is an executable file or not
     *
     * @param path of the file to check
     * @return bool depending if the path is an executable file
     */
    static bool isExec(std::string & path);

    /**
     * Remove a file
     *
     * @param path of the file to remove
     * @return bool if the file is removed correctly
     */
    static bool removeFile(std::string & path);

    /**
     * Check if the path passed in parameter is a directory
     *
     * @param path of the directory to check
     * @return bool is the path is a directory
     */
    static bool isDirectory(const std::string & path);

    /**
     * Remove a directory
     *
     * @param path of the directory to remove
     * @return bool is the directory is removed correctly
     */
    static bool removeDirectory(std::string & path);

    //will add comment later when i get to use it
    static bool extractFileToFd(const std::string & path, int fd, std::size_t & contentLength);
};

#endif //WEBSERVER_FILESYSTEM_HPP
