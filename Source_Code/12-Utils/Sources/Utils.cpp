//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#include "../Includes/Utils.hpp"


std::string intToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}
//
//std::size_t stringToSizet(const std::string & str){
//    ssize_t size;
//
//    std::istringstream iss(str);
//    iss >> std::hex >> size;
//    return size;
//}
//
//std::string sizetToString(std::size_t size){
//    std::ostringstream oss;
//    oss << std::hex << size;
//    return oss.str();
//}
//
//std::string sizetToStringHex(std::size_t size){
//    std::ostringstream oss;
//    oss << std::hex << size;
//    return oss.str();
//}

//std::vector<char*>  setEnvp(std::vector<std::string> & envVec) {
//    std::vector<char*> env;
//    for (size_t i = 0; i < envVec.size(); ++i) {
//        env.push_back(const_cast<char*>(envVec[i].c_str()));
//    }
//    env.push_back(NULL);
//    return env;
//}


//bool isDirectory(std::string & path) {
//    struct stat statbuf;
////    std::cout << "directory"<< std::endl;
//
//    if (stat(path.c_str(), &statbuf) != 0)
//        return false;
//    return S_ISDIR(statbuf.st_mode);
//}

bool isFile(const std::string & path) {
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) {
        return false;
    }
    return S_ISREG(statbuf.st_mode);
}

//bool isExec(std::string & path) {
//    struct stat statbuf;
////    std::cout << "exec"<< std::endl;
//    if (stat(path.c_str(), &statbuf) != 0)
//        return false;
//    return S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR ||
//            statbuf.st_mode & S_IXGRP ||statbuf.st_mode & S_IXOTH);
//}
//
//bool autoIndexToHtml(std::string & path, std::string & url, std::ostringstream &oss){
//    DIR* directory = opendir(path.c_str());
//    if (!directory)
//        return false;
//    oss << "<!DOCTYPE html><html><head><title>Auto Index of " << url
//         << "</title></head><body><h1>Auto Index of " << url << "</h1><ul>";
//    struct dirent* entry;
//    while ((entry = readdir(directory)) != NULL) {
//        oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name << "</a></li>";
//    }
//    oss << "</ul></body></html>";
//    closedir(directory);
//    return true;
//}

//bool removeDirectory(std::string &path){
//    DIR* directory = opendir(path.c_str());
//    if (!directory)
//        return removeFile(path);
//    struct dirent* entry;
//    while ((entry = readdir(directory)) != NULL) {
//        if (std::string(entry->d_name) != "." || std::string(entry->d_name) != "..") {
//            std::string entryPath = path + "/" + std::string(entry->d_name);
//            if (isFile(entryPath))
//                if (removeFile(entryPath))
//                    continue;
//        }
//    }
//    closedir(directory);
//    return removeFile(path);
//}

//bool removeFile(std::string &path){
//    if (remove(path.c_str()) != 0)
//        return false;
//    return true;
//}

//bool extractFileToFd(const std::string & path, int fd, std::size_t & contentLength) {
//    std::size_t min = 1024;

//    while (!buffer.empty()){
//        std::size_t size = std::min(buffer.size(), min);
//        std::cout << path << " " << contentLength << " " << buffer.size() <<" " << size << std::endl;
//        write(fd, buffer.data(), size);
//        buffer.erase(buffer.begin(), buffer.begin() + size);
//    }
//    std::cout <<"end" <<  path << " " << contentLength << " " << buffer.size()<< std::endl;
//    buffer.clear();
//    return true;
//}

//std::vector<char*>  setPhpEnv(const std::string& method, const std::string& query, std::map<std::string, std::string>& headers) {
//    std::vector<std::string> envVec;
//
//    envVec.push_back("REQUEST_METHOD=" + method);
//    if (!query.empty()) {
//        envVec.push_back("QUERY_STRING=" + query);
//    }
//    for (std::map<std::string, std::string>::iterator it = headers.begin();
//    it != headers.end(); ++it) {
//        std::string envVar = "HTTP_" + it->first;
//        std::replace(envVar.begin(), envVar.end(), '-', '_');
//        std::transform(envVar.begin(), envVar.end(), envVar.begin(), ::toupper);
//        envVar += "=" + it->second;
//        envVec.push_back(envVar);
//    }
//    return setEnvp(envVec);
//}
//
//std::vector<char*> setArgv(const std::string& executablePath, const std::string& filePath){
//    std::vector<char*> argv;
//    argv.push_back(const_cast<char*>(executablePath.c_str()));
//    argv.push_back(const_cast<char*>(filePath.c_str()));
//    argv.push_back(NULL);
//
//    return argv;
//}

//bool launchChild(int * pipefdIn,int * pipefdOut, pid_t &pid,
//                 std::vector<char*> argv, std::vector<char*> envp) {
//
//    if (pipe(pipefdIn) == -1 || pipe(pipefdOut) == -1)
//        return false;
//    pid = fork();
//    if (pid == -1)
//        return false;
//    if (pid == 0) {
//        dup2(pipefdIn[STDIN_FILENO], STDIN_FILENO);
//        close(pipefdOut[STDIN_FILENO]);
//        dup2(pipefdOut[STDOUT_FILENO], STDOUT_FILENO);
//        close(pipefdIn[STDOUT_FILENO]);
//        execve(argv[0], argv.data(), envp.data());
//        exit(EXIT_FAILURE);
//    }
//    return true;
//}
//



