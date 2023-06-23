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
    delete[] _events;
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
        throw Exception(strerror(errno), 503);
}

void Epoll::setEpollCtl(int  option){
    if (epoll_ctl(_epollInstanceFd, option, data.fd, this) == -1){
        close (data.fd);
        throw Exception(strerror(errno), 503);
    }

}

bool Epoll::EpollWait(int timeOut) {
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config._workerConnections, timeOut);
    if ( _numberTriggeredEvents == -1)
        throw Exception(strerror(errno), 503);
    manageEvent();
    return (_numberTriggeredEvents > 0);
}

bool Epoll::EpollWait() {
    _config._accessLog.writeLogFile("Epoll Wait ...");
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config._workerConnections, -1);
    if ( _numberTriggeredEvents == -1) {
        _config._accessLog.failure();
        throw Exception(strerror(errno), 503);
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

    for (std::map<int, Socket*>::iterator it = _config._mapFdSocket.begin();
         it != _config._mapFdSocket.end(); ++it) {
        _config._accessLog.writeLogFile("starts monitoring on [" +
        it->second->getIpAddress() + ":" + intToString(it->second->getPort()) + "]");
        addSocket(it->first, EPOLLIN);
        _config._accessLog.success();
    }
}

void Epoll::manageEvent() {
    for (int i = 0; i < _numberTriggeredEvents; ++i) {

        _config._accessLog.writeLogFile("Event number [" + intToString(i) +
        "] with an event fd [ " + intToString(_events[i].data.fd) + "] and events flag => [" +
        _config._accessLog.convertEventsTostring(_events[i].events) + "]");

        std::map<int, Socket*>::iterator it = _config._mapFdSocket.find(_events[i].data.fd);
        if (it != _config._mapFdSocket.end() && (it->second->getServer()))
            addConnexion(i, it->second);
        else if (it != _config._mapFdSocket.end() && it->second->checkSocket(_events[i].data.fd))
            selectEvent(dynamic_cast<Client*>(it->second), i);
//            else {
//                if (_events[i].data.fd == 0)
//                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                else
//                    close(_events[i].data.fd);
//            }
    }
    checkConnexion();
}

void Epoll::addConnexion(int numberTrigged, Socket * server) {
    if ((!(_events[numberTrigged].events & EPOLLERR)) ||(!(_events[numberTrigged].events & EPOLLHUP))
    || (!(_events[numberTrigged].events & EPOLLRDHUP)) || (_events[numberTrigged].events & EPOLLIN)) {

        _config._accessLog.writeLogFile("Accept new client {");
        _config._accessLog.addIndent();
        try {

            Client* newClient = new Client(_events[numberTrigged], _config, server);

            _config._accessLog.writeLogFile("Address ["  + newClient->getIpAddress() + ":"
            + intToString(newClient->getPort()) + "] with socket [" + intToString(newClient->getSocket()) +
            "] on socket server [" + intToString(newClient->getServer()->getSocket()) + "]");

            addSocket(newClient->getSocket(), newClient->getEvents());
            _config._mapFdSocket[newClient->getSocket()] = newClient;
        }catch (std::exception & e){
            _config._accessLog.failure();
            _config._errorLog.writeLogFile(e.what());
        }
        _config._accessLog.removeIndent();
        _config._accessLog.writeLogFile("}");
        _config._accessLog.writeLogFile("Connexion available [" + intToString(_config._workerConnections) + "]");
    }
}

void Epoll::removeConnexionServer(Socket* server) {

    _config._accessLog.writeLogFile("Remove client {");
    _config._accessLog.addIndent();
    _config._accessLog.writeLogFile("Address ["  + server->getIpAddress() + ":"
    + intToString(server->getPort()) + "] with socket [" + intToString(server->getSocket()) +
    "] on socket server [" + intToString(dynamic_cast<Client*>(server)->getServer()) + "]");

    removeSocket(server->getSocket());
    int socket = server->getSocket();
    delete server;
    _config._mapFdSocket.erase(socket);

    _config._accessLog.removeIndent();
    _config._accessLog.writeLogFile("}");
    _config._accessLog.writeLogFile("Connexion available [" + intToString(_config._workerConnections) + "]");

}

void Epoll::checkConnexion(){
    std::time_t currentTime = std::time(NULL);
    currentTime -= 10;
    for (std::map<int, Socket*>::iterator itSock = _config._mapFdSocket.begin();
    itSock != _config._mapFdSocket.end(); ++itSock) {
        if (!dynamic_cast<Client*>(itSock->second)->isConnection() || currentTime > dynamic_cast<Client*>(itSock->second)->getLastConnection())
            removeConnexionServer(itSock->second);
    }
}

void Epoll::selectEvent(Client *client, int numberTrigged) {
    if (((_events[numberTrigged].events & EPOLLERR)) ||((_events[numberTrigged].events & EPOLLHUP))
        || ((_events[numberTrigged].events & EPOLLRDHUP))) {
        removeConnexionServer(client);
        return;
    }

    try {

        int events = client->getEvents();
        if (_events[numberTrigged].events & EPOLLIN) {

            _config._accessLog.writeLogFile("Recv data {");
            _config._accessLog.addIndent();
            _config._accessLog.writeLogFile("Address [" + client->getIpAddress() + ":"
            + intToString(client->getPort()) + "] with socket [" + intToString(client->getSocket()) +
              "] on socket server [" + intToString(client->getServer()) + "]");

            client->recvEvent();

            _config._accessLog.removeIndent();
            _config._accessLog.writeLogFile("}");

        }
        if (_events[numberTrigged].events & EPOLLOUT) {

            _config._accessLog.writeLogFile("send data {");
            _config._accessLog.addIndent();
            _config._accessLog.writeLogFile("Address [" + client->getIpAddress() + ":"
            + intToString(client->getPort()) + "] with socket [" + intToString(client->getSocket()) +
            "] on socket server [" + intToString(client->getServer()) + "]");

            client->sendEvent();

            _config._accessLog.removeIndent();
            _config._accessLog.writeLogFile("}");

        }
        if (client->getEvents() != events)
            modSocket(_events[numberTrigged].data.fd, client->getEvents());
        client->setLastConnection(std::time(NULL));
    }catch (std::exception & e){
        if (dynamic_cast<Exception&>(e).getCode() >= 0)
            client->setConnection(false);
        _config._accessLog.failure();
        _config._errorLog.writeLogFile(e.what());
    }
    if (!client->isConnection())
        removeConnexionServer(client);
}
