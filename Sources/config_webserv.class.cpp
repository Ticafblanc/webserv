/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configWebserv.class.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/config_webserv.class.hpp"


/*
*==========================================================================================================
*|                                                  Bloc location                                         |
*==========================================================================================================
*/


blocLocation::blocLocation(configWebserv& config)
        : _config(config), _mapTokenListAction(), _root(), _index() {
    setMapToken();
}

blocLocation::~blocLocation() {}

blocLocation::blocLocation(const blocLocation& other)
        : _config(other._config), _root(other._root), _index(other._index) {}

blocLocation &blocLocation::operator=(const blocLocation & rhs) {
    this->_config = rhs._config;
    this->_root = rhs._root;
    this->_index = rhs._index;
    return *this;
}


std::string blocLocation::parseBlocLocation() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string blocLocation::setRoot(){
    _mapTokenListAction.erase("root");
    _root = _config._pegParser.extractData(';');
    //@todo manage error
    return std::string("");

}

std::string blocLocation::addIndex() {
    _mapTokenListAction.erase("index");
    std::string index = _config._pegParser.extractData(';');
    _index.push_back(index);
    return std::string("");

}

void blocLocation::setMapToken() {
    _mapTokenListAction["root"] =  &blocLocation::setRoot;
    _mapTokenListAction["index"] = &blocLocation::addIndex;
}

void blocLocation::setDefaultValue() {

}

/*
*==========================================================================================================
*|                                                listen data                                             |
*==========================================================================================================
*/


