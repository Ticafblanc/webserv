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
//        close (_epollInstanceFd);
        throw epollException(strerror(errno));
    }

}

bool Epoll::EpollWait(int timeOut) {
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config.workerConnections, timeOut);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    return (_numberTriggeredEvents > 0);
}

bool Epoll::EpollWait() {
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _config.workerConnections, -1);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    return (_numberTriggeredEvents > 0);
}

void Epoll::addSocket(int socket){
    setEpollEvent(socket, EPOLLIN);
    setEpollCtl(EPOLL_CTL_ADD) ;
}

void Epoll::removeSocket(int socket){
    setEpollEvent(socket, EPOLLIN);
    setEpollCtl(EPOLL_CTL_DEL) ;
}

void Epoll::launchEpoll(){
    createEpollInstance(_config.mapFdSocket.size());
    for (std::map<int, Socket>::iterator it = _config.mapFdSocket.begin();
         it != _config.mapFdSocket.end(); ++it) {
        addSocket(it->first);
    }
}

void Epoll::manageEvent() {
    for (int i = 0; i < _numberTriggeredEvents; ++i) {
        if ((!(_events[i].events & EPOLLERR)) ||(!(_events[i].events & EPOLLHUP)) || (_events[i].events & EPOLLIN)) {
            std::map<int, Socket>::iterator it = _config.mapFdSocket.find(_events[i].data.fd);
            if (it != _config.mapFdSocket.end()) {
                try {
                    Socket newClient(_events[i]);
                    HttpMessage message(*it, newClient, _config)
                } catch (std::exception &e) {
                    _config.errorLog.writeLogFile(e.what());
                    std::cerr << e.what() << std::endl;
                }
            }
        } else{
            _config.errorLog.writeLogFile(intToString(_events[i].data.fd));
            close(_events[i].data.fd);
        }

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