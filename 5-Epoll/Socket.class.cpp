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

#include "Socket.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

Socket::Socket()
:  _ipAddress(), _port(), _sock(), _socket(0), _mapServerNameToken(),
  _client(0){}

Socket::Socket(const std::string & ipAddr, const int & port)
: _ipAddress(ipAddr), _port(port), _sock(), _socket(0), _mapServerNameToken(),
  _client(0){}

Socket::Socket(epoll_event & event)
: _ipAddress(), _port(), _sock(), _socket(event.data.fd), _mapServerNameToken(),
  _client(event.data.fd){
    buildClientSocket();
}

Socket::~Socket() {
//    std::cout   << "erase client socket = "<< _socket
//                <<" ip address = "<< _ipAddress
//                << " port = "  << _port<< std::endl;
//    closeSocket();
}

Socket::Socket(const Socket &other)
        : _ipAddress(other._ipAddress), _port(other._port),
          _sock(other._sock), _socket(other._socket), _mapServerNameToken(other._mapServerNameToken),
          _client(other._client){}

Socket& Socket::operator=(const Socket& rhs){
    if (this != &rhs) {
        this->_ipAddress = rhs._ipAddress;
        this->_port = rhs._port;
        this->_sock = rhs._sock;
        this->_socket = rhs._socket;
        this->_mapServerNameToken = rhs._mapServerNameToken;
        this->_client = rhs._client;
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
    if (_socket == 0) {
        setSockaddrIn();
        setSocket();
        setSocketOption();
        setBind();
        setListen(10);
        accessorSocketFlag(F_SETFL, O_NONBLOCK);
    }
}

void Socket::buildClientSocket() {
    acceptConnection();
    getSockaddrIn();
    accessorSocketFlag(F_SETFL, O_NONBLOCK);

//    _blocServer._peg._mapFdSocket.insert(data.fd, *this);
//    _blocServer._maxEvents--;
}

void Socket::closeSocket() const {
//    _blocServer._maxEvents++;
//    _blocServer.setEpollCtl(EPOLL_CTL_DEL, *this);
//    _blocServer._peg._mapFdSocket.erase(data.fd);
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

void Socket::addServerName( std::vector<std::string> & name, const std::string & token){
    for ( std::vector<std::string>::iterator it = name.begin();
          it != name.end(); ++it) {
        if (_mapServerNameToken.find(*it) == _mapServerNameToken.end())
            _mapServerNameToken[*it] = token;
    }
}

bool Socket::operator==(const Socket & rhs) {
    if ((this->_ipAddress == "0.0.0.0" && this->_port == rhs._port) ||
    (this->_ipAddress == rhs._ipAddress && this->_port == rhs._port))
        return true;
    return false;
}

std::string  Socket::findServerName(const string &serverName) {
    std::map<std::string, std::string>::iterator it = _mapServerNameToken.find(serverName);
    if (it != _mapServerNameToken.end())
        return it->second;
    return NULL;
}

SocketClient &Socket::getclient() {
    return _client;
}


SocketClient::SocketClient(int server)
        : _server(server), _connection(true), _content(), _contentType(), _serverToken() {}

SocketClient::~SocketClient() {}

SocketClient::SocketClient(const SocketClient &other) :
_server(other._server), _connection(other._connection), _content(other._content),
_contentType(other._contentType), _serverToken(other._serverToken){}

SocketClient &SocketClient::operator=(const SocketClient &rhs) {
    if (this != &rhs){
        this->_server = rhs._server;
        this->_connection = rhs._connection;
        this->_content = rhs._content;
        this->_contentType = rhs._contentType;
        this->_serverToken = rhs._serverToken;
    }
    return *this;
}
