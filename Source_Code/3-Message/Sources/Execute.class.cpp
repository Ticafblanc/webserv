//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/Execute.class.hpp>


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













/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/







/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/


