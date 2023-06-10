//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "Server.class.hpp"

Server::Server(Config &config)
: _config(config), _configServer(config.token.generateToken()), _mapTokenListAction() {
    setMapToken();
}

Server::~Server() {}

Server::Server(const Server& other)
: _config(other._config), _configServer(other._configServer), _mapTokenListAction(other._mapTokenListAction) {}

Server &Server::operator=(const Server & rhs) {
    if (this != &rhs) {
        this->_config = rhs._config;
        this->_configServer = rhs._configServer;
        this->_mapTokenListAction = rhs._mapTokenListAction;
    }
    return *this;
}

std::string Server::parseBlocServer(std::string &token) {
    (void)token;
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    _config.mapConfigServer.insert(std::make_pair(_configServer.token, _configServer));
    _config.vecEpoll.back().addConfigServer(_configServer);
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
    _configServer.name.push_back(server_name);
    return std::string("");
}

std::string Server::setRoot(std::string &token){
    (void)token;
    _mapTokenListAction.erase("root");
    _configServer.root = _config.pegParser.extractData(';');
    //@todo manage error
    return std::string("");
}

std::string Server::addMapBlocLocation(std::string &token) {
    (void)token;
    std::string uri = _config.pegParser.extractData('{');
    //@todo check path ....
    Location Location(_config, _configServer, uri);
    Location.parseBlocLocation(token);
    uri.clear();
    return uri;
}



void Server::setMapToken() {
    _mapTokenListAction["listen"] =  &Server::addVectorListen;
    _mapTokenListAction["server_name"] =  &Server::addVectorServerName;
    _mapTokenListAction["root"] =  &Server::setRoot;
    _mapTokenListAction["location"] =  &Server::addMapBlocLocation;
}

