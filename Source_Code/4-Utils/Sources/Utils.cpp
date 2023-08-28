//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#include <Source_Code/4-Utils/Includes/Utils.hpp>

//std::vector<char*>  setEnvp(std::vector<std::string> & envVec) {
//    std::vector<char*> env;
//    for (size_t i = 0; i < envVec.size(); ++i) {
//        env.push_back(const_cast<char*>(envVec[i].c_str()));
//    }
//    env.push_back(NULL);
//    return env;
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



