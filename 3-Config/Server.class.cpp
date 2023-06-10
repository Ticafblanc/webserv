//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "Server.class.hpp"

Server::Server(Config &config)
: _config(config), _mapTokenListAction(), _vectorListen(), _vectorServerName(), _root(), _mapBlocLocation() {
    setMapToken();
}

Server::~Server() {}

Server::Server(const Server& other)
: _config(other._config), _mapTokenListAction(other._mapTokenListAction), _vectorListen(other._vectorListen),
_vectorServerName(other._vectorServerName), _root(other._root), _mapBlocLocation(other._mapBlocLocation){}

Server &Server::operator=(const Server & rhs) {
    if (this != &rhs) {
        this->_mapTokenListAction = rhs._mapTokenListAction;
        this->_vectorListen = rhs._vectorListen;
        this->_vectorServerName = rhs._vectorServerName;
        this->_root = rhs._root;
        this->_mapBlocLocation = rhs._mapBlocLocation;
    }
    return *this;
}

std::string Server::parseBlocServer(std::string &token) {
    (void)token;
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    return std::string("");
}

std::string Server::addVectorListen(std::string &token){
    (void)token;
    _mapTokenListAction.erase("listen");
    std::string value = _config.pegParser.extractData(';');
    if (value.empty())
        return std::string("empty");

    value.clear();
    return value;
}

std::string Server::addVectorServerName(std::string &token){
    (void)token;
    std::string server_name = _config.pegParser.extractData(';');
    _vectorServerName.push_back(server_name);
    return std::string("");
}

std::string Server::setRoot(std::string &token){
    (void)token;
    _mapTokenListAction.erase("root");
    _root = _config.pegParser.extractData(';');
    //@todo manage error
    return std::string("");
}

std::string Server::addMapBlocLocation(std::string &token) {
    (void)token;
    std::string path = _config.pegParser.extractData('{');
    //@todo check path ....
    Location Location(_config);
    Location.parseBlocLocation(token);
    _mapBlocLocation.insert(std::make_pair(path, Location));
    path.clear();
    return path;
}

void Server::setDefaultValue() {
    Listen lisdef(_config);
    lisdef.parseListenData("0.0.0.0:80");
    _vectorListen.push_back(lisdef);
    _vectorServerName.push_back("webserv.local") ;
    _root = "/usr/local/var/www";
    Location locdef(_config);
    _mapBlocLocation.insert(std::make_pair("/html", locdef));
}

void Server::setMapToken() {
    _mapTokenListAction["listen"] =  &Server::addVectorListen;
    _mapTokenListAction["server_name"] =  &Server::addVectorServerName;
    _mapTokenListAction["root"] =  &Server::setRoot;
    _mapTokenListAction["location"] =  &Server::addMapBlocLocation;
}



std::vector<Listen> &Server::getVectorListen() {
    return _vectorListen;
}

std::vector<std::string> & Server::getVectorServerName() {
    return _vectorServerName;
}
