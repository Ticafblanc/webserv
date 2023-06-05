//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#include "Config/Includes/Config.class.hpp"

Config::Config() : _pegParser(), _mapTokenListAction(), _workerProcess(),
                   _blocEvents(*this), _blocHttp(*this) {
    setMapToken();
    setDefaultValue();
}

Config::Config(std::string &pathConfigFile) : _pegParser(pathConfigFile.c_str(), "#"),
                                              _mapTokenListAction(), _workerProcess(), _blocEvents(*this), _blocHttp(*this) {
    setMapToken();
    while (!_pegParser.checkIsEmpty()) {
        _pegParser.findToken(*this, _mapTokenListAction, 0);
    }
    setDefaultValue();
}

Config::~Config() {}

Config::Config(Config & other)
        : _pegParser(other._pegParser),_mapTokenListAction(other._mapTokenListAction),
          _workerProcess(other._workerProcess), _blocEvents(other._blocEvents), _blocHttp(other._blocHttp){

}

Config &Config::operator=(const Config &rhs) {
    this->_pegParser = rhs._pegParser;
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_workerProcess = rhs._workerProcess;
    this->_blocEvents = rhs._blocEvents;
    this->_blocHttp = rhs._blocHttp;
    return *this;
}


std::string Config::parseBlocEvent() {
    _mapTokenListAction.erase("events");
    std::string value = _pegParser.extractData('{');
    if (value.empty())
        value = _blocEvents.parseBlocEvents();
    return value;
}

std::string Config::parseBlocHttp() {
    _mapTokenListAction.erase("http");
    std::string value = _pegParser.extractData('{');
    if (value.empty())
        value = _blocHttp.parseBlocHttp();
//    std::cout << "_vectorBlocServer size:" << " " << _blocHttp._vectorBlocServer.size() << std::endl;
//    std::cout << "_vectorBlocServer 0:" << " " <<_ << std::endl;
    return value;
}

std::string Config::setWorkerProcesses() {
    _mapTokenListAction.erase("worker_processes");
    std::string value = _pegParser.extractData(';');
    char * end;//@todo to manage error
    const long val = std::strtol(value.c_str(), &end, 10);
    if (val < 1 || val > 4)
        return value;
    _workerProcess = static_cast<int>(val);
    value.clear();
    return value;
}

void Config::setDefaultValue() {
//    std::map<std::string, std::string (3-Config.class::*)()>::iterator it = _mapTokenListAction.begin();
    _workerProcess = 1;
    _blocEvents.setDefaultValue();
    _blocHttp.setDefaultValue();
}

void Config::setMapToken() {
    _mapTokenListAction["worker_processes"] = &Config::setWorkerProcesses;
    _mapTokenListAction["events"] = &Config::parseBlocEvent;
    _mapTokenListAction["http"] = &Config::parseBlocHttp;
}