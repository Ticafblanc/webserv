//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Events.class.hpp>

Events::Events(ConfigBase &config): _config(config), _mapTokenListAction() {
    setMapToken();
}

Events::~Events() {}

Events::Events(const Events &other)
        : _config(other._config), _mapTokenListAction(other._mapTokenListAction) {}


Events &Events::operator=(const Events &rhs) {
    this->_mapTokenListAction = rhs._mapTokenListAction;
    return *this;
}


std::string Events::parseBlocEvents(std::string &token) {
    (void)token;
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    return std::string("");
}

std::string Events::setWorkerConnections(std::string &token) {
    (void)token;
    _mapTokenListAction.erase("worker_connections");
    std::string value = _config.pegParser.extractData(';');
    char * end;//@todo to manage error
    const long val = std::strtol(value.c_str(), &end, 10);
    if (val < 10 || val > 20)
        return value;
    _config.workerConnections = static_cast<int>(val);
    value.clear();
    return value;
}

void Events::setMapToken() {
    _mapTokenListAction["worker_connections"] = &Events::setWorkerConnections;
}

