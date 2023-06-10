//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include "Http.class.hpp"

Http::Http(Config& config)
: _config(config), _mapTokenListAction() {
    setMapToken();
}

Http::~Http() {}

Http::Http(const Http &other)
: _config(other._config), _mapTokenListAction(other._mapTokenListAction) {}

Http &Http::operator=(const Http &rhs) {
    if (this != &rhs) {
        this->_config = rhs._config;
        this->_mapTokenListAction = rhs._mapTokenListAction;
    }
    return *this;
}

std::string Http::parseBlocHttp(std::string &) {
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    return std::string("");
}

std::string Http::addVectorBlocServer(std::string &token) {
    std::string value = _config.pegParser.extractData('{');
    if (value.empty()) {
        Server buildBlocServer(_config);
        value = buildBlocServer.parseBlocServer(token);
        _config.vecEpoll.back().addServer(buildBlocServer);
//        _peg._vectorServer.push_back(buildBlocServer);
    }
    return value;
}

void Http::setMapToken() {
    _mapTokenListAction["serverSocket"]= &Http::addVectorBlocServer;
}

