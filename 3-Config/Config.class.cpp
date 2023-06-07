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

#include "3-Config/Config.class.hpp"


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

Listen::Listen(Config& config) : _config(config), _ipAddress(), _port() {}

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
        : _config(other._config), _ipAddress(other._ipAddress),
          _port(other._port){}

Listen &Listen::operator=(const Listen & rhs) {
    this->_config = rhs._config;
    this->_ipAddress = rhs._ipAddress;
    this->_port = rhs._port;
    return *this;
}

std::string Listen::parseListenData() {
    //@todo check port and ip
    return std::string("");
}

std::string Listen::parseListenData(std::string in) {
    std::stringstream input(in);
    std::string port;
    std::getline(input >> std::ws, _ipAddress, ':');
    input >> port >> std::ws;
    _port = std::atoi(port.c_str());
    return std::string();
}


/*
*==========================================================================================================
*|                                                  Bloc serverSocket                                             |
*==========================================================================================================
*/

//Server::Server() : _config(*(new Config) ) {}

Server::Server(Config &config)
: _config(config), _epoll(*(new Epoll)), _mapTokenListAction(), _vectorServerSocket(),
  _vectorServerName(), _root(), _mapBlocLocation() {
    setMapToken();
}

Server::~Server() {
//    delete[] &_epoll;
}

Server::Server(const Server& other)
        : _config(other._config), _epoll(other._epoll), _mapTokenListAction(other._mapTokenListAction), _vectorServerSocket(other._vectorServerSocket),
          _vectorServerName(other._vectorServerName), _root(other._root), _mapBlocLocation(other._mapBlocLocation){}

Server &Server::operator=(const Server & rhs) {
    if (this != &rhs) {
        this->_epoll = rhs._epoll;
        this->_mapTokenListAction = rhs._mapTokenListAction;
        this->_vectorServerSocket = rhs._vectorServerSocket;
        this->_vectorServerName = rhs._vectorServerName;
        this->_root = rhs._root;
        this->_mapBlocLocation = rhs._mapBlocLocation;
    }
    return *this;
}

std::string Server::parseBlocServer() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
//    setDefaultValue();
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
    std::string path = _config._pegParser.extractData('{');
    //@todo check path ....
    Location Location(_config);
    Location.parseBlocLocation();
    _mapBlocLocation.insert(std::make_pair(path, Location));
    path.clear();
    return path;
}

void Server::setDefaultValue(std::string address) {
    Listen lisdef(_config);
    lisdef.parseListenData(address);
    Socket sock1(lisdef._ipAddress, lisdef._port);
    _vectorServerSocket.push_back(sock1);
    _vectorServerName.push_back("sever_name.com") ;
    _root = "/usr/local/var/www";
    Location locdef(_config);
    _mapBlocLocation.insert(std::make_pair("/html", locdef));
}

void Server::setMapToken() {
    _mapTokenListAction["listen"] =  &Server::addVectorListen;
    _mapTokenListAction["server_name"] =  &Server::addVectorServerName;
    _mapTokenListAction["root"] =  &Server::setRoot;
    _mapTokenListAction["location"] =  &Server::addMapBlocLocation;
}

void Server::manageEvent(epoll_event &event){
    if (!isNewClient(event)){
        if (!isClient(event))
            return;
    }
    //reponse request
}

bool Server::isNewClient(epoll_event &event){
    std::vector<Socket>::iterator itSocket = std::find_if(_vectorServerSocket.begin(),
                                                          _vectorServerSocket.end(),
                                                          Socket(event));
    if (itSocket != _vectorServerSocket.end()) {
        if ((!(event.events & EPOLLERR)) || (!(event.events & EPOLLHUP)) || (event.events & EPOLLIN)) {
            Socket newClientSocket(event);
            _epoll.addSocket(newClientSocket.getSocket());
            _vectorClientSocket.push_back(newClientSocket);
            return true;
        } else {
            std::cerr << "error event at connexion " << std::endl;
        }
    }
    return false;
}

bool Server::isClient(epoll_event &event) {
    std::vector<Socket>::iterator itSocket = std::find_if(_vectorClientSocket.begin(),
                                                          _vectorClientSocket.end(),
                                                          Socket(event));
    if (itSocket != _vectorServerSocket.end()) {
        if ((!(event.events & EPOLLERR)) || (!(event.events & EPOLLHUP)) || (event.events & EPOLLIN)) {

            return true;
        } else {
            close(itSocket->getSocket());
            _epoll.removeSocket(itSocket->getSocket());
            _vectorClientSocket.erase(itSocket);//@todo manage close socket
        }

    }
    return false;
}

/*
*==========================================================================================================
*|                                                  mime type                                             |
*==========================================================================================================
*/


Types::Types(std::string pathFile) : _peg(pathFile.c_str()), _mapMimeType(){
    parseBlocTypes();
}

Types::~Types() {}

Types::Types(Types & other) : _peg(other._peg), _mapMimeType(other._mapMimeType){}

Types &Types::operator=(const Types &rhs) {
    this->_peg = rhs._peg;
    this->_mapMimeType = rhs._mapMimeType;
    return *this;
}

