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


ConfigFile::ConfigFile(Config & config, PegParser<ConfigFile>& peg)
: _config(config), _peg(peg), _parent(&config) {
    parseFile();
}

ConfigFile::ConfigFile(ConfigFile& other, Config * config)
        : _config(*(new Config(*config))), _peg(other._peg), _parent(other._parent) {}

ConfigFile::~ConfigFile() {}

void ConfigFile::parseFile() {
    setMapToken("");
    while (!_peg.checkIsEmpty()) {
        _peg.findToken(*this, 0);
    }
    if (_config._listen.empty())
        throw Exception("No listen");
}

void ConfigFile::parseBloc() {
    while (!_peg.checkIsEndOfBloc('}'))
        _peg.findToken(*this,  0);
}

std::string ConfigFile::blocToken(std::string & token) {
    std::string value = _peg.extractData('{');
    if (value.empty() || (!value.empty() && token == "location")){
        ConfigFile configFile(*this, &_config);
        configFile.setMapToken(token);
        configFile.parseBloc();
        if (token == "location" || (token == "server")) {
            _config.addChild(configFile._config);
        }
        return "";
    }


    return "unexpected value =>" + value;
}

std::string ConfigFile::setWorkerProcesses(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 0 && val < 5)
        value.clear();
    else
        return "invalide data for worker processes =>" + value;
    _config._workerProcess = static_cast<int>(val);
    return value;
}

std::string ConfigFile::setClientBodyBufferSize(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 1023 && val < 8193)
        value.clear();
    else
        return "invalide data for body buffer size =>" + value;
    _config._clientBodyBufferSize = static_cast<int>(val);
    return value;
}


std::string ConfigFile::setClientHeaderBufferSize(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 511 && val < 1025)
        value.clear();
    else
        return "invalide data for header buffer size =>" + value;
    _config._clientHeaderBufferSize = static_cast<int>(val);
    return value;
}

std::string ConfigFile::setClientMaxBodySize(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 500000 && val < 1048576)
        value.clear();
    else
        return "invalide data for max body size =>" + value;
    _config._clientMaxBodySize = static_cast<int>(val);
    return value;
}

std::string ConfigFile::setWorkerConnections(std::string &token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end == value.c_str() || val < 10 || val > 20)
        value.clear();
    else
        return "invalide data for workerConnection =>" + value;
    _parent->_workerConnections = static_cast<int>(val);
    return value;
}

std::string ConfigFile::addVectorListen(std::string &token){
    (void)token;
    std::string value = _peg.extractData(';');
    Listen listen(*_parent);
    return listen.parseListenData(value);
}

std::string ConfigFile::addIndex(std::string &token){
    (void)token;
    std::stringstream value(_peg.extractData(';'));
    if (!value.str().empty()) {
        std::vector<std::string> val;
        while (!value.eof()) {
            std::string line;
            value >> line >> std::ws;
            val.push_back(line);
        }
        _config.addToSet(val, _config._index);
        return std::string();
    }
    return std::string("no value at index");
}

std::string ConfigFile::addVectorServerName(std::string &token){
    (void)token;
    std::stringstream value(_peg.extractData(';'));
    if (!value.str().empty()) {
        std::vector<std::string> val;
        while (!value.eof()) {
            std::string line;
            value >> line >> std::ws;
            val.push_back(line);
        }
        _config.addToSet(val, _config._name);
        return std::string();
    }
    return std::string("no value at server_name");
}

std::string ConfigFile::setRoot(std::string &token){
    (void)token;
    std::string root = _peg.extractData(';');
    if (root.empty())
        return std::string("no value at root");
    struct stat statBuf;
    if (stat(root.c_str(), &statBuf) != 0)
        _config._root = root;
    else
        return "Path not found => " + root;
    return std::string("");
}

std::string ConfigFile::setCgiPass(std::string &token){
    (void)token;
    std::string cgi = _peg.extractData(';');
    if (cgi.empty())
        return std::string("no value at cgi");
    _config._cgiPass = cgi;
    return std::string("");
}

std::string ConfigFile::setAllowMethods(std::string &token){
    (void)token;
    int _get = 0;
    int _post = 0;
    int _delete = 0;

    std::stringstream value(_peg.extractData(';'));
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
    }
    return std::string("no value at allow_methods");
}

