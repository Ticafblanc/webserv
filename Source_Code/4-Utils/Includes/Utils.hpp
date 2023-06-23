//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#ifndef WEBSERVER_UTILS_HPP
#define WEBSERVER_UTILS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/4-Utils/Template/PegParser.class.tpp>
#include <dirent.h>
#include <filesystem>

std::string intToString(int number);
char** setEnvp(char **envp);
bool isDirectory(std::string & path);
bool isFile(std::string & path);
int autoIndexToHtml(std::string & path, std::string & url, std::ostringstream &oss);
std::size_t stringToSizet(const std::string & str);

#endif //WEBSERVER_UTILS_HPP
