/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigFile.class.hpp"


ConfigFile::ConfigFile(Config & config)
: _config(config), _mapTokenListAction(), _Events(config), _Http(config){
    parseConfigFile();
}

ConfigFile::~ConfigFile() {}

ConfigFile::ConfigFile(const ConfigFile & other)
: _config(other._config), _mapTokenListAction(other._mapTokenListAction), _Events(other._Events), _Http(other._Http) {}

ConfigFile &ConfigFile::operator=(const ConfigFile &rhs) {
    if (this != &rhs) {
        this->_config = rhs._config;
        this->_mapTokenListAction = rhs._mapTokenListAction;
        this->_Events = rhs._Events;
        this->_Http = rhs._Http;
    }
    return *this;
}

void ConfigFile::parseConfigFile() {
    setMapToken();
    while (!_config.pegParser.checkIsEmpty()) {
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    }
}

std::string ConfigFile::parseBlocEvent(std::string & token) {
    _mapTokenListAction.erase("events");
    std::string value = _config.pegParser.extractData('{');
    if (value.empty())
        value = _Events.parseBlocEvents(token);
    return value;
}

std::string ConfigFile::parseBlocHttp(std::string & token) {
    _mapTokenListAction.erase("http");
    std::string value = _config.pegParser.extractData('{');
    if (value.empty())
        value = _Http.parseBlocHttp(token);
    return value;
}

std::string ConfigFile::setWorkerProcesses(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("worker_processes");
    std::string value = _config.pegParser.extractData(';');
    char * end;//@todo to manage error
    const long val = std::strtol(value.c_str(), &end, 10);
    if (val < 1 || val > 4)
        return value;
    _config.workerProcess = static_cast<int>(val);
    value.clear();
    return value;
}


void ConfigFile::setMapToken() {
    _mapTokenListAction["worker_processes"] = &ConfigFile::setWorkerProcesses;
    _mapTokenListAction["events"] = &ConfigFile::parseBlocEvent;
    _mapTokenListAction["http"] = &ConfigFile::parseBlocHttp;
}




