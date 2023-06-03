//
// Created by Matthis DoQuocBao on 2023-06-02.
//

#include "Include/baseEpoll.class.hpp"


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

baseEpoll::baseEpoll() : _epollInstanceFd(), _maxEvents(10), _events(new epoll_event[_maxEvents]), _numberTriggeredEvents() {}

baseEpoll::baseEpoll(std::vector<serverSocket> &sock, int maxEvents)
: _epollInstanceFd(), _maxEvents(maxEvents), _events(new epoll_event[_maxEvents]), _numberTriggeredEvents() {
    createEpollInstance(static_cast<int>(sock.size()));
    for (std::vector<serverSocket>::iterator it = sock.begin();
    it != sock.end() ; ++it) {
        setEpollCtl(EPOLL_CTL_ADD, *it) ;
    }

}

baseEpoll::~baseEpoll() {
    delete[] _events;
}

baseEpoll::baseEpoll(const baseEpoll &other)
: _epollInstanceFd(other._epollInstanceFd), _maxEvents(other._maxEvents), _events(other._events), _numberTriggeredEvents(other._numberTriggeredEvents) {


}

baseEpoll &baseEpoll::operator=(const baseEpoll &rhs) {
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

baseEpoll::epollException::epollException(const char * message)
        : _message(message){}

baseEpoll::epollException::~epollException() throw() {}

const char * baseEpoll::epollException::what() const throw() { return _message.c_str(); }

baseEpoll::epollException::epollException(const baseEpoll::epollException & other)
        : _message(other._message) {}

baseEpoll::epollException &baseEpoll::epollException::operator=(const baseEpoll::epollException &rhs) {
    this->_message = rhs._message;
    return *this;
}

/*
*====================================================================================
*|                               public method                                      |
*====================================================================================
*/

void baseEpoll::createEpollInstance(int nbr) {
    _epollInstanceFd = epoll_create(nbr);
    if (_epollInstanceFd == -1)
        throw epollException(strerror(errno));
}

void baseEpoll::setEpollCtl(int  option, AbaseSocket & sock) const {
    if (epoll_ctl(_epollInstanceFd, option, sock.getSocket(), &sock) == -1){
        close (_epollInstanceFd);
        throw epollException(strerror(errno));
    }
}

bool baseEpoll::EpollWait(int timeOut) {
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _maxEvents, timeOut);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    return (_numberTriggeredEvents > 0);
}

bool baseEpoll::EpollWait() {
    _numberTriggeredEvents = epoll_wait(_epollInstanceFd, _events, _maxEvents, -1);
    if ( _numberTriggeredEvents == -1)
        throw epollException(strerror(errno));
    return (_numberTriggeredEvents > 0);
}

epoll_event *baseEpoll::getEvents() const {
    return _events;
}

int baseEpoll::getNumberTriggeredEvents() const {
    return _numberTriggeredEvents;
}



