//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Http.class.hpp>

Http::Http(ConfigBase & config)
: _configBase(config), _mapTokenListAction() {
    setMapToken();
}

Http::~Http() {}

Http::Http(Http &other)
: _configBase(other._configBase), _mapTokenListAction(other._mapTokenListAction){}

Http &Http::operator=(const Http &rhs) {
    if (this != &rhs) {
        this->_configBase = rhs._configBase;
        this->_mapTokenListAction = rhs._mapTokenListAction;
    }
    return *this;
}

std::string Http::parseBlocHttp(std::string &) {
    while (!_configBase.pegParser.checkIsEndOfBloc('}'))
        _configBase.configBase.pegParser.findToken(*this, _mapTokenListAction, 0);
    return std::string("");
}
std::string Http::setclientBodyBufferSize(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("client_body_buffer_size");
    std::string value = _configBase.configBase.pegParser.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 1024 || val > 8192){
        value = "value in valid for client_body_buffer_size => " + value;
        return value;
    }
    _configBase.clientBodyBufferSize = static_cast<int>(val);
    value.clear();
    return value;
}

std::string Http::setclientHeaderBufferSize(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("client_header_buffer_size");
    std::string value = _configBase.configBase.pegParser.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 512 || val > 1024) {
        value = "value in valid for client_header_buffer_size => " + value;
        return value;
    }
    _configBase.clientHeaderBufferSize = static_cast<int>(val);
    value.clear();
    return value;
}

std::string Http::setclientMaxBodySize(std::string & token) {
    (void)token;
    _mapTokenListAction.erase("client_max_body_size");
    std::string value = _configBase.configBase.pegParser.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 500000 || val > 1048576){
        value = "value in valid for client_max_body_size => " + value;
        return value;
    }
    _configBase.clientMaxBodySize = static_cast<int>(val);
    value.clear();
    return value;
}
std::string Http::parseBlocServer(std::string &token) {
    clearToken();
    std::string value = _configBase.configBase.pegParser.extractData('{');
    if (value.empty()) {
        Server buildBlocServer(_configBase);
        value = buildBlocServer.parseBlocServer(token);
    } else
        value = "find value before server bloc =>" + value;
    return value;
}

std::string Http::addVectorListen(std::string &token){
    (void)token;
    std::string value = _configBase.configBase.pegParser.extractData(';');
    Listen listen(_configBase);
    return listen.parseListenData(value);
}

std::string Http::addIndex(std::string &token){
    (void)token;
    std::stringstream value(_configBase.configBase.pegParser.extractData(';'));
    if (!value.str().empty()) {
        std::vector<std::string> val;
        while (!value.eof()) {
            std::string line;
            value >> line >> std::ws;
            val.push_back(line);
        }
        _configBase.addIndex(val);
        return std::string();
    }
    return std::string("no value at index");
}

void Http::setMapToken() {
    _mapTokenListAction["client_body_buffer_size"] = &Http::setclientBodyBufferSize;
    _mapTokenListAction["client_header_buffer_size"] = &Http::setclientHeaderBufferSize;
    _mapTokenListAction["client_max_body_size"] = &Http::setclientMaxBodySize;
    _mapTokenListAction["server"]= &Http::parseBlocServer;
    _mapTokenListAction["listen"]= &Http::addVectorListen;
    _mapTokenListAction["index"]= &Http::addIndex;
}

void Http::clearToken() {
    if (_mapTokenListAction.find("listen") != _mapTokenListAction.end())
        _mapTokenListAction.erase("listen");
    if (_mapTokenListAction.find("index") != _mapTokenListAction.end())
        _mapTokenListAction.erase("index");
    if (_mapTokenListAction.find("client_body_buffer_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_body_buffer_size");
    if (_mapTokenListAction.find("client_header_buffer_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_header_buffer_size");
    if (_mapTokenListAction.find("client_max_body_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_max_body_size");
}

