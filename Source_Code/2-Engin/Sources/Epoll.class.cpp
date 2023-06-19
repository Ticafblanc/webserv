//
// Created by Matthis DoQuocBao on 2023-06-02.
//

#include <Source_Code/2-Engin/Includes/Epoll.class.hpp>


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

Epoll::Epoll(Config& config)
: epoll_event(), _config(config), _epollInstanceFd(),
_events(new epoll_event[config._workerConnections]),_numberTriggeredEvents() {}

Epoll::~Epoll() {
//    delete[] _events;
}

Epoll::Epoll(const Epoll &other)
: epoll_event(other), _config(other._config), _epollInstanceFd(other._epollInstanceFd),
 _events(other._events), _numberTriggeredEvents(other._numberTriggeredEvents) {}

Epoll &Epoll::operator=(const Epoll &rhs) {
    if (this != &rhs) {
        epoll_event::operator=(rhs);
        this->_config = rhs._config;
        this->_epollInstanceFd = rhs._epollInstanceFd;
        delete[] this->_events;
        this->_events = rhs._events;
        this->_numberTriggeredEvents = rhs._numberTriggeredEvents;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

Epoll::epollException::epollException(const char * message)
        : _message(message){}

Epoll::epollException::~epollException() throw() {}

const char * Epoll::epollException::what() const throw() { return _message.c_str(); }

Epoll::epollException::epollException(const Epoll::epollException & other)
        : _message(other._message) {}

Epoll::epollException &Epoll::epollException::operator=(const Epoll::epollException &rhs) {
    this->_message = rhs._message;
    return *this;
}

/*
*====================================================================================
*|                               public method                                      |
*====================================================================================
*/

void Epoll::setEpollEvent(int socket, int flag){
    data.fd = socket;
    events = flag;
}

void Epoll::createEpollInstance(int nbr) {
    _epollInstanceFd = epoll_create(nbr);
    if (_epollInstanceFd == -1)
        throw epollException(strerror(errno));
}

void Epoll::setEpollCtl(int  option){
    if (epoll_ctl(_epollInstanceFd, option, data.fd, this) == -1){
        close (data.fd);
        throw epollException(strerror(errno));
    }

}

bool Epoll::EpollWait(int timeOut) {
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config._workerConnections, timeOut);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    manageEvent();
    return (_numberTriggeredEvents > 0);
}

bool Epoll::EpollWait() {
    _config._accessLog.writeLogFile("Epoll Wait ...");
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config._workerConnections, -1);
    if ( _numberTriggeredEvents == -1) {
        _config._accessLog.failure();
        throw epollException(strerror(errno));
    }
    _config._accessLog.writeLogFile("[" + intToString(_numberTriggeredEvents) + "] New Events {");
    _config._accessLog.addIndent();
    manageEvent();
    _config._accessLog.removeIndent();
    _config._accessLog.writeLogFile("}");
    return (_numberTriggeredEvents > 0);
}

void Epoll::addSocket(int socket, int events){
    _config._accessLog.writeLogFile("Add Socket [" +
    intToString(socket) + "] to Epoll with events flag [" +
    _config._accessLog.convertEventsTostring(events) + "]");
    setEpollEvent(socket, events);
    setEpollCtl(EPOLL_CTL_ADD) ;
    _config._workerConnections--;
    _config._accessLog.success();
}

void Epoll::modSocket(int socket, int events){
    _config._accessLog.writeLogFile("Mod Socket [" +
    intToString(socket) + "] to Epoll with events flag [" +
    _config._accessLog.convertEventsTostring(events) + "]");
    setEpollEvent(socket, events);
    setEpollCtl(EPOLL_CTL_MOD);
    _config._accessLog.success();
}

void Epoll::removeSocket(int socket){
    _config._accessLog.writeLogFile("Remove Socket [" +
    intToString(socket) + "]");
    setEpollEvent(socket, 0);
    setEpollCtl(EPOLL_CTL_DEL);
    close(socket);
    _config._workerConnections++;
    _config._accessLog.success();
}

void Epoll::launchEpoll(){
    _config._accessLog.writeLogFile("Create Epoll Instance ...");
    createEpollInstance(_config._mapFdSocket.size());
    _config._accessLog.success();
    for (std::map<int, Socket>::iterator it = _config._mapFdSocket.begin();
         it != _config._mapFdSocket.end(); ++it) {
        _config._accessLog.writeLogFile("starts monitoring on [" +
        it->second.getIpAddress() + ":" + intToString(it->second.getPort()) + "]");
        addSocket(it->first, EPOLLIN);
        _config._accessLog.success();
    }
}

void Epoll::manageEvent() {
    std::map<int, Socket>::iterator it;
    for (int i = 0; i < _numberTriggeredEvents; ++i) {
        _config._accessLog.writeLogFile("Event number [" + intToString(i) +
        "] with an event fd [ " + intToString(_events[i].data.fd) + "] and events flag => [" +
        _config._accessLog.convertEventsTostring(_events[i].events) + "]");
        try {
            it = _config._mapFdSocket.find(_events[i].data.fd);
            if (it != _config._mapFdSocket.end() && (it->second.getclient()._server == 0))
                addConnexion(i);
            else if (it != _config._mapFdSocket.end() && it->second.checkSocket(_events[i].data.fd))
                selectEvent(it->second, i);
            else {
                if (_events[i].data.fd == 0)
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                else
                    close(_events[i].data.fd);
            }
        }catch (std::exception & e){
            _config._accessLog.failure();
            _config._errorLog.writeLogFile(e.what());
        }
    }
    checkConnexion();
}

