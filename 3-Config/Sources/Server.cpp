//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#include "Config/Includes/Server.hpp"

Server::Server(Config&  config)
        : _config(config), _vectorListen(), _vectorServerName(),
          _root(), _mapBlocLocation(), _epollInstance() {
    setMapToken();
}

Server::~Server() {}

Server::Server(const Server& other)
        : _config(other._config), _vectorListen(other._vectorListen),
          _vectorServerName(), _root(), _mapBlocLocation(), _epollInstance() {}

Server &Server::operator=(const Server & rhs) {
    this->_config = rhs._config;
    this->_vectorListen = rhs._vectorListen;
    this->_vectorServerName = rhs._vectorServerName;
    this->_root = rhs._root;
    this->_mapBlocLocation = rhs._mapBlocLocation;
    return *this;
}

std::string Server::parseBlocServer() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string Server::addVectorListen(){
    _mapTokenListAction.erase("listen");
    std::string value = _config._pegParser.extractData(';');
    if (value.empty())
        return std::string("empty");

    value.clear();
    return value;
}

std::string Server::addVectorServerName(){
    std::string server_name = _config._pegParser.extractData(';');
    _vectorServerName.push_back(server_name);
    return std::string("");
}

std::string Server::setRoot(){
    _mapTokenListAction.erase("root");
    _root = _config._pegParser.extractData(';');
    //@todo manage error
    return std::string("");
}

std::string Server::addMapBlocLocation() {
    this->_numberTriggeredEvents = 0;
    std::string path = _config._pegParser.extractData('{');
    //@todo check path ....
    blocLocation blocLocation(_config);
    blocLocation.parseBlocLocation();
    _mapBlocLocation.insert(std::make_pair(path, blocLocation));
    path.clear();
    return path;
}

void Server::setDefaultValue() {
    if (_vectorListen.empty())
        _vectorListen.push_back(listenData(_config, "0.0.0.0:8081"));
    (void)_config;
//    if(_vectorServerName.empty() )
//        _vectorServerName.push_back("default_server.com");
//    if(_root.empty())
//        _root = "/usr/local/var/www";
}

void Server::setMapToken() {
    _mapTokenListAction["listen"] =  &Server::addVectorListen;
    _mapTokenListAction["server_name"] =  &Server::addVectorServerName;
    _mapTokenListAction["root"] =  &Server::setRoot;
    _mapTokenListAction["location"] =  &Server::addMapBlocLocation;
}

Server::Server() {

}

bool Server::EpollWait(int timeOut) {
    return Epoll::EpollWait(timeOut);
}
