//
// Created by Matthis DoQuocBao on 2023-06-02.
//

#include "5-Epoll/Includes/Epoll.class.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

Epoll::Epoll() : _epollInstanceFd(), _maxEvents(10), _events(new epoll_event[_maxEvents]), _numberTriggeredEvents() {}

Epoll::Epoll(std::vector<serverSocket> &sock, int maxEvents)
: _epollInstanceFd(), _maxEvents(maxEvents), _events(new epoll_event[_maxEvents]), _numberTriggeredEvents() {
    createEpollInstance(static_cast<int>(sock.size()));
    for (std::vector<serverSocket>::iterator it = sock.begin();
    it != sock.end() ; ++it) {
        setEpollCtl(EPOLL_CTL_ADD, *it) ;
    }

}

Epoll::~Epoll() {
    delete[] _events;
}

Epoll::Epoll(const Epoll &other)
: _epollInstanceFd(other._epollInstanceFd), _maxEvents(other._maxEvents), _events(other._events), _numberTriggeredEvents(other._numberTriggeredEvents) {


}

Epoll &Epoll::operator=(const Epoll &rhs) {
    if (this != &rhs) {
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

void Epoll::createEpollInstance(int nbr) {
    _epollInstanceFd = epoll_create(nbr);
    if (_epollInstanceFd == -1)
        throw epollException(strerror(errno));
}

void Epoll::setEpollCtl(int  option, Socket & sock) const {
    if (epoll_ctl(_epollInstanceFd, option, sock.getSocket(), &sock) == -1){
        close (_epollInstanceFd);
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

epoll_event *Epoll::getEvents() const {
    return _events;
}

int Epoll::getNumberTriggeredEvents() const {
    return _numberTriggeredEvents;
}



