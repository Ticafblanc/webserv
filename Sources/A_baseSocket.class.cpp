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
: epoll_event(), sockaddr_in(), _ipAddress(), _port(), _blocServer(*(new blocServer)) {}

AbaseSocket::AbaseSocket(blocServer& blocServer, std::string & ipAddr, int & port)
: epoll_event(), sockaddr_in(), _ipAddress(ipAddr), _port(port), _blocServer(blocServer){
    buildServerSocket();
}

AbaseSocket::AbaseSocket(blocServer& blocServer, epoll_event & event)
: epoll_event(event), sockaddr_in(), _port(), _blocServer(blocServer){
    buildClientSocket();
}

AbaseSocket::~AbaseSocket() {
    delete &_blocServer;
    closeSocket();
}

AbaseSocket::AbaseSocket(const AbaseSocket &other)
        : epoll_event(other), sockaddr_in(other), _port(), _blocServer(other._blocServer) {}

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

void AbaseSocket::getSockaddrIn() {
    _ipAddress = inet_ntoa(sin_addr);
    _port = ntohs(sin_port);
}

void AbaseSocket::setSocket() {
    data.fd = socket(AF_INET, SOCK_STREAM, 0);/*IPPROTO_TCP*/
    if (data.fd == 0)
        throw socketException(strerror(errno));
}

void AbaseSocket::setSocketOption() {
    int optionVal = 1;
    if (setsockopt(data.fd, SOL_SOCKET, SO_REUSEADDR,
                   &optionVal, (socklen_t)sizeof(optionVal))){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::setBind() {
    if (bind(data.fd, reinterpret_cast<struct sockaddr *>(this), sizeof(*this)) < 0){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::setListen(int backlog) const {
    if (listen(data.fd, backlog) < 0){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::accessorSocketFlag(int command, int flag) const {
    if (fcntl(data.fd, command, flag ) < 0){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void AbaseSocket::acceptConnection() {
    socklen_t  addressLen = sizeof(*this);
    int fd = accept(data.fd, reinterpret_cast<struct sockaddr *>(this), &addressLen);
    if (fd == -1) {
        closeSocket();
        throw socketException(strerror(errno));
    }
    data.fd = fd;
}

void AbaseSocket::setEpollEvent(int flag){
    data.fd = data.fd;
    events = flag;
}

int AbaseSocket::getSocket() const {
    return data.fd; 
}

void AbaseSocket::buildServerSocket() {
    setSockaddrIn();
    setSocket();
    setSocketOption();
    setBind();
    setListen(5);
    accessorSocketFlag(F_SETFD, O_NONBLOCK);
    setEpollEvent(EPOLLIN);
}

void AbaseSocket::buildClientSocket() {
    acceptConnection();
    getSockaddrIn();
    accessorSocketFlag(F_SETFL, O_NONBLOCK);
    setEpollEvent(EPOLLIN | EPOLLET);
    _blocServer.setEpollCtl(EPOLL_CTL_ADD, *this);
    _blocServer._config._mapFdSocket.insert(data.fd, *this);
    _blocServer._maxEvents--;
}

void AbaseSocket::closeSocket() const {
    _blocServer._maxEvents++;
    _blocServer.setEpollCtl(EPOLL_CTL_DEL, *this);
    _blocServer._config._mapFdSocket.erase(data.fd);
    close(data.fd);
}




