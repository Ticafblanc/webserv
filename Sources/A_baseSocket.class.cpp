/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbaseSocket.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/A_baseSocket.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

AbaseSocket::AbaseSocket()
: epoll_event(), sockaddr_in(), _socket(), _ipAddress(), _port(), _blocServer(*(new blocServer)) {}

AbaseSocket::AbaseSocket(blocServer& blocServer, std::string & ipAddr, int & port)
: epoll_event(), sockaddr_in(), _socket(), _ipAddress(ipAddr), _port(port), _blocServer(blocServer){
    buildSocket();
}

AbaseSocket::AbaseSocket(blocServer& blocServer, epoll_event & event, sockaddr_in & sockaddr)
: epoll_event(event), sockaddr_in(sockaddr), _socket(), _port(), _blocServer(blocServer){}

AbaseSocket::~AbaseSocket() {
    delete &_blocServer;
    closeSocket();
}

AbaseSocket::AbaseSocket(const AbaseSocket &other, blocServer &blocServer)
        : epoll_event(other), sockaddr_in(other), _socket(), _port(), _blocServer(blocServer) {}

AbaseSocket& AbaseSocket::operator=(const AbaseSocket& rhs){
    if (this != &rhs) {
        epoll_event::operator=(rhs);
        sockaddr_in::operator=(rhs);
        delete &this->_blocServer;
        this->_blocServer = rhs._blocServer;
    }
    return *this;
}



/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

AbaseSocket::socketException::socketException(const char * message)
: _message(message){}

AbaseSocket::socketException::~socketException() throw() {}

const char * AbaseSocket::socketException::what() const throw() { return _message.c_str(); }

AbaseSocket::socketException::socketException(const AbaseSocket::socketException & other)
: _message(other._message) {}

AbaseSocket::socketException &AbaseSocket::socketException::operator=(const AbaseSocket::socketException &rhs) {
    this->_message = rhs._message;
    return *this;
}


/*
*====================================================================================
*|                               public method                                      |
*====================================================================================
*/


void AbaseSocket::setSockaddrIn() {
    memset(&sin_zero, 0, sizeof(sin_zero));
    sin_family = AF_INET;
    sin_addr.s_addr = inet_addr(_ipAddress.c_str());
    sin_port = htons(_port);
}

__attribute__((unused)) void AbaseSocket::setSocket() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);/*IPPROTO_TCP*/
    if (_socket == 0)
        throw socketException(strerror(errno));
}

void AbaseSocket::setSocketOption() {
    int optionVal = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR,
                   &optionVal, (socklen_t)sizeof(optionVal))){
        close(_socket);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::setBind() {
    if (bind(_socket, reinterpret_cast<struct sockaddr *>(this), sizeof(*this)) < 0){
        close(_socket);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::setListen(int backlog) const {
    if (listen(_socket, backlog) < 0){
        close(_socket);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::accessorSocketFlag(int command, int flag) const {
    if (fcntl(_socket, command, flag ) < 0){
        close(_socket);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::setEpollEvent(int flag){
    data.fd = _socket;
    events = flag;
}

int AbaseSocket::getSocket() const {
    return _socket;
}

void AbaseSocket::buildSocket() {
    setSockaddrIn();
    setSocket();
    setSocketOption();
    setBind();
    setListen(5);
    accessorSocketFlag(F_SETFD, O_NONBLOCK);
    setEpollEvent(EPOLLIN);
}

void AbaseSocket::closeSocket() const {
    close(_socket);
}