void Epoll::addConnexion(int numberTrigged) {
    if ((!(_events[numberTrigged].events & EPOLLERR)) ||(!(_events[numberTrigged].events & EPOLLHUP))
    || (!(_events[numberTrigged].events & EPOLLRDHUP)) || (_events[numberTrigged].events & EPOLLIN)) {
        _config._accessLog.writeLogFile("Accept new client {");
        _config._accessLog.addIndent();
        Socket newClient(_events[numberTrigged]);
        _config._accessLog.writeLogFile("Address ["  + newClient.getIpAddress() + ":"
        + intToString(newClient.getPort()) + "] with socket [" + intToString(newClient.getSocket()) +
        "] on socket server [" + intToString(newClient.getclient()._server) + "]");
        addSocket(newClient.getSocket(), EPOLLIN | EPOLLET);
        _config._accessLog.removeIndent();
        _config._accessLog.writeLogFile("}");
        _config._accessLog.writeLogFile("Connexion available [" + intToString(_config._workerConnections) + "]");
    }
}

void Epoll::removeConnexionServer(Socket &server) {
    _config._accessLog.writeLogFile("Remove client {");
    _config._accessLog.addIndent();
    _config._accessLog.writeLogFile("Address ["  + server.getIpAddress() + ":"
    + intToString(server.getPort()) + "] with socket [" + intToString(server.getSocket()) +
    "] on socket server [" + intToString(server.getclient()._server) + "]");
    removeSocket(server.getSocket());
    _config._mapFdSocket.erase(server.getSocket());
    _config._accessLog.removeIndent();
    _config._accessLog.writeLogFile("}");
    _config._accessLog.writeLogFile("Connexion available [" + intToString(_config._workerConnections) + "]");
}

void Epoll::checkConnexion(){
    std::time_t currentTime = std::time(NULL);
    currentTime -= 10;
    for (std::map<int, Socket>::iterator itSock = _config._mapFdSocket.begin();
    itSock != _config._mapFdSocket.end(); ++itSock) {
        if (!itSock->second.getclient()._connection || currentTime > itSock->second.getclient()._lastConnection)
            removeConnexionServer(itSock->second);
    }
}

void Epoll::selectEvent(Socket &client, int numberTrigged) {
    if (((_events[numberTrigged].events & EPOLLERR)) ||((_events[numberTrigged].events & EPOLLHUP))
        || ((_events[numberTrigged].events & EPOLLRDHUP))) {
        removeConnexionServer(client);
        return;
    }
    client.getclient()._lastConnection = std::time(NULL);
    try {
        if (_events[numberTrigged].events & EPOLLIN) {
            _config._accessLog.writeLogFile("Recv data {");
            _config._accessLog.addIndent();
            _config._accessLog.writeLogFile("Address [" + client.getIpAddress() + ":"
            + intToString(client.getPort()) + "] with socket [" + intToString(client.getSocket()) +
              "] on socket server [" + intToString(client.getclient()._server) + "]");
            HttpMessage message(client, _config);
            if(!client.getclient()._content.empty()) {
                modSocket(_events[numberTrigged].data.fd, EPOLLOUT | EPOLLET);
            }
            _config._accessLog.removeIndent();
            _config._accessLog.writeLogFile("}");
        }
        if (_events[numberTrigged].events & EPOLLOUT) {
            _config._accessLog.writeLogFile("send data {");
            _config._accessLog.addIndent();
            _config._accessLog.writeLogFile("Address [" + client.getIpAddress() + ":"
            + intToString(client.getPort()) + "] with socket [" + intToString(client.getSocket()) +
            "] on socket server [" + intToString(client.getclient()._server) + "]");
            HttpReponse reponse(client, _config);
            modSocket(_events[numberTrigged].data.fd, EPOLLIN | EPOLLET);
            _config._accessLog.removeIndent();
            _config._accessLog.writeLogFile("}");
        }
    }catch (std::exception & e){
        _config._accessLog.failure();
        _config._errorLog.writeLogFile(e.what());
    }
    if (!client.getclient()._connection)
        removeConnexionServer(client);
}


//bool Server::checkEvent(epoll_event &event){
//    std::vector<Socket>::iterator itSocket = std::find_if(_vectorServerSocket.begin(),
//                                                          _vectorServerSocket.end(),
//                                                          Socket(event));
//    if (itSocket != _vectorServerSocket.end() && ((!(event.events & EPOLLERR)) ||
//                                                  (!(event.events & EPOLLHUP)) || (event.events & EPOLLIN)))
//        return true;
//    else
//        std::cerr << "error event at connexion " << event.events << event.data.fd << std::endl;
//    return false;
//}