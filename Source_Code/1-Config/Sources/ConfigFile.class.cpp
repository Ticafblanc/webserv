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

#include <Source_Code/1-Config/Includes/ConfigFile.class.hpp>


ConfigFile::ConfigFile(ConfigBase & config)
: _config(config), _mapTokenListAction(), _Events(config), _Http(_config), _server(_config){
    parseConfigFile();
}

ConfigFile::~ConfigFile() {}

ConfigFile::ConfigFile(const ConfigFile & other)
: _config(other._config), _mapTokenListAction(other._mapTokenListAction),
_Events(other._Events), _Http(other._Http) , _server(_config) {}

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
    if (_config.mapTokenUriConfig.empty())
        throw Exception("No listen");
}

std::string ConfigFile::parseBlocEvent(std::string & token) {
    _mapTokenListAction.erase("events");
    std::string value = _config.pegParser.extractData('{');
    if (value.empty())
        value = _Events.parseBlocEvents(token);
    return value;
}

std::string ConfigFile::parseBlocHttp(std::string & token) {
    clearToken();
    std::string value = _config.pegParser.extractData('{');
    if (value.empty())
        value = _Http.parseBlocHttp(token);
    return value;
}

std::string ConfigFile::parseBlocServer(std::string & token) {
    clearToken();
    std::string value = _config.pegParser.extractData('{');
    if (value.empty())
        value = _Http.parseBlocHttp(token);
    return value;
}

std::string ConfigFile::setWorkerProcesses(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("worker_processes");
    std::string value = _config.pegParser.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 1 || val > 4)
        return value;
    _config.workerProcess = static_cast<int>(val);
    value.clear();
    return value;
}

std::string ConfigFile::setclientBodyBufferSize(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("client_body_buffer_size");
    std::string value = _config.pegParser.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 1024 || val > 8192)
        return value;
    _config.clientBodyBufferSize = static_cast<int>(val);
    value.clear();
    return value;
}

std::string ConfigFile::setclientHeaderBufferSize(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("client_header_buffer_size");
    std::string value = _config.pegParser.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 512 || val > 1024)
        return value;
    _config.clientHeaderBufferSize = static_cast<int>(val);
    value.clear();
    return value;
}

std::string ConfigFile::setclientMaxBodySize(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("client_header_buffer_size");
    std::string value = _config.pegParser.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 500000 || val > 1048576)
        return value;
    _config.clientMaxBodySize = static_cast<int>(val);
    value.clear();
    return value;
}

void ConfigFile::setMapToken() {
    _mapTokenListAction["worker_processes"] = &ConfigFile::setWorkerProcesses;
    _mapTokenListAction["client_body_buffer_size"] = &ConfigFile::setclientBodyBufferSize;
    _mapTokenListAction["client_header_buffer_size"] = &ConfigFile::setclientHeaderBufferSize;
    _mapTokenListAction["client_max_body_size"] = &ConfigFile::setclientMaxBodySize;
    _mapTokenListAction["events"] = &ConfigFile::parseBlocEvent;
    _mapTokenListAction["http"] = &ConfigFile::parseBlocHttp;
    _mapTokenListAction["server"] = &ConfigFile::parseBlocServer;
}

void ConfigFile::clearToken() {
    if (_mapTokenListAction.find("events") != _mapTokenListAction.end())
        _mapTokenListAction.erase("events");
    if (_mapTokenListAction.find("worker_processes") != _mapTokenListAction.end())
        _mapTokenListAction.erase("worker_processes");
    if (_mapTokenListAction.find("client_body_buffer_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_body_buffer_size");
    if (_mapTokenListAction.find("client_header_buffer_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_header_buffer_size");
    if (_mapTokenListAction.find("client_max_body_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_max_body_size");
}