std::string Types::parseBlocTypes() {
    std::string value;
    std::string token;

    while (!_peg.checkIsEndOfBloc('}')) {
        value = _peg.extractData(0);
        token = _peg.extractData(';');
        _mapMimeType[token] = value;
    }
    return std::string();
}

/*
*==========================================================================================================
*|                                                  Bloc http                                             |
*==========================================================================================================
*/

std::string path("/webserv/config_content_server/for_etc/webserv/conf/mime.types");
Http::Http(Config& config) : _config(config), _mapTokenListAction(), _vecPairServerEpoll(), _Types(path),
_clientBodyBufferSize(8192), _clientHeaderBufferSize(1024), _clientMaxBodySize(1048576){
    setMapToken();
}

Http::~Http() {}

Http::Http(Http &other)
        : _config(other._config), _mapTokenListAction(other._mapTokenListAction),
        _vecPairServerEpoll(other._vecPairServerEpoll), _Types(other._Types),
          _clientBodyBufferSize(8192), _clientHeaderBufferSize(1024), _clientMaxBodySize(1048576){}

Http &Http::operator=(const Http &rhs) {
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_vecPairServerEpoll = rhs._vecPairServerEpoll;
    this->_Types = rhs._Types;
    this->_clientBodyBufferSize = rhs._clientBodyBufferSize;
    this->_clientHeaderBufferSize = rhs._clientHeaderBufferSize;
    this->_clientMaxBodySize = rhs._clientMaxBodySize;
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
//        _config._vectorServer.push_back(buildBlocServer);
    }
    return value;
}

void Http::setDefaultValue() {
    Server Server1(_config);
    Server1.setDefaultValue("0.0.0.0:8080");
    Epoll epoll(Server1._vectorServerSocket, _config._Events._workerConnections);
    Server1._epoll = epoll;
    _vecPairServerEpoll.push_back(std::make_pair(Server1, epoll));
    Server Server2(_config);
    Server2.setDefaultValue("0.0.0.0:8081");
    Epoll epoll2(Server2._vectorServerSocket, _config._Events._workerConnections);
    Server2._epoll = epoll2;
    _vecPairServerEpoll.push_back(std::make_pair(Server2, epoll2));
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
        : _config(config), _mapTokenListAction(), _workerConnections(10){
    setMapToken();
}

Events::~Events() {}

Events::Events(Events &other)
        : _config(other._config), _mapTokenListAction(other._mapTokenListAction), _workerConnections(other._workerConnections) {}


Events &Events::operator=(const Events &rhs) {
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_workerConnections = rhs._workerConnections;
    return *this;
}


std::string Events::parseBlocEvents() {
    while (!_config._pegParser.checkIsEndOfBloc('}'))
        _config._pegParser.findToken(*this, _mapTokenListAction, 0);
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

void Events::setMapToken() {
    _mapTokenListAction["worker_connections"] = &Events::setWorkerConnections;
}


/*
*==========================================================================================================
*|                                                  Config                                                |
*==========================================================================================================
*/

//Config::Config() : _pegParser(), _mapTokenListAction(), _workerProcess(),
//_errorLog("logs/error.logs"), _pidLog("logs/webserv.pid"), _Events(*this),
//_Http(*this){}

Config::Config(std::string &pathConfigFile, char ** envp) : _pegParser(/*pathConfigFile.c_str(), "#"*/),
_mapTokenListAction(), _workerProcess(1), _errorLog("logs/error.logs"), _pidLog("logs/webserv.pid"),
_Events(*this), _Http(*this), _enp(setEnvp(envp)) {
    if (!pathConfigFile.empty()) {
        setMapToken();
        while (!_pegParser.checkIsEmpty()) {
            _pegParser.findToken(*this, _mapTokenListAction, 0);
        }
    }
    setDefaultValue();
}

Config::~Config() {}

Config::Config(Config & other)
        : _pegParser(other._pegParser),_mapTokenListAction(other._mapTokenListAction),
          _workerProcess(other._workerProcess), _errorLog(other._errorLog), _pidLog(other._pidLog),
          _Events(other._Events), _Http(other._Http){}

Config &Config::operator=(const Config &rhs) {
    this->_pegParser = rhs._pegParser;
    this->_mapTokenListAction = rhs._mapTokenListAction;
    this->_workerProcess = rhs._workerProcess;
    this->_errorLog = rhs._errorLog;
    this->_pidLog = rhs._pidLog;
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
    _Http.setDefaultValue();
}

void Config::setMapToken() {
    _mapTokenListAction["worker_processes"] = &Config::setWorkerProcesses;
    _mapTokenListAction["events"] = &Config::parseBlocEvent;
    _mapTokenListAction["http"] = &Config::parseBlocHttp;
}

char** Config::setEnvp(char **envp){
    if (envp) {
        std::vector<char *> vecEnvp;
        for (int i = 0; envp[i] != NULL; ++i) {
            char * tmp = strdup(envp[i]);
            vecEnvp.push_back(tmp);
        }
        vecEnvp.push_back(NULL);
        char **newEnvp = new char *[vecEnvp.size()];
        std::copy(vecEnvp.begin(), vecEnvp.end(), newEnvp);
        return newEnvp;
    }
    return NULL;
}

