//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "Location.class.hpp"

Location::Location(Config& config)
        : _config(config), _mapTokenListAction(), _root(), _index() {
    setMapToken();
}

Location::~Location() {}

Location::Location(const Location& other)
        : _config(other._config), _root(other._root), _index(other._index) {}

Location &Location::operator=(const Location & rhs) {
    this->_config = rhs._config;
    this->_root = rhs._root;
    this->_index = rhs._index;
    return *this;
}


std::string Location::parseBlocLocation(std::string &token) {
    (void)token;
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    return std::string("");
}

std::string Location::setRoot(std::string &token){
    (void)token;
    _mapTokenListAction.erase("root");
    _root = _config.pegParser.extractData(';');
    //@todo manage error
    return std::string("");

}

std::string Location::addIndex(std::string &token) {
    (void)token;
    _mapTokenListAction.erase("index");
    std::string index = _config.pegParser.extractData(';');
    _index.push_back(index);
    return std::string("");

}

void Location::setMapToken() {
    _mapTokenListAction["root"] =  &Location::setRoot;
    _mapTokenListAction["index"] = &Location::addIndex;
}
