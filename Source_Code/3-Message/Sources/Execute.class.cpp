//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/Execute.class.hpp>
#include <dirent.h>

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
    if (isFile())
        _isCgi  = checkIsCgi();
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

bool Execute::isFile() {
    struct stat statbuf;
    if (stat(_request.getUrl().c_str(), &statbuf) != 0)
        return false;
    return S_ISREG(statbuf.st_mode);
}

bool Execute::checkIsCgi() {
    std::size_t pos = _request.getUrl().find_last_of('.');
    if (pos != std::string::npos) {
        if (_mapMethode.find(_request.getUrl().substr(pos + 1)) != _mapMethode.end())
             return true;
    }
    return false;
}

void Execute::setIndex(){
    std::string saveUrl = _request.getUrl();
    for (std::set<std::string>::iterator  itSet = _location->_index.begin();
    itSet != _location->_index.end() ; ++itSet) {
        _request.getUrl() += "/" ;
        _request.getUrl() += *itSet;
        if (isFile())
            break;
        _request.getUrl() = saveUrl;
    }
}

void Execute::setAutoIndex(){
    DIR* directory = opendir(_request.getUrl().c_str());
    if (!directory)
       throw Exception("fail to create autoindex", 404);
    std::ostringstream oss;
    oss << "<!DOCTYPE html><html><head><title>Auto Index of " << _request.getUrl()
    << "</title></head><body><h1>Auto Index of " << _request.getUrl() << "</h1><ul>";
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name << "</a></li>";
    }
    oss << "</ul></body></html>";
    closedir(directory);
}

void Execute::setContent(const std::string & path){
    std::ifstream htmlPage(path.c_str());
    if(!htmlPage.is_open())
        throw Exception("impossible to open file", 403);
    _client.getclient()._content.assign(std::istreambuf_iterator<char>(htmlPage), std::istreambuf_iterator<char>());
    _client.getclient()._contentType = _config._mapMimeType.at(path.substr(path.find_last_of('.')));
}

void Execute::GETmethode() {
    if (!checkIsAllowedMethode(1, 3, 5))
        throw Exception("Method GET Not Allowed ", 405);
    if (_isCgi)
        setCgi();
    else
        setContent(_request.getUrl());



}

void Execute::POSTmethode() {
    if(checkIsAllowedMethode(2, 3, 6))
        throw Exception("Method POST Not Allowed ", 405);
    findRessource();
    std::string url = _request.getUrl();
    //todo find location
    //vald methode
    //execute request
    //build reponse
    std::ostringstream oss;

     = "<!DOCTYPE html>\n"
               "<html>\n"
               "<head>\n"
               "<title>Welcome to nginx!</title>\n"
               "<style>\n"
               "html { color-scheme: light dark; }\n"
               "body { width: 35em; margin: 0 auto;\n"
               "font-family: Tahoma, Verdana, Arial, sans-serif; }\n"
               "</style>\n"
               "</head>\n"
               "<body>\n"
               "<h1>Welcome to nginx!</h1>\n"
               "<p>If you see this page, the nginx web serverSocket is successfully installed and\n"
               "working. Further configuration is required.</p>\n"
               "\n"
               "<p>For online documentation and support please refer to\n"
               "<a href=\"http://nginx.org/\">nginx.org</a>.<br/>\n"
               "Commercial support is available at\n"
               "<a href=\"http://nginx.com/\">nginx.com</a>.</p>\n"
               "\n"
               "<p><em>Thank you for using nginx.</em></p>\n"
               "</body>\n"
               "</html>";

     _client.getclient()._contentType = "text/html";

}

void Execute::DELETEmethode() {
    if(checkIsAllowedMethode(4, 5, 6))
        throw Exception("Method DELETE Not Allowed ", 405);

    std::string url = _request.getUrl();


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
    std::ifstream htmlPage(_location->_code.getStatusPage(code).c_str());
    if(htmlPage.is_open())
        _client.getclient()._content.assign(std::istreambuf_iterator<char>(htmlPage), std::istreambuf_iterator<char>());
    if (_client.getclient()._content.empty()) {
        _client.getclient()._content = "<!DOCTYPE html><html><head><title>" +
        _config._code.getStatusCode(code) + "</title></head><body><h1>" +
        _config._code.getStatusCode(code) + "</h1><p>Sorry</p></body></html>";
    }
    _client.getclient()._contentType = "text/html";
}

void Execute::executeRequest(Config & location) {
    _location = &location;
    findRessource();
    selectMethode();
    if (location._return != 0)
        defaultPage(location._return);
}


/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/


