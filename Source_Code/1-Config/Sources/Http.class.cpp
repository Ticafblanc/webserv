//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Http.class.hpp>

Http::Http(ConfigBase & config)
: _config(config), _configBase(config), _mapTokenListAction(), _haveChild(false) {
    setMapToken();
}

Http::~Http() {}

Http::Http(const Http &other)
: _config(other._config), _configBase(_config),
_mapTokenListAction(other._mapTokenListAction), _haveChild(other._haveChild){}

Http &Http::operator=(const Http &rhs) {
    if (this != &rhs) {
        this->_config = rhs._config;
        this->_configBase = rhs._configBase;
        this->_mapTokenListAction = rhs._mapTokenListAction;
        this->_haveChild = rhs._haveChild;
    }
    return *this;
}

std::string Http::parseBlocHttp(std::string &) {
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    if (!_haveChild)
        _configBase.addConfigBase(_config);
    return std::string("");
}
std::string Http::setclientBodyBufferSize(std::string & token) {
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

std::string Http::setclientHeaderBufferSize(std::string & token) {
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

std::string Http::setclientMaxBodySize(std::string & token) {
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
std::string Http::addVectorBlocServer(std::string &token) {
    clearToken();
    std::string value = _config.pegParser.extractData('{');
    if (value.empty()) {
        Server buildBlocServer(_config);
        value = buildBlocServer.parseBlocServer(token);
    }
    return value;
}

std::string Http::addVectorListen(std::string &token){
    (void)token;
    std::string value = _config.pegParser.extractData(';');
    Listen listen(_config);
    return listen.parseListenData(value);
}

void Http::setMapToken() {
    _mapTokenListAction["client_body_buffer_size"] = &Http::setclientBodyBufferSize;
    _mapTokenListAction["client_header_buffer_size"] = &Http::setclientHeaderBufferSize;
    _mapTokenListAction["client_max_body_size"] = &Http::setclientMaxBodySize;
    _mapTokenListAction["server"]= &Http::addVectorBlocServer;
    _mapTokenListAction["listen"]= &Http::addVectorListen;
}

void Http::clearToken() {
    if (_mapTokenListAction.find("listen") != _mapTokenListAction.end())
        _mapTokenListAction.erase("listen");
    if (_mapTokenListAction.find("client_body_buffer_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_body_buffer_size");
    if (_mapTokenListAction.find("client_header_buffer_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_header_buffer_size");
    if (_mapTokenListAction.find("client_max_body_size") != _mapTokenListAction.end())
        _mapTokenListAction.erase("client_max_body_size");
}

