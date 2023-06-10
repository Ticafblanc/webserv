//
// Created by Matthis DoQuocBao on 2023-06-02.
//

#include "5-Epoll/Epoll.class.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

Epoll::Epoll(int maxEvents)
: epoll_event(), _token(), _mapFdSocket(), _epollInstanceFd(), _maxEvents(maxEvents),
_events(new epoll_event[_maxEvents]),_numberTriggeredEvents() {}

Epoll::~Epoll() {
//    delete[] _events;
}

Epoll::Epoll(const Epoll &other)
: epoll_event(other), _token(other._token), _mapFdSocket(), _epollInstanceFd(other._epollInstanceFd),
_maxEvents(other._maxEvents), _events(other._events), _numberTriggeredEvents(other._numberTriggeredEvents) {}

Epoll &Epoll::operator=(const Epoll &rhs) {
    if (this != &rhs) {
        epoll_event::operator=(rhs);
        this->_epollInstanceFd = rhs._epollInstanceFd;
        this->_maxEvents = rhs._maxEvents;
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
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _maxEvents, timeOut);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    return (_numberTriggeredEvents > 0);
}

bool Epoll::EpollWait() {
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _maxEvents, -1);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    return (_numberTriggeredEvents > 0);
}

epoll_event *Epoll::getEvents()  {
    return _events;
}

int Epoll::getNumberTriggeredEvents() const {
    return _numberTriggeredEvents;
}

void Epoll::addSocket(Socket & socket){
    setEpollEvent(socket.getSocket(), EPOLLIN);
    setEpollCtl(EPOLL_CTL_ADD) ;
}

void Epoll::removeSocket(Socket & socket){
    setEpollEvent(socket.getSocket(), EPOLLIN);
    setEpollCtl(EPOLL_CTL_DEL) ;
}

void Epoll::launchEpoll(){
    createEpollInstance(_mapFdSocket.size());
    for (std::map<int, Socket>::iterator it = _mapFdSocket.begin();
         it != _mapFdSocket.end(); ++it) {
        addSocket(it->second);
    }
}

void Epoll::addServer(Server &server) {
    for (std::vector<Listen>::iterator it = server.getVectorListen().begin();
            it != server.getVectorListen().end(); ++it) {
        std::pair<std::string, int> data = it->getDataListen();
        Socket sock(data.first, data.second);
        Socket& newSocket = sock;
        for(std::map<int, Socket>::iterator sockIt = _mapFdSocket.begin();
        sockIt != _mapFdSocket.end(); ++sockIt){
            if (sockIt->second == newSocket){
                newSocket = sockIt->second;
                break;
            }
        }
        newSocket.addServer(server);
        try {
            newSocket.buildServerSocket();
        }catch (std::exception & e){
            std::cerr << e.what()<<std::endl;
            continue;
        }
        _mapFdSocket.insert(std::make_pair(newSocket.getSocket(), newSocket));
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