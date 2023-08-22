//
// Created by Ben on 2023-08-22.
//

#ifndef WEBSERVER_CONVERSIONUTILS_HPP
#define WEBSERVER_CONVERSIONUTILS_HPP

#include <map>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <filesystem>

std::string intToString(int number);
std::size_t hexaStringToSizet(const std::string & str);

#endif //WEBSERVER_CONVERSIONUTILS_HPP
