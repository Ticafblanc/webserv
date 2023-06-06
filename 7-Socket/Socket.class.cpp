/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-Socket.Aclass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "7-Socket/Socket.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

Socket::Socket()
: epoll_event(), sockaddr_in(), _ipAddress(), _port(){}

Socket::Socket(std::string & ipAddr, int & port)
: epoll_event(), sockaddr_in(), _ipAddress(ipAddr), _port(port){
    buildServerSocket();
}

Socket::Socket(epoll_event & event)
: epoll_event(event), sockaddr_in(), _port(){
    buildClientSocket();
}

Socket::~Socket() {
//    closeSocket();
}

Socket::Socket(const Socket &other)
        : epoll_event(other), sockaddr_in(other), _ipAddress(other._ipAddress), _port(other._port){}

Socket& Socket::operator=(const Socket& rhs){
    if (this != &rhs) {
        epoll_event::operator=(rhs);
        sockaddr_in::operator=(rhs);
        this->_ipAddress = rhs._ipAddress;
        this->_port = rhs._port;
    }
    return *this;
}



/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

Socket::socketException::socketException(const char * message)
: _message(message){}

Socket::socketException::~socketException() throw() {}

const char * Socket::socketException::what() const throw() { return _message.c_str(); }

Socket::socketException::socketException(const Socket::socketException & other)
: _message(other._message) {}

Socket::socketException &Socket::socketException::operator=(const Socket::socketException &rhs) {
    this->_message = rhs._message;
    return *this;
}


/*
*====================================================================================
*|                               public method                                      |
*====================================================================================
*/


void Socket::setSockaddrIn() {
    memset(&sin_zero, 0, sizeof(sin_zero));
    sin_family = AF_INET;
    sin_addr.s_addr = inet_addr(_ipAddress.c_str());
    sin_port = htons(_port);
}

void Socket::getSockaddrIn() {
    _ipAddress = inet_ntoa(sin_addr);
    _port = ntohs(sin_port);
}

void Socket::setSocket() {
    data.fd = socket(AF_INET, SOCK_STREAM, 0);/*IPPROTO_TCP*/
    if (data.fd == 0)
        throw socketException(strerror(errno));
}

void Socket::setSocketOption() {
    int optionVal = 1;
    if (setsockopt(data.fd, SOL_SOCKET, SO_REUSEADDR,
                   &optionVal, (socklen_t)sizeof(optionVal))){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void Socket::setBind() {
    sockaddr_in sok;
    socklen_t  addressLen = sizeof(sok);
    memset(&sok.sin_zero, 0, sizeof(sok.sin_zero));
    sok.sin_family = sin_family;
    sok.sin_addr.s_addr = sin_addr.s_addr;
    sok.sin_port = sin_port;
    if (bind(data.fd, reinterpret_cast<struct sockaddr *>(&sok), addressLen) < 0){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void Socket::setListen(int backlog) const {
    if (listen(data.fd, backlog) < 0){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void Socket::accessorSocketFlag(int command, int flag) const {
    if (fcntl(data.fd, command, flag ) < 0){
        close(data.fd);
        throw socketException(strerror(errno));
    }
}

void Socket::acceptConnection() {
    socklen_t  addressLen = sizeof(*this);
    int fd = accept(data.fd, reinterpret_cast<struct sockaddr *>(this), &addressLen);
    if (fd == -1) {
        closeSocket();
        throw socketException(strerror(errno));
    }
    data.fd = fd;
}

void Socket::setEpollEvent(int flag){
    data.fd = data.fd;
    events = flag;
}

int Socket::getSocket() const {
    return data.fd; 
}

void Socket::buildServerSocket() {
    setSockaddrIn();
    setSocket();
    setSocketOption();
    setBind();
    setListen(5);
    accessorSocketFlag(F_SETFD, O_NONBLOCK);
    setEpollEvent(EPOLLIN);
}

void Socket::buildClientSocket() {
    acceptConnection();
    getSockaddrIn();
    accessorSocketFlag(F_SETFL, O_NONBLOCK);
    setEpollEvent(EPOLLIN | EPOLLET);
//    _blocServer.setEpollCtl(EPOLL_CTL_ADD, *this);
//    _blocServer._config._mapFdSocket.insert(data.fd, *this);
//    _blocServer._maxEvents--;
}

void Socket::closeSocket() const {
//    _blocServer._maxEvents++;
//    _blocServer.setEpollCtl(EPOLL_CTL_DEL, *this);
//    _blocServer._config._mapFdSocket.erase(data.fd);
    close(data.fd);
}




