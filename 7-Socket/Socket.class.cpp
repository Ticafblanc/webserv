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
: _ipAddress(), _port(), _sock(), _socket(){}

Socket::Socket(std::string & ipAddr, int & port)
: _ipAddress(ipAddr), _port(port), _sock(), _socket(){
    buildServerSocket();
}

Socket::Socket(epoll_event & event)
: _port(), _sock(), _socket(event.data.fd){
    buildClientSocket();
}

Socket::~Socket() {
    std::cout   << "erase client socket = "<< _socket
                <<" ip address = "<< _ipAddress
                << " port = "  << _port<< std::endl;
//    closeSocket();
}

Socket::Socket(const Socket &other)
        : _ipAddress(other._ipAddress), _port(other._port),
          _sock(other._sock), _socket(other._socket){}

Socket& Socket::operator=(const Socket& rhs){
    if (this != &rhs) {
        this->_ipAddress = rhs._ipAddress;
        this->_port = rhs._port;
        this->_sock = rhs._sock;
        this->_socket = rhs._socket;
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
    memset(&_sock.sin_zero, 0, sizeof(_sock.sin_zero));
    _sock.sin_family = AF_INET;
    _sock.sin_addr.s_addr = inet_addr(_ipAddress.c_str());
    _sock.sin_port = htons(_port);
}

void Socket::getSockaddrIn() {
    _ipAddress = inet_ntoa(_sock.sin_addr);
    _port = ntohs(_sock.sin_port);
    std::cout   << "add client socket = "<< _socket
                <<" ip address = "<< _ipAddress
                << " port = "  << _port<< std::endl;
}

void Socket::setSocket() {
    _socket = socket(AF_INET, SOCK_STREAM, 0);/*IPPROTO_TCP*/
    if(_socket == 0)
        throw socketException(strerror(errno));
}

void Socket::setSocketOption() {
    int optionVal = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR,
                   &optionVal, (socklen_t)sizeof(optionVal))){
        close(_socket);
        throw socketException(strerror(errno));
    }
}

void Socket::setBind() {
    socklen_t  addressLen = sizeof(_sock);
    if (bind(_socket, reinterpret_cast<struct sockaddr *>(&_sock), addressLen) < 0){
        close(_socket);
        throw socketException(strerror(errno));
    }

}

void Socket::setListen(int backlog) const {
    if (listen(_socket, backlog) < 0){
        close(_socket);
        throw socketException(strerror(errno));
    }
}

void Socket::accessorSocketFlag(int command, int flag) const {
    if (fcntl(_socket, command, flag ) < 0){
        close(_socket);
        throw socketException(strerror(errno));
    }
}

void Socket::acceptConnection() {
    socklen_t  addressLen = sizeof(_sock);
    int fd = accept(_socket, reinterpret_cast<struct sockaddr *>(&_sock), &addressLen);
    if (fd == -1) {
        closeSocket();
        throw socketException(strerror(errno));
    }
    _socket = fd;
}

int Socket::getSocket() const {
    return _socket;
}

void Socket::buildServerSocket() {
    setSockaddrIn();
    setSocket();
    setSocketOption();
    setBind();
    setListen(10);
    accessorSocketFlag(F_SETFL, O_NONBLOCK);
}

void Socket::buildClientSocket() {
    acceptConnection();
    getSockaddrIn();
    accessorSocketFlag(F_SETFL, O_NONBLOCK);
//    setEpollEvent(EPOLLIN | EPOLLET);
//    _blocServer.setEpollCtl(EPOLL_CTL_ADD, *this);
//    _blocServer._config._mapFdSocket.insert(data.fd, *this);
//    _blocServer._maxEvents--;
}

void Socket::closeSocket() const {
//    _blocServer._maxEvents++;
//    _blocServer.setEpollCtl(EPOLL_CTL_DEL, *this);
//    _blocServer._config._mapFdSocket.erase(data.fd);
    close(_socket);
}


bool Socket::operator()(const Socket& socket) const {
    return socket._socket == this->_socket;
}

int Socket::getPort() const {
    return _port;
}

const string &Socket::getIpAddress() const {
    return _ipAddress;
}

