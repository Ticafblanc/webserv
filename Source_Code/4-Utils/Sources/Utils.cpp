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

void executCgi() {
    _request.recvMessage();
    int status;
    int pipefd[2];
    if (pipe(pipefd) == -1)
        throw Exception("fail to to create pipe", 500);
    pid_t pid = fork();
    if (pid == -1)
        throw Exception("fail to fork", 500);
    if (pid == 0) {
        close(pipefd[STDOUT_FILENO]);
        dup2(pipefd[STDIN_FILENO], STDIN_FILENO);
        close(pipefd[STDIN_FILENO]);
        char* const argv[] = {"/path/to/cgi/script", NULL};
        execv(argv[0], argv);
        exit(EXIT_FAILURE);
    } else {
        // We're in the parent process
        close(pipefd[0]); // Close the read end of the pipe in the parent

        char buffer[4096];
        ssize_t read_size;
        while ((read_size = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            write(pipefd[1], buffer, read_size);
        }

        close(pipefd[1]); // This sends an EOF to the child


        waitpid(pid, &status, 0);
    }

    return 0;
}

std::string addDate() {
    std::time_t now = std::time(0);
    std::tm* timeInfo = std::gmtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
    return std::string(buffer);
}
