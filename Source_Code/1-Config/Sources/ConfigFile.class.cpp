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
: _parent(&config), _config(config), _peg(peg), _id() {
    parseFile();
}

ConfigFile::ConfigFile(ConfigFile& other, Config * config)
        : _parent(other._parent), _config(*(new Config(*config))), _peg(other._peg) {}

ConfigFile::~ConfigFile() {}

void ConfigFile::printData(){
    for (std::map<int, Socket*>::iterator itSock = _config._mapFdSocket.begin();
         itSock != _config._mapFdSocket.end(); ++itSock) {
        _config._pidLog.writePidLogFile("Socket fd => " + intToString(itSock->first));
        _config._pidLog.writePidLogFile("ipaddress => " + itSock->second->getIpAddress() + " port => " + intToString(itSock->second->getPort()));
        _config._pidLog.addIndent();
        for(std::vector<std::pair<std::string, std::string> >::iterator itNameToken = itSock->second->getVectorServerNameToken().begin();
            itNameToken != itSock->second->getVectorServerNameToken().end(); ++itNameToken) {
            _config._pidLog.writePidLogFile("server name => " + itNameToken->first + " = Token => " + itNameToken->second);
            for (std::map<std::string, std::vector<std::pair<std::string, Config> > >::iterator itToken = _config._mapTokenVectorUriConfig.begin();
                 itToken != _config._mapTokenVectorUriConfig.end(); ++itToken) {
                if (itToken->first == itNameToken->second) {
                    for (std::vector<std::pair<std::string, Config> >::iterator itConfig = itToken->second.begin();
                         itConfig != itToken->second.end(); ++itConfig) {
                        _config._pidLog.writePidLogFile("uri => " + itConfig->first);
                        for( std::set<std::string>::iterator itIndex = itConfig->second._index.begin();
                             itIndex != itConfig->second._index.end(); ++itIndex){
                            _config._pidLog.writePidLogFile("index => " + *itIndex);
                        }
                        _config._pidLog.writePidLogFile("root => " + itConfig->second._root);
                        _config._pidLog.writePidLogFile("allow method => " + intToString(itConfig->second._allowMethods));
                        _config._pidLog.writePidLogFile("cgi => " + itConfig->second._cgiPass);
                        _config._pidLog.writePidLogFile("autoIndex => " + (std::string) ((itConfig->second._autoindex) ? "true" : "false"));
                        _config._pidLog.writePidLogFile("return => " + intToString(itConfig->second._return));
                    }
                }
            }
        }
        _config._pidLog.removeIndent();
    }
}
void ConfigFile::parseFile() {
    _config._pidLog.addIndent();
    _config._pidLog.writePidLogFile("\r\n\r\n\t\t\t\t#### Config File ####\r\n\r\n");
    setMapToken("");
    while (!_peg.checkIsEmpty()) {
        _peg.findToken(*this, 0);
    }
    if (_config._mapFdSocket.empty())
        throw Exception("No IP:PORT to listen", 0);
    _config._pidLog.writePidLogFile("\r\n\r\n\t\t\t\t#### Config data ####\r\n\r\n");
    printData();
}

void ConfigFile::parseBloc(std::string & id) {
    _config._pidLog.addIndent();
    _config._pidLog.writePidLogFile("####" + id + "####");
    _id = id;
    if (id == "server")
        _config._tok = _config._token.generateToken();
    setMapToken(id);
    while (!_peg.checkIsEndOfBloc('}'))
        _peg.findToken(*this,  0);
    _config._pidLog.removeIndent();
}

std::string ConfigFile::blocToken(std::string & token) {
    std::string value = _peg.extractData('{');
    if ((value.empty()  && token != "location") ||
    (!value.empty() && value[0] == '/' && token == "location")){
        ConfigFile configFile(*this, &_config);
        if (token == "location") {
            configFile._config._root = configFile._config._root + value;
            configFile._config._uri = value;
        }
        configFile.parseBloc(token);
        if (token == "location" || token == "server") {
            if (configFile._config._uri.empty())
                configFile._config._uri = "/";
            _parent->addChild(configFile._config);
            _parent->addServerName(configFile._config);
        }
        setMapToken(_id);
        return "";
    }
    return "unexpected value => " + value;
}

std::string ConfigFile::setWorkerProcesses(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 0 && val < 5){
        _config._workerProcess = static_cast<int>(val);
        _config._pidLog.writePidLogFile("worker processes = " + value);
        return "";
    }
    return "invalide data for worker processes => " + value;

}

std::string ConfigFile::setClientBodyBufferSize(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 1023 && val < 8193){
        _config._clientBodyBufferSize = static_cast<int>(val);
        _config._pidLog.writePidLogFile("client Body buffer size = " + value);
        return "";
    }
    return "invalide data for body buffer size => " + value;

}


std::string ConfigFile::setClientHeaderBufferSize(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 511 && val < 1025){
        _config._clientHeaderBufferSize = static_cast<int>(val);
        _config._pidLog.writePidLogFile("client Header buffer size = " + value);
        return "";
    }
    return "invalide data for header buffer size => " + value;

}

std::string ConfigFile::setClientMaxBodySize(std::string & token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 500000 && val < 1048576){
        _config._clientMaxBodySize = static_cast<int>(val);
        _config._pidLog.writePidLogFile("client max Body size = " + value);
        return "";
    }
    return "invalide data for max body size => " + value;

}

std::string ConfigFile::setWorkerConnections(std::string &token) {
    (void)token;
    std::string value = _peg.extractData(';');
    char * end;
    const long val = std::strtol(value.c_str(), &end, 10);
    if (end != value.c_str() && val > 9 && val < 21){
        _parent->_workerConnections = static_cast<int>(val);
        _config._pidLog.writePidLogFile("worker connection = " + value);
        return "";
    }
    return "invalide data for workerConnection => " + value;

}

std::string ConfigFile::addVectorListen(std::string &token){
    (void)token;
    std::string value = _peg.extractData(';');
    Listen listen(_config, *_parent);
    return listen.parseListenData(value);
}

std::string ConfigFile::addMapAddHeader(std::string &token) {
    (void)token;
    std::string directive = _peg.extractData(' ');
    if (directive == "Content-Disposition") {
        std::string argument = _peg.extractData(';');
        if(argument == "attachment")
            _config._addHeader = std::make_pair(directive, argument);
        return "";
    }
    return std::string("no value at add_header");
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
        _config._pidLog.writePidLogFile("index = " + value.str());
        return "";
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
        _config._name.insert(_config._name.end(), val.begin(), val.end());
        _config._pidLog.writePidLogFile("name = " + value.str());
        return "";
    }
    return std::string("no value at server_name");
}

std::string ConfigFile::setRoot(std::string &token){
    (void)token;
    std::string root = _peg.extractData(';');
    if (root.empty())
        return std::string("no value at root");
    struct stat statBuf;
    if (stat(root.c_str(), &statBuf) == 0)
        _config._root = root;
    else
        return "Path not found => " + root;
    _config._pidLog.writePidLogFile("root = " + root);
    return std::string("");
}

std::string ConfigFile::setCgiPass(std::string &token){
    (void)token;
    std::string cgi = _peg.extractData(';');
    if (cgi.empty())
        return std::string("no value at cgi");
    _config._cgiPass = cgi;
    _config._pidLog.writePidLogFile("cgi pass = " + cgi);
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
        if ( _config._allowMethods > _get + _post + _delete)
            _config._allowMethods = _get + _post + _delete;
        _config._pidLog.writePidLogFile("allow methods = " + value.str() + "conf = " + intToString(_config._allowMethods));
        return "";
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
        line.clear();
        value >> line >> std::ws;
        if (value.eof()) {
            if (!line.empty()) {
                _config._code.setDefaultPage((int) code, line);
                _config._pidLog.writePidLogFile("error page = " + value.str());
                return "";
            }
            return "no index to set" ;
        }
        return "to much value in error page";
    }
    return "no value at error page";
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
            else if (_config._return == 0) {
                if (line.find("http://www.") != 0) || line.substr(line.find_last_of('.')) != "html")
                    return "not html or http://www. content in return";
                _config._code.setDefaultPage((int) code, line);
            }
            else
                return "";
            _config._return = (int)code;
            _config._pidLog.writePidLogFile("return = " + value.str());
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
    _config._pidLog.writePidLogFile("auto index = " + (std::string)((_config._autoindex) ? "on" : "off"));
    return std::string("");
}

void ConfigFile::setMapToken(const std::string & token) {
    if ( token.empty())
        _peg.setMapTokenFile();
    else if(token == "events")
        _peg.setMapTokenEvents();
    else if(token == "http")
        _peg.setMapTokenHttp();
    else if(token == "server")
        _peg.setMapTokenServer();
    else if(token == "location")
        _peg.setMapTokenLocation();
    else
        _peg.clearMapToken();
}

