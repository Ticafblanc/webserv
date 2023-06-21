//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/Execute.class.hpp>
#include <dirent.h>
#include <filesystem>

Execute::Execute(HttpRequest& httpRequest, Config & config, Socket& client)
        : _request(httpRequest), _config(config), _mapMethode(), _client(client){
    buildMapMethode();
    buildMapCGI();
}

Execute::~Execute() {}

Execute::Execute(const Execute & other)
        : _request(other._request), _config(other._config), _client(other._client){}

Execute &Execute::operator=(const Execute &rhs) {
    this->_request = rhs._request;
    this->_config = rhs._config;
    this->_client = rhs._client;
    return *this;
}

void Execute::buildMapMethode(){
    _mapMethode["GET"] = &Execute::GETmethode;
    _mapMethode["POST"] = &Execute::POSTmethode;
    _mapMethode["DELETE"] = &Execute::DELETEmethode;
}

void Execute::buildMapCGI(){
    _mapCGI["cpp"] = "/usr/bin/php";
    _mapCGI["php"] = "/usr/bin/php";
    _mapCGI["py"] = "/usr/bin/python";
    _mapCGI["sh"] = "/usr/bin/bash";
}

void Execute::selectMethode() {
    (this->*_mapMethode[_request.getMethode()])();
}

bool Execute::checkIsAllowedMethode(int allow, int dual1, int dual2) const{
    return(_location->_allowMethods == 7 ||
    _location->_allowMethods == allow ||
    _location->_allowMethods == dual1 ||
    _location->_allowMethods == dual2);
};

void Execute::findRessource() {
    if (isDirectory())
        setIndex();
    if (isFile(_request.getUrl()))
        _cgi = checkIsCgi();
    else if (_location->_autoindex)
        setAutoIndex();
    else
        throw Exception("Uri not found", 404);
}

bool Execute::isDirectory() {
    struct stat statbuf;
    if (stat(_request.getUrl().c_str(), &statbuf) != 0)
        return false;
    return S_ISDIR(statbuf.st_mode);
}

bool Execute::isFile(std::string & path) {
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISREG(statbuf.st_mode);
}

std::string Execute::checkIsCgi() {
    std::string & url = _request.getUrl();
    std::size_t pos = url.find_last_of('.');
    if (pos != std::string::npos) {
        std::map<std::string, std::string>::iterator cgi = _mapCGI.find(url.substr(pos + 1));
        if (cgi != _config._mapMimeType.end()){
            return cgi->second;
        }
    }
    return "";
}

void Execute::setIndex(){
    std::string saveUrl = _request.getUrl();
    for (std::set<std::string>::iterator  itSet = _location->_index.begin();
    itSet != _location->_index.end() ; ++itSet) {
        _request.getUrl() += "/" ;
        _request.getUrl() += *itSet;
        if (isFile(_request.getUrl()))
            break;
        _request.getUrl() = saveUrl;
    }
}

void Execute::setAutoIndex(){
    DIR* directory = opendir(_location->_root.c_str());
    if (!directory)
       throw Exception("fail to create autoindex", 404);
    _oss << "<!DOCTYPE html><html><head><title>Auto Index of " << _request.getUrl()
    << "</title></head><body><h1>Auto Index of " << _request.getUrl() << "</h1><ul>";
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        _oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name << "</a></li>";
    }
    _oss << "</ul></body></html>";
    closedir(directory);
    _client.getclient()._contentType = "text/html";
}

void Execute::setFile(const std::string & path){
    std::ifstream htmlPage(path.c_str());
    if(!htmlPage.is_open())
        throw Exception("impossible to open file", 403);
    std::copy(std::istreambuf_iterator<char>(htmlPage),
              std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(_oss));
    _client.getclient()._contentType = _config._mapMimeType.at(path.substr(path.find_last_of('.')));
}

void Execute::setContent(){
    _client.getclient()._content = _oss.str();
}

void Execute::executCgi() {
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

void Execute::GETmethode() {
    findRessource();
    if (!checkIsAllowedMethode(1, 3, 5))
        throw Exception("Method GET Not Allowed ", 405);
    if (!_cgi.empty())
        executCgi();
    else
        setFile(_request.getUrl());
    setContent();
}

void Execute::POSTmethode() {
    findRessource();
    if(checkIsAllowedMethode(2, 3, 6))
        throw Exception("Method POST Not Allowed ", 405);
    else if (!_cgi.empty())
        executCgi();
    setContent();
}

void Execute::removeDirectory(std::string &path){
    DIR* directory = opendir(path.c_str());
    if (!directory)
        throw Exception("fail to remove directory", 500);
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        if (std::string(entry->d_name) != "." || std::string(entry->d_name) != "..") {
            std::string entryPath = path + "/" + std::string(entry->d_name);
            if (isFile(entryPath))
                removeFile(entryPath);
        }
    }
    closedir(directory);
    removeFile(path);
}

void Execute::removeFile(std::string &path){
    if (remove(path.c_str()) != 0) {
        throw Exception("fail to remove ressource", 500);
    }
}

void Execute::DELETEmethode() {
    if(checkIsAllowedMethode(4, 5, 6))
        throw Exception("Method DELETE Not Allowed ", 405);
    if (isDirectory())
        removeDirectory(_request.getUrl());
    else if (isFile(_request.getUrl()))
        removeFile(_request.getUrl());
    else if (_location->_autoindex)
        setAutoIndex();
    else
        throw Exception("Uri not found", 404);
}

std::string Execute::getReponse() {
    return _client.getclient()._content;
}

std::string Execute::getContentType() {
    return _client.getclient()._contentType;
}




/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/


void Execute::defaultPage(int code){
    setFile(_location->_code.getStatusPage(code));
    if (_client.getclient()._content.empty()) {
        _client.getclient()._content = "<!DOCTYPE html><html><head><title>" +
        _config._code.getStatusCode(code) + "</title></head><body><h1>" +
        _config._code.getStatusCode(code) + "</h1><p>Sorry</p></body></html>";
    }
    _client.getclient()._contentType = "text/html";
    _client.getclient()._statusCode = code;
}

void Execute::executeRequest(Config & location) {
    _location = &location;
    selectMethode();
    if (location._return != 0)
        return defaultPage(location._return);
    if (_client.getclient()._content.empty())
        _client.getclient()._statusCode = 204;
    else
        _client.getclient()._statusCode = 200;
}


/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/


