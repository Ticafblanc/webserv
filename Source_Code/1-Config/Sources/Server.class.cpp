//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Server.class.hpp>

Server::Server(ConfigBase &configBase)
: _config(configBase), _mapTokenListAction() {
    setMapToken();
}

Server::~Server() {}

Server::Server(const Server& other)
: _config(other._config), _mapTokenListAction(other._mapTokenListAction) {}

Server &Server::operator=(const Server & rhs) {
    if (this != &rhs) {
        this->_config = rhs._config;
        this->_mapTokenListAction = rhs._mapTokenListAction;
    }
    return *this;
}

std::string Server::parseBlocServer(std::string &token) {
    (void)token;
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.configBase.pegParser.findToken(*this, _mapTokenListAction, 0);
    if (!_config._uri.empty()) {
        if (_config._name.empty())
            _config._name.insert("default.com");
        _config.configBase.addConfigBase(_config);
    }
    return std::string("");
}

std::string Server::addVectorListen(std::string &token){
    (void)token;
    std::string value = _config.configBase.pegParser.extractData(';');
    Listen listen(_config);
    return listen.parseListenData(value);
}

std::string Server::addVectorServerName(std::string &token){
    (void)token;
    std::stringstream value(_config.configBase.pegParser.extractData(';'));
    if (!value.str().empty()) {
        std::vector<std::string> val;
        while (!value.eof()) {
            std::string line;
            value >> line >> std::ws;
            val.push_back(line);
        }
        _config.addName(val);
        return std::string();
    }
    return std::string("no value at server_name");
}

std::string Server::addIndex(std::string &token){
    (void)token;
    std::stringstream value(_config.configBase.pegParser.extractData(';'));
    if (!value.str().empty()) {
        std::vector<std::string> val;
        while (!value.eof()) {
            std::string line;
            value >> line >> std::ws;
            val.push_back(line);
        }
        _config.addIndex(val);
        return std::string();
    }
    return std::string("no value at index");
}

std::string Server::setRoot(std::string &token){
    (void)token;
    std::string root = _config.pegParser.extractData(';');
    if (root.empty())
        return std::string("no value at root");
    if (root[0] == '/')
        _config.root = root;
    else if(root[0] == '.'&& root[1] == '/')
        _config.root += root.substr(1, root.size() - 2);
    else
        return "error root must be start / or ./ => " + root;
    return std::string("");
}

std::string Server::parseBlocLocation(std::string &token) {
    (void)token;
    clearToken();
    std::string saveUri = _config._uri;
    std::string uri = _config.pegParser.extractData('{');
    if (uri.empty())
        return std::string("no value at location");
    else if (uri[0] == '/')
        _config.root += uri;

    else if(uri[0] == '.' && uri[1] == '/')
        _config._root += uri.substr(1, uri.size() - 2);

    else if(uri[0] == '*') {
        _config._uri += uri.substr(1, uri.size() - 2);
    }
    else
        return "error uri of location must be start / or ./ => " + uri;
    if (!_config._uri.empty()) {
        Location Location(_config);
        Location.parseBlocLocation(token);
    }else
        return std::string("Missing Uri in bloc location");
    _config._uri = saveUri;
    return std::string();
}

void Server::setMapToken() {
    _mapTokenListAction["listen"] =  &Server::addVectorListen;
    _mapTokenListAction["server_name"] =  &Server::addVectorServerName;
    _mapTokenListAction["index"] =  &Server::addIndex;
    _mapTokenListAction["root"] =  &Server::setRoot;
    _mapTokenListAction["location"] =  &Server::parseBlocLocation;
}

void Server::clearToken() {
    if (_mapTokenListAction.find("listen") != _mapTokenListAction.end())
        _mapTokenListAction.erase("listen");
    if (_mapTokenListAction.find("server_name") != _mapTokenListAction.end())
        _mapTokenListAction.erase("server_name");
    if (_mapTokenListAction.find("index") != _mapTokenListAction.end())
        _mapTokenListAction.erase("index");
    if (_mapTokenListAction.find("root") != _mapTokenListAction.end())
        _mapTokenListAction.erase("root");
}