//
// Created by Matthis DoQuocBao on 2023-05-31.
//

#include <Source_Code/4-Utils/Includes/Utils.hpp>



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


//


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



