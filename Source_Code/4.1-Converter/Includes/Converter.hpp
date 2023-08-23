//
// Created by Ben on 2023-08-22.
//

#ifndef WEBSERVER_CONVERTER_HPP
#define WEBSERVER_CONVERTER_HPP

#include <map>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <filesystem>

std::string intToString(int number);
std::size_t hexStringToSizet(const std::string & str);
std::string sizetToStringHex(std::size_t size);

#endif //WEBSERVER_CONVERTER_HPP