std::string ConfigFile::setErrorPage(std::string &token){
    (void)token;
    std::stringstream value(_peg.extractData(';'));
    if (!value.str().empty()){
        std::string line;
        value >> line >> std::ws;
        char * end;
        const long code = std::strtol(line.c_str(), &end, 10);
        if (end == line.c_str() || code < 100 || code > 599 || !_config._code.FindCode((int)code)) {
            line = "value in code invalid for return => " + line;
            return line;
        }
        value >> line >> std::ws;
        if (value.eof()) {
            _config._code.setDefaultPage((int)code, line);
            return std::string();
        }
        return std::string("to much value in error page");
    }
    return std::string("no value at error page");;
}

std::string ConfigFile::setReturn(std::string & token) {
    (void)token;
    std::stringstream value(_peg.extractData(';'));
    if (!value.str().empty()){
        std::string line;
        value >> line >> std::ws;
        char * end;
        const long code = std::strtol(line.c_str(), &end, 10);
        if (end == line.c_str() || code < 100 || code > 599 || !_config._code.FindCode((int)code)) {
            line = "value in code invalid for return => " + line;
            return line;
        }
        value >> line >> std::ws;
        if (value.eof()) {
            if (line[0] == '\"' && line[line.size()] == '\"' && _config._return == 0)
                _config._code.setStatus((int)code, line.substr(1, line.size() - 3));
            else if (_config._return == 0)
                _config._code.setDefaultPage((int)code, line);
            else
                return "";
            _config._return = (int)code;
            return "";
        }
        return std::string("to much value in return");
    }
    return std::string("no value at return");;
}

std::string ConfigFile::setAutoIndex(std::string &token){
    (void)token;
    std::string value = _peg.extractData(';');
    if (value.empty())
        return std::string("no value at auto index");
    if (value == "on" || value == "off")
        _config._autoindex = (value == "on") ? true : false;
    else
        return std::string("error value at auto index");
    return std::string("");
}

void ConfigFile::setMapToken(const std::string & token) {
    if ( token.empty())
        setMapTokenFile();
    else if(token == "events")
        setMapTokenEvents();
    else if(token == "http")
        setMapTokenHttp();
    else if(token == "server")
        setMapTokenServer();
    else if(token == "location")
        setMapTokenLocation();
    else
        _peg.clearMapToken();
}

void ConfigFile::setMapTokenFile() {
    _peg.clearMapToken();
    _peg.setMapToken("worker_processes", &ConfigFile::setWorkerProcesses);
    _peg.setMapToken("client_body_buffer_size", &ConfigFile::setClientBodyBufferSize);
    _peg.setMapToken("client_header_buffer_size", &ConfigFile::setClientHeaderBufferSize);
    _peg.setMapToken("client_max_body_size", &ConfigFile::setClientMaxBodySize);
    _peg.setMapToken("events", &ConfigFile::blocToken);
    _peg.setMapToken("http", &ConfigFile::blocToken);
    _peg.setMapToken("server", &ConfigFile::blocToken);
}

void ConfigFile::setMapTokenEvents() {
    _peg.clearMapToken();
    _peg.setMapToken("worker_connections", &ConfigFile::setWorkerConnections);
}

void ConfigFile::setMapTokenHttp() {
    _peg.clearMapToken();
    _peg.setMapToken("listen", &ConfigFile::addVectorListen);
    _peg.setMapToken("server_name", &ConfigFile::addVectorServerName);
    _peg.setMapToken("root", &ConfigFile::setRoot);
    _peg.setMapToken("index", &ConfigFile::addIndex);
    _peg.setMapToken("error_page", &ConfigFile::setErrorPage);
    _peg.setMapToken("auto_index", &ConfigFile::setAutoIndex);
    _peg.setMapToken("allow_methods", &ConfigFile::setAllowMethods);
    _peg.setMapToken("server", &ConfigFile::blocToken);
}

void ConfigFile::setMapTokenServer() {
    _config._tok = _config._token.generateToken();
    _peg.setMapToken("location", &ConfigFile::blocToken);
}

void ConfigFile::setMapTokenLocation() {
    _peg.setMapToken("return", &ConfigFile::setReturn);
    _peg.setMapToken("cgi_pass", &ConfigFile::setClientBodyBufferSize);
}