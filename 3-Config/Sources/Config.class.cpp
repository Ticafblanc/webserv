/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Config.class.hpp"


/*
*==========================================================================================================
*|                                                  Bloc location                                         |
*==========================================================================================================
*/


Location::Location(Config& config)
        : _config(config), _mapTokenListAction(), _root(), _index() {
    setMapToken();
}

Location::~Location() {}

Location::Location(const Location& other)
        : _config(other._config), _root(other._root), _index(other._index) {}

Location &Location::operator=(const Location & rhs) {
    this->_config = rhs._config;
    this->_root = rhs._root;
    this->_index = rhs._index;
    return *this;
}


std::string Location::parseBlocLocation() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string Location::setRoot(){
    _mapTokenListAction.erase("root");
    _root = _config._pegParser.extractData(';');
    //@todo manage error
    return std::string("");

}

std::string Location::addIndex() {
    _mapTokenListAction.erase("index");
    std::string index = _config._pegParser.extractData(';');
    _index.push_back(index);
    return std::string("");

}

void Location::setMapToken() {
    _mapTokenListAction["root"] =  &Location::setRoot;
    _mapTokenListAction["index"] = &Location::addIndex;
}

void Location::setDefaultValue() {

}

/*
*==========================================================================================================
*|                                                listen data                                             |
*==========================================================================================================
*/


Listen::Listen(Config& config, std::string & input)
        : _config(config), _input(input), _ipAddress(), _port(0), _socket(<#initializer#>) {}

Listen::Listen(Config& config, std::string defaultInput)
        : _config(config), _input(defaultInput), _ipAddress(), _port(0), _socket(<#initializer#>) {
    parseListenData();

}

Listen::~Listen() {}
//todo manage close fd at end of programme
/*check if file descriptor is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int fd_isopen();

/*check if AbaseSocket  is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int socket_isopen();

Listen::Listen(const Listen& other)
        : _config(other._config), _input(other._input.str()), _ipAddress(other._ipAddress),
          _port(other._port), _serverSocket(other._serverSocket), _sockaddress(other._sockaddress),
          _socket(<#initializer#>) {}

Listen &Listen::operator=(const Listen & rhs) {
    this->_config = rhs._config;
    this->_input.str() = rhs._input.str();
    this->_ipAddress = rhs._ipAddress;
    this->_port = rhs._port;
    this->_serverSocket = rhs._serverSocket;
    this->_sockaddress = rhs._sockaddress;
    return *this;
}

std::string Listen::parseListenData() {
    std::string port;
    std::getline(_input >> std::ws, _ipAddress, ':');
    _input >> port >> std::ws;
    _port = std::atoi(port.c_str());
    //@todo check port and ip
    return std::string("");
}




/*
*==========================================================================================================
*|                                                  Bloc serverSocket                                             |
*==========================================================================================================
*/


Server::Server(Config&  config)
        : _config(config), _vectorListen(), _vectorServerName(),
          _root(), _mapBlocLocation(), _epollInstance() {
    setMapToken();
}

Server::~Server() {}

Server::Server(const Server& other)
        : _config(other._config), _vectorListen(other._vectorListen),
          _vectorServerName(), _root(), _mapBlocLocation(), _epollInstance() {}

Server &Server::operator=(const Server & rhs) {
    this->_config = rhs._config;
    this->_vectorListen = rhs._vectorListen;
    this->_vectorServerName = rhs._vectorServerName;
    this->_root = rhs._root;
    this->_mapBlocLocation = rhs._mapBlocLocation;
    return *this;
}

std::string Server::parseBlocServer() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string Server::addVectorListen(){
    _mapTokenListAction.erase("listen");
    std::string value = _config._pegParser.extractData(';');
    if (value.empty())
        return std::string("empty");

    value.clear();
    return value;
}

std::string Server::addVectorServerName(){
    std::string server_name = _config._pegParser.extractData(';');
    _vectorServerName.push_back(server_name);
    return std::string("");
}

std::string Server::setRoot(){
    _mapTokenListAction.erase("root");
    _root = _config._pegParser.extractData(';');
    //@todo manage error
    return std::string("");
}

std::string Server::addMapBlocLocation() {
    this->_numberTriggeredEvents = 0;
    std::string path = _config._pegParser.extractData('{');
    //@todo check path ....
    Location Location(_config);
    Location.parseBlocLocation();
    _mapBlocLocation.insert(std::make_pair(path, Location));
    path.clear();
    return path;
}

void Server::setDefaultValue() {
    if (_vectorListen.empty())
        _vectorListen.push_back(Listen(_config, "0.0.0.0:8081"));
    (void)_config;
//    if(_vectorServerName.empty() )
//        _vectorServerName.push_back("default_server.com");
//    if(_root.empty())
//        _root = "/usr/local/var/www";
}

void Server::setMapToken() {
    _mapTokenListAction["listen"] =  &Server::addVectorListen;
    _mapTokenListAction["server_name"] =  &Server::addVectorServerName;
    _mapTokenListAction["root"] =  &Server::setRoot;
    _mapTokenListAction["location"] =  &Server::addMapBlocLocation;
}

Server::Server() {

}

bool Server::EpollWait(int timeOut) {
    return Epoll::EpollWait(timeOut);
}

/*
*==========================================================================================================
*|                                                  Bloc http                                             |
*==========================================================================================================
*/


Http::Http(Config& config) : _config(config), _mapTokenListAction(), _vectorBlocServer(),
                                            _mapClientSocket(), _numberMaxEvents(config._Events._workerConnections * config._workerProcess) {
    setMapToken();
}

Http::~Http() {}

Http::Http(Http &other)
        : _config(other._config), _mapTokenListAction(other._mapTokenListAction),
          _vectorBlocServer(other._vectorBlocServer), _mapClientSocket(), _numberMaxEvents(other._numberMaxEvents){}

Http &Http::operator=(const Http &rhs) {
    this->_config = rhs._config;
    this->_vectorBlocServer = rhs._vectorBlocServer;
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_mapClientSocket = rhs._mapClientSocket;
    this->_numberMaxEvents = rhs._numberMaxEvents;
    return *this;
}

std::string Http::parseBlocHttp() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string Http::addVectorBlocServer() {
    std::string value = _config._pegParser.extractData('{');
    if (value.empty()) {
        Server buildBlocServer(_config);
        value = buildBlocServer.parseBlocServer();
        _vectorBlocServer.push_back(buildBlocServer);
    }
    return value;
}

void Http::setDefaultValue() {
//    if (_vectorBlocServer.empty()) {
//
//    }
    _numberMaxEvents = _config._Events._workerConnections * _config._workerProcess ;
    Server Server(_config);
    Server.setDefaultValue();
    _vectorBlocServer.push_back(Server);
}

void Http::setMapToken() {
    _mapTokenListAction["serverSocket"]= &Http::addVectorBlocServer;
}


/*
*==========================================================================================================
*|                                                  Bloc events                                           |
*==========================================================================================================
*/

Events::Events(Config& config)
        : _config(config), _mapTokenListAction(), _workerConnections(){
    setMapToken();
}

Events::~Events() {}

Events::Events(Events &other)
        : _config(other._config), _mapTokenListAction(other._mapTokenListAction), _workerConnections(other._workerConnections) {}


Events &Events::operator=(const Events &rhs) {
    this->_config = rhs._config;
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_workerConnections = rhs._workerConnections;
    return *this;
}


std::string Events::parseBlocEvents() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string Events::setWorkerConnections() {
    _mapTokenListAction.erase("worker_connections");
    std::string value = _config._pegParser.extractData(';');
    char * end;//@todo to manage error
    const long val = std::strtol(value.c_str(), &end, 10);
    if (val < 10 || val > 20)
        return value;
    _workerConnections = static_cast<int>(val);
    value.clear();
    return value;
}

void Events::setDefaultValue() {
//    if (_mapTokenListAction.size() == 1)
    _workerConnections = 10;
}

void Events::setMapToken() {
    _mapTokenListAction["worker_connections"] = &Events::setWorkerConnections;
}


/*
*==========================================================================================================
*|                                                  Config serverSocket                                         |
*==========================================================================================================
*/

Config::Config() : _pegParser(),_mapTokenListAction(), _workerProcess(),
                                 _Events(*this), _Http(*this) {
    setMapToken();
    setDefaultValue();
}

Config::Config(std::string &pathConfigFile) : _pegParser(pathConfigFile.c_str(), "#"),
                                                            _mapTokenListAction(), _workerProcess(), _Events(*this), _Http(*this) {
    setMapToken();
    while (!_pegParser.checkIsEmpty()) {
        _pegParser.findToken(*this, _mapTokenListAction, 0);
    }
    setDefaultValue();
}

Config::~Config() {}

Config::Config(Config & other)
        : _pegParser(other._pegParser),_mapTokenListAction(other._mapTokenListAction),
          _workerProcess(other._workerProcess), _Events(other._Events), _Http(other._Http){

}

Config &Config::operator=(const Config &rhs) {
    this->_pegParser = rhs._pegParser;
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_workerProcess = rhs._workerProcess;
    this->_Events = rhs._Events;
    this->_Http = rhs._Http;
    return *this;
}


std::string Config::parseBlocEvent() {
    _mapTokenListAction.erase("events");
    std::string value = _pegParser.extractData('{');
    if (value.empty())
        value = _Events.parseBlocEvents();
    return value;
}

std::string Config::parseBlocHttp() {
    _mapTokenListAction.erase("http");
    std::string value = _pegParser.extractData('{');
    if (value.empty())
        value = _Http.parseBlocHttp();
//    std::cout << "_vectorBlocServer size:" << " " << _Http._vectorBlocServer.size() << std::endl;
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
//    std::map<std::string, std::string (Config::*)()>::iterator it = _mapTokenListAction.begin();
    _workerProcess = 1;
    _Events.setDefaultValue();
    _Http.setDefaultValue();
}

void Config::setMapToken() {
    _mapTokenListAction["worker_processes"] = &Config::setWorkerProcesses;
    _mapTokenListAction["events"] = &Config::parseBlocEvent;
    _mapTokenListAction["http"] = &Config::parseBlocHttp;
    _mapTokenListAction["types"] = &Config::parseBlocHttp;
}




