//
// Created by Matthis DoQuocBao on 2023-06-02.
//

#include "5-Epoll/Epoll.class.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

Epoll::Epoll(Config& config)
: epoll_event(), _config(config), _epollInstanceFd(),
_events(new epoll_event[config.workerConnections]),_numberTriggeredEvents() {}

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
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config.workerConnections, timeOut);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    manageEvent();
    return (_numberTriggeredEvents > 0);
}

bool Epoll::EpollWait() {
//    std::cout << " Epoll Wait !!" << std::endl;
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config.workerConnections, -1);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    manageEvent();
    return (_numberTriggeredEvents > 0);
}

void Epoll::addSocket(int socket, int events){
    setEpollEvent(socket, events);
    setEpollCtl(EPOLL_CTL_ADD) ;
}

void Epoll::modSocket(int socket, int events){
    setEpollEvent(socket, events);
    setEpollCtl(EPOLL_CTL_MOD) ;
}

void Epoll::removeSocket(int socket){
    setEpollEvent(socket, 0);
    setEpollCtl(EPOLL_CTL_DEL);
    close(socket);
}

void Epoll::launchEpoll(){
    createEpollInstance(_config.mapFdServer.size());
    for (std::map<int, Socket>::iterator it = _config.mapFdServer.begin();
         it != _config.mapFdServer.end(); ++it) {
        addSocket(it->first, EPOLLIN);
    }
}

void Epoll::manageEvent() {
    std::map<int, Socket>::iterator it;
    for (int i = 0; i < _numberTriggeredEvents; ++i) {
//        std::cout << "event fd => " << _events[i].data.fd << " events" << _events[i].events  <<std::endl;
        it = _config.mapFdServer.find(_events[i].data.fd);
        if (it != _config.mapFdServer.end()) {
            addConnexion(i);
        }else {
            it = _config.mapFdClient.find(_events[i].data.fd);
            if (it != _config.mapFdServer.end()) {
                selectEvent(it->second, i);
            } else {
                close(_events[i].data.fd);
            }
        }
    }

}

void Epoll::addConnexion(int numberTrigged) {
    if ((!(_events[numberTrigged].events & EPOLLERR)) ||(!(_events[numberTrigged].events & EPOLLHUP))
    || (!(_events[numberTrigged].events & EPOLLRDHUP)) || (_events[numberTrigged].events & EPOLLIN)) {
        try {
            Socket newClient(_events[numberTrigged]);
            addSocket(newClient.getSocket(), EPOLLIN);
            _config.mapFdClient.insert(std::make_pair(newClient.getSocket(), newClient));
        } catch (std::exception &e) {
            _config.errorLog.writeLogFile(e.what());
            std::cerr << e.what() << std::endl;
        }
    } else {
        close(_events[numberTrigged].data.fd);
    }
}

void Epoll::removeConnexionClient(Socket &client) {
    removeSocket(client.getSocket());
    _config.mapFdClient.erase(client.getSocket());
}

void Epoll::removeConnexionServer(Socket &server) {
    removeSocket(server.getSocket());
    _config.mapFdServer.erase(server.getSocket());
}

void Epoll::selectEvent(Socket &client, int numberTrigged) {
    if ((!(_events[numberTrigged].events & EPOLLERR)) ||(!(_events[numberTrigged].events & EPOLLHUP))
        || (!(_events[numberTrigged].events & EPOLLRDHUP))) {
        try {
            if (_events[numberTrigged].events & EPOLLIN) {
                HttpMessage message(client, _config);
                if(!client.getclient()._content.empty())
                    modSocket(_events[numberTrigged].data.fd, EPOLLOUT);
            }
            if (_events[numberTrigged].events & EPOLLOUT) {
                HttpReponse reponse(client, _config);
                reponse.sendMessage();
                modSocket(_events[numberTrigged].data.fd, EPOLLIN);
                removeConnexionClient(client);
            }
        }catch (std::exception & e){
            _config.errorLog.writeLogFile(e.what());
            std::cerr << e.what() << std::endl;
        }
        if (!client.getclient()._connection){
            removeConnexionClient(client);
        }
    }
    else {
        removeConnexionClient(client);
    }
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