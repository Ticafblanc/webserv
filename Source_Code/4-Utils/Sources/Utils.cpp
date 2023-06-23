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

char** setEnvp(char **envp) {
    if (envp) {
        std::vector<char *> vecEnvp;
        for (int i = 0; envp[i] != NULL; ++i) {
            char *tmp = strdup(envp[i]);
            vecEnvp.push_back(tmp);
        }
        vecEnvp.push_back(NULL);
        char **newEnvp = new char *[vecEnvp.size()];
        std::copy(vecEnvp.begin(), vecEnvp.end(), newEnvp);
        return newEnvp;
    }
    return NULL;
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

int autoIndexToHtml(std::string & path, std::string & url, std::ostringstream &oss){
    DIR* directory = opendir(path.c_str());
    if (!directory)
        return -1;
    oss << "<!DOCTYPE html><html><head><title>Auto Index of " << url
         << "</title></head><body><h1>Auto Index of " << url << "</h1><ul>";
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name << "</a></li>";
    }
    oss << "</ul></body></html>";
    closedir(directory);
    return 0;
}



