//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#include <Source_Code/4-Utils/Includes/Utils.hpp>


std::string intToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

std::size_t stringToSizet(const std::string & str){
    ssize_t size;

    std::istringstream iss(str);
    iss >> std::hex >> size;
    return size;
}

std::vector<char*>  setEnvp(std::vector<std::string> & envVec) {
    std::vector<char*> env;
    for (size_t i = 0; i < envVec.size(); ++i) {
        env.push_back(const_cast<char*>(envVec[i].c_str()));
    }
    env.push_back(NULL);
    return env;
}


bool isDirectory(std::string & path) {
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISDIR(statbuf.st_mode);
}

bool isFile(std::string & path) {
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISREG(statbuf.st_mode);
}

bool isExec(std::string & path) {
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR ||
            statbuf.st_mode & S_IXGRP ||statbuf.st_mode & S_IXOTH);
}

bool autoIndexToHtml(std::string & path, std::string & url, std::ostringstream &oss){
    DIR* directory = opendir(path.c_str());
    if (!directory)
        return false;
    oss << "<!DOCTYPE html><html><head><title>Auto Index of " << url
         << "</title></head><body><h1>Auto Index of " << url << "</h1><ul>";
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name << "</a></li>";
    }
    oss << "</ul></body></html>";
    closedir(directory);
    return true;
}

bool removeDirectory(std::string &path){
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

bool removeFile(std::string &path){
    if (remove(path.c_str()) != 0)
        return false;
    return true;
}

bool setFile(const std::string & path, std::ostringstream &oss){
    std::ifstream htmlPage(path.c_str());
    if(!htmlPage.is_open())
        return false;
    std::copy(std::istreambuf_iterator<char>(htmlPage),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(oss));
    return true;
}

std::vector<char*>  setPhpEnv(const std::string& method, const std::string& query, std::map<std::string, std::string>& headers) {
    std::vector<std::string> envVec;

    envVec.push_back("REQUEST_METHOD=" + method);
    if (!query.empty()) {
        envVec.push_back("QUERY_STRING=" + query);
    }
    for (std::map<std::string, std::string>::iterator it = headers.begin();
    it != headers.end(); ++it) {
        std::string envVar = "HTTP_" + it->first;
        std::replace(envVar.begin(), envVar.end(), '-', '_');
        std::transform(envVar.begin(), envVar.end(), envVar.begin(), ::toupper);
        envVar += "=" + it->second;
        envVec.push_back(envVar);
    }
    return setEnvp(envVec);
}

std::vector<char*> setArgv(const std::string& executablePath, const std::string& filePath, ){
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(executablePath.c_str()));
    argv.push_back(const_cast<char*>(filePath.c_str()));
    argv.push_back(NULL);

    return argv;
}

bool launchChild(int * pipefdIn,int * pipefdOut, pid_t &pid,
                 std::vector<char*> argv, std::vector<char*> envp) {

    if (pipe(pipefdIn) == -1 || pipe(pipefdOut) == -1)
        return false;
    pid = fork();
    if (pid == -1)
        return false;
    if (pid == 0) {
        dup2(pipefdIn[STDIN_FILENO], STDIN_FILENO);
        close(pipefdOut[STDIN_FILENO]);
        dup2(pipefdOut[STDOUT_FILENO], STDOUT_FILENO);
        close(pipefdIn[STDOUT_FILENO]);
        execve(argv[0], argv.data(), envp.data());
        exit(EXIT_FAILURE);
    }
    return true;
}

std::string addDate() {
    std::time_t now = std::time(0);
    std::tm* timeInfo = std::gmtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
    return std::string(buffer);
}

void chunkData(std::vector<std::string> & vec, std::string data, std::size_t size) {
    for (std::size_t i = 0; i < data.size(); i += size + 1) {
        vec.push_back(data.substr(i, (data.size() > size) ? size : data.size()) + "\r\n");
        data = data.substr(size + 1);
    }
    vec.push_back("\0\r\n\r\n");
}
