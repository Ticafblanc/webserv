//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Location.class.hpp>

Location::Location(Config& config)
: _config(config), _mapTokenListAction() {
    setMapToken();
}

Location::~Location() {}

Location::Location(const Location& other)
        : _config(other._config), _mapTokenListAction(other._mapTokenListAction){}

Location &Location::operator=(const Location & rhs) {
    if (this != &rhs) {
        this->_config = rhs._config;
        this->_mapTokenListAction = rhs._mapTokenListAction;
    }
    return *this;
}


std::string Location::parseBlocLocation(std::string &token) {
    (void)token;
    while (!_config.pegParser.checkIsEndOfBloc('}'))
        _config.pegParser.findToken(*this, _mapTokenListAction, 0);
    if (_config._name.empty())
        _config._name.insert("default.com");
    _config.configBase.addConfigBase(_config);
    return std::string("");
}

std::string Location::addIndex(std::string &token) {
    (void)token;
    std::stringstream value(_config.configBase.pegParser.extractData(';'));
    if (!value.str().empty()) {
        std::vector<std::string> val;
        while (!value.eof()) {
            std::string line;
            value >> line >> std::ws;
            val.push_back(line);
        }
        if (!_config._return)
            _config.addIndex(val);
        return std::string();
    }
    return std::string("no value at index");

}

std::string Location::setRoot(std::string &token){
    (void)token;
    std::string root = _config.pegParser.extractData(';');
    if (root.empty())
        return std::string("no value at root");
    if (!_config._return)
        _config._root
    return std::string("");
}

std::string Location::setAllowMethods(std::string &token){
    (void)token;
    int _get = 0;
    int _post = 0;
    int _delete = 0;

    std::stringstream value(_config.configBase.pegParser.extractData(';'));
    if (!value.str().empty()) {
        while (!value.eof()) {
            std::string line;
            value >> line >> std::ws;
            if (line == "GET")
                _get = 1;
            else if (line == "POST")
                _post = 2;
            else if (line == "DELETE")
                _delete = 4;
            else
                return line += " not allowed methods";
        }
        _config._allowMethods = _get + _post + _delete;
        addVecInfo("allow_method", &_config._allowMethods);
    }
    return std::string("no value at allow_methods");
}

std::string Location::setReturn(std::string & token) {
    (void)token;
    std::stringstream value(_config.configBase.pegParser.extractData(';'));
    if (!value.str().empty()){
        std::string line;
        value >> line >> std::ws;
        char * end;
        const long code = std::strtol(line.c_str(), &end, 10);
        if (end == line.c_str() || code < 100 || code > 599 || !_config.code.FindCode((int)code)) {
            line = "value in code invalid for return => " + line;
            return line;
        }
        value >> line >> std::ws;
        if (value.eof()) {
            if (line[0] == '\"' && line[line.size()] == '\"')
                _config.code.setStatus((int)code, line.substr(1, line.size() - 3));
            else
                _config.code.setDefaultPage((int)code, line);
            _config._return = (int)code;
            addVecInfo("return", &_config._return);
            return std::string();
        }
        return std::string("to much value in return");
    }
    return std::string("no value at return");;
}

std::string Location::setCgiPass(std::string &token){
    (void)token;
    _config._root = _config.pegParser.extractData(';');
    if (_config._root.empty())
        return std::string("no value at root");
    return std::string("");
}

std::string Location::setAutoIndex(std::string &token){
    (void)token;
    _config._root = _config.pegParser.extractData(';');
    if (_config._root.empty())
        return std::string("no value at root");
    return std::string("");
}

void Location::setMapToken() {
    _mapTokenListAction["index"] = &Location::addIndex;
    _mapTokenListAction["root"] =  &Location::setRoot;
    _mapTokenListAction["allow_methods"] =  &Location::setAllowMethods;
    _mapTokenListAction["return"] =  &Location::setReturn;
    _mapTokenListAction["cgi_pass"] =  &Location::setCgiPass;
    _mapTokenListAction["auto_index"] =  &Location::setAutoIndex;
}

void Location::addVecInfo(const std::string& token, void* v) {
    _config._info.push_back(std::make_pair(token, v));
}