listenData::listenData(configWebserv& config, std::string & input)
    : _config(config), _input(input), _ipAddress(), _port(0), _socket(<#initializer#>) {}

listenData::listenData(configWebserv& config, std::string defaultInput)
        : _config(config), _input(defaultInput), _ipAddress(), _port(0), _socket(<#initializer#>) {
    parseListenData();

}

listenData::~listenData() {}
//todo manage close fd at end of programme
/*check if file descriptor is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int fd_isopen();

/*check if AbaseSocket  is open
 * if process fail throw serverSocket::socket_exception();
 */
//    int socket_isopen();

listenData::listenData(const listenData& other)
    : _config(other._config), _input(other._input.str()), _ipAddress(other._ipAddress),
      _port(other._port), _serverSocket(other._serverSocket), _sockaddress(other._sockaddress),
      _socket(<#initializer#>) {}

listenData &listenData::operator=(const listenData & rhs) {
    this->_config = rhs._config;
    this->_input.str() = rhs._input.str();
    this->_ipAddress = rhs._ipAddress;
    this->_port = rhs._port;
    this->_serverSocket = rhs._serverSocket;
    this->_sockaddress = rhs._sockaddress;
    return *this;
}

std::string listenData::parseListenData() {
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


blocServer::blocServer(configWebserv&  config)
        : _config(config), _vectorListen(), _vectorServerName(),
          _root(), _mapBlocLocation(), _epollInstance() {
    setMapToken();
}

blocServer::~blocServer() {}

blocServer::blocServer(const blocServer& other)
        : _config(other._config), _vectorListen(other._vectorListen),
          _vectorServerName(), _root(), _mapBlocLocation(), _epollInstance() {}

blocServer &blocServer::operator=(const blocServer & rhs) {
    this->_config = rhs._config;
    this->_vectorListen = rhs._vectorListen;
    this->_vectorServerName = rhs._vectorServerName;
    this->_root = rhs._root;
    this->_mapBlocLocation = rhs._mapBlocLocation;
    return *this;
}

std::string blocServer::parseBlocServer() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string blocServer::addVectorListen(){
    _mapTokenListAction.erase("listen");
    std::string value = _config._pegParser.extractData(';');
    if (value.empty())
        return std::string("empty");

    value.clear();
    return value;
}

std::string blocServer::addVectorServerName(){
    std::string server_name = _config._pegParser.extractData(';');
    _vectorServerName.push_back(server_name);
    return std::string("");
}

std::string blocServer::setRoot(){
    _mapTokenListAction.erase("root");
    _root = _config._pegParser.extractData(';');
    //@todo manage error
    return std::string("");
}

std::string blocServer::addMapBlocLocation() {
    this->_numberTriggeredEvents = 0;
    std::string path = _config._pegParser.extractData('{');
    //@todo check path ....
    blocLocation blocLocation(_config);
    blocLocation.parseBlocLocation();
    _mapBlocLocation.insert(std::make_pair(path, blocLocation));
    path.clear();
    return path;
}

void blocServer::setDefaultValue() {
    if (_vectorListen.empty())
        _vectorListen.push_back(listenData(_config, "0.0.0.0:8081"));
    (void)_config;
//    if(_vectorServerName.empty() )
//        _vectorServerName.push_back("default_server.com");
//    if(_root.empty())
//        _root = "/usr/local/var/www";
}

void blocServer::setMapToken() {
    _mapTokenListAction["listen"] =  &blocServer::addVectorListen;
    _mapTokenListAction["server_name"] =  &blocServer::addVectorServerName;
    _mapTokenListAction["root"] =  &blocServer::setRoot;
    _mapTokenListAction["location"] =  &blocServer::addMapBlocLocation;
}

blocServer::blocServer() {

}

bool blocServer::EpollWait(int timeOut) {
    return baseEpoll::EpollWait(timeOut);
}

/*
*==========================================================================================================
*|                                                  Bloc http                                             |
*==========================================================================================================
*/


blocHttp::blocHttp(configWebserv& config) : _config(config), _mapTokenListAction(), _vectorBlocServer(),
                                               _mapClientSocket(), _numberMaxEvents(config._blocEvents._workerConnections * config._workerProcess) {
    setMapToken();
}

blocHttp::~blocHttp() {}

blocHttp::blocHttp(blocHttp &other)
    : _config(other._config), _mapTokenListAction(other._mapTokenListAction),
    _vectorBlocServer(other._vectorBlocServer), _mapClientSocket(), _numberMaxEvents(other._numberMaxEvents){}

blocHttp &blocHttp::operator=(const blocHttp &rhs) {
    this->_config = rhs._config;
    this->_vectorBlocServer = rhs._vectorBlocServer;
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_mapClientSocket = rhs._mapClientSocket;
    this->_numberMaxEvents = rhs._numberMaxEvents;
    return *this;
}

std::string blocHttp::parseBlocHttp() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string blocHttp::addVectorBlocServer() {
    std::string value = _config._pegParser.extractData('{');
    if (value.empty()) {
        blocServer buildBlocServer(_config);
        value = buildBlocServer.parseBlocServer();
        _vectorBlocServer.push_back(buildBlocServer);
    }
    return value;
}

void blocHttp::setDefaultValue() {
//    if (_vectorBlocServer.empty()) {
//
//    }
    _numberMaxEvents = _config._blocEvents._workerConnections * _config._workerProcess ;
    blocServer blocServer(_config);
    blocServer.setDefaultValue();
    _vectorBlocServer.push_back(blocServer);
}

void blocHttp::setMapToken() {
    _mapTokenListAction["serverSocket"]= &blocHttp::addVectorBlocServer;
}


/*
*==========================================================================================================
*|                                                  Bloc events                                           |
*==========================================================================================================
*/

blocEvents::blocEvents(configWebserv& config)
    : _config(config), _mapTokenListAction(), _workerConnections(){
    setMapToken();
}

blocEvents::~blocEvents() {}

blocEvents::blocEvents(blocEvents &other)
: _config(other._config), _mapTokenListAction(other._mapTokenListAction), _workerConnections(other._workerConnections) {}


blocEvents &blocEvents::operator=(const blocEvents &rhs) {
   this->_config = rhs._config;
   this->_mapTokenListAction = rhs._mapTokenListAction;
   this->_workerConnections = rhs._workerConnections;
    return *this;
}


std::string blocEvents::parseBlocEvents() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
    setDefaultValue();
    return std::string("");
}

std::string blocEvents::setWorkerConnections() {
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

void blocEvents::setDefaultValue() {
//    if (_mapTokenListAction.size() == 1)
    _workerConnections = 10;
}

void blocEvents::setMapToken() {
    _mapTokenListAction["worker_connections"] = &blocEvents::setWorkerConnections;
}


/*
*==========================================================================================================
*|                                                  Config serverSocket                                         |
*==========================================================================================================
*/

configWebserv::configWebserv() : _pegParser(),_mapTokenListAction(), _workerProcess(),
                            _blocEvents(*this), _blocHttp(*this) {
    setMapToken();
    setDefaultValue();
}

configWebserv::configWebserv(std::string &pathConfigFile) : _pegParser(pathConfigFile.c_str(), "#"),
                                    _mapTokenListAction(), _workerProcess(), _blocEvents(*this), _blocHttp(*this) {
    setMapToken();
    while (!_pegParser.checkIsEmpty()) {
        _pegParser.findToken(*this, _mapTokenListAction, 0);
    }
    setDefaultValue();
}

configWebserv::~configWebserv() {}

configWebserv::configWebserv(configWebserv & other)
    : _pegParser(other._pegParser),_mapTokenListAction(other._mapTokenListAction),
    _workerProcess(other._workerProcess), _blocEvents(other._blocEvents), _blocHttp(other._blocHttp){

}

configWebserv &configWebserv::operator=(const configWebserv &rhs) {
    this->_pegParser = rhs._pegParser;
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_workerProcess = rhs._workerProcess;
    this->_blocEvents = rhs._blocEvents;
    this->_blocHttp = rhs._blocHttp;
    return *this;
}


std::string configWebserv::parseBlocEvent() {
    _mapTokenListAction.erase("events");
    std::string value = _pegParser.extractData('{');
    if (value.empty())
        value = _blocEvents.parseBlocEvents();
    return value;
}

std::string configWebserv::parseBlocHttp() {
    _mapTokenListAction.erase("http");
    std::string value = _pegParser.extractData('{');
    if (value.empty())
        value = _blocHttp.parseBlocHttp();
//    std::cout << "_vectorBlocServer size:" << " " << _blocHttp._vectorBlocServer.size() << std::endl;
//    std::cout << "_vectorBlocServer 0:" << " " <<_ << std::endl;
    return value;
}

std::string configWebserv::setWorkerProcesses() {
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

void configWebserv::setDefaultValue() {
//    std::map<std::string, std::string (configWebserv::*)()>::iterator it = _mapTokenListAction.begin();
    _workerProcess = 1;
    _blocEvents.setDefaultValue();
    _blocHttp.setDefaultValue();
}

void configWebserv::setMapToken() {
    _mapTokenListAction["worker_processes"] = &configWebserv::setWorkerProcesses;
    _mapTokenListAction["events"] = &configWebserv::parseBlocEvent;
    _mapTokenListAction["http"] = &configWebserv::parseBlocHttp;
}





