//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Location.class.hpp>

Location::Location(Config& config, ConfigServer& configServer, std::string & uri)
        : _config(config), _configServer(configServer), _configLoaction(uri), _mapTokenListAction() {
    setMapToken();
}

Location::~Location() {}

Location::Location(const Location& other)
        : _config(other._config), _configServer(other._configServer), _configLoaction(other._configLoaction) {}

Location &Location::operator=(const Location & rhs) {
    if (this != &rhs) {
        this->_config = rhs._config;
        this->_configServer = rhs._configServer;
        this->_configLoaction = rhs._configLoaction;
    }
    return *this;
}


std::string Location::parseBlocLocation(std::string &token) {
    (void)token;
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    _configServer.location.insert(std::make_pair(_configLoaction.uri, _configLoaction));
    return std::string("");
}

std::string Location::setRoot(std::string &token){
    (void)token;
    _mapTokenListAction.erase("root");
    _configLoaction.root = _config.pegParser.extractData(';');
    //@todo manage error
    return std::string("");

}

std::string Location::addIndex(std::string &token) {
    (void)token;
    _mapTokenListAction.erase("index");
    std::string index = _config.pegParser.extractData(';');
    _configLoaction.index = index;
    return std::string("");

}

void Location::setMapToken() {
    _mapTokenListAction["root"] =  &Location::setRoot;
    _mapTokenListAction["index"] = &Location::addIndex;
}
