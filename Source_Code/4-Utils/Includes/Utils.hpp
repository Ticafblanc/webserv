//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#ifndef WEBSERVER_UTILS_HPP
#define WEBSERVER_UTILS_HPP

#include <map>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <filesystem>


//std::string intToString(int number);
//std::string sizetToStringHex(std::size_t size);
//char** setEnvp(char **envp);
//bool isDirectory(const std::string & path);
bool isFile(const std::string & path);
//bool isExec(const std::string & path);
//bool autoIndexToHtml(std::string & path, std::string & url, std::ostringstream &oss);
//std::size_t stringToSizet(const std::string & str);
//std::string sizetToString(std::size_t size);
//bool removeDirectory(std::string &path);
//bool removeFile(std::string &path);
//bool extractFileToFd(const std::string & path, int fd, std::size_t & contentLength);
//void chunkData(std::vector<std::string> & vec, std::string data, std::size_t size);
//std::vector<char*> setArgv(const std::string& executablePath, const std::string& filePath);
//std::vector<char*> setPhpEnv(const std::string& method, const std::string& query, std::map<std::string, std::string>& headers);
//bool launchChild(int * pipefdIn,int * pipefdOut, pid_t &pid,
//                 std::vector<char*> argv, std::vector<char*> envp);
#endif //WEBSERVER_UTILS_HPP
