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
bool isExec(std::string & path);
bool autoIndexToHtml(std::string & path, std::string & url, std::ostringstream &oss);
std::size_t stringToSizet(const std::string & str);
bool removeDirectory(std::string &path);
bool removeFile(std::string &path);
bool setFile(const std::string & path, std::ostringstream &oss);
std::string addDate();
void chunkData(std::vector<std::string> & vec, std::string data, std::size_t size);
std::vector<char*> setArgv(const std::string& executablePath, const std::string& filePath);
std::vector<char*> setPhpEnv(const std::string& method, const std::string& query, std::map<std::string, std::string>& headers);
bool launchChild(int * pipefdIn,int * pipefdOut, pid_t &pid,
                 std::vector<char*> argv, std::vector<char*> envp);
#endif //WEBSERVER_UTILS_HPP
