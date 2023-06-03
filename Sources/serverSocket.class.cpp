/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverSocket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/serverSocket.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

serverSocket::serverSocket(configWebserv& config) : _config(config), _epollInstance(), _numberTriggeredEvents(), _webservEvent(),
                                         _serverSocketEvents(new struct epoll_event[config._blocHttp._numberMaxEvents]){}

serverSocket::~serverSocket() {
    delete[] _serverSocketEvents;
}

serverSocket::serverSocket(const serverSocket& other) : _config(other._config), _epollInstance(other._epollInstance),
                                      _numberTriggeredEvents(other._numberTriggeredEvents),
                                      _webservEvent(other._webservEvent), _serverSocketEvents(other._serverSocketEvents){}
                                      
serverSocket& serverSocket::operator=(const serverSocket& rhs){
    this->_config = rhs._config;
    this->_epollInstance = rhs._epollInstance;
    this->_numberTriggeredEvents = rhs._numberTriggeredEvents;
    this->_webservEvent = rhs._webservEvent;
    this->_serverSocketEvents = rhs._serverSocketEvents;
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

serverSocket::serverSocketException::serverSocketException(const char * message, int statusCode)
: _message(message), _statusCode(statusCode) {}

serverSocket::serverSocketException::~serverSocketException() throw() {}

const char * serverSocket::serverSocketException::what() const throw() { return _message.c_str(); }

serverSocket::serverSocketException::serverSocketException(const serverSocket::serverSocketException & other) : _message(other._message) {}

serverSocket::serverSocketException &serverSocket::serverSocketException::operator=(const serverSocket::serverSocketException &rhs) {
    this->_message = rhs._message;
    return *this;
}


/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void serverSocket::launcher() {
    std::set<client>::iterator          itSetClient;

    setEpoll();
    while(true) {
        setEpollWait();
        for (int i = 0; i < _numberTriggeredEvents; ++i) {
            try {
                if(isNotNewClient(_serverSocketEvents[i], itSetClient))
                    if (itSetClient.manageEvent())
                        disconnectClient(itSetClient);
            } catch (const std::exception &e) {
                writeLogFile(e.what(), "/webserv/config_content_serverSocket/for_var/log/log_error.txt");
                std::cout << e.what() << std::endl;//@todo to delete
            }

        }
    }

}

/*
*====================================================================================
*|                                 private utils function to launch                 |
*====================================================================================
*/

bool serverSocket::isServerSocketAlreadyConnected(epoll_event & event, std::set<client>::iterator & itSetClient){
    for (std::vector<blocServer>::iterator serverSocket = _config._blocHttp._vectorBlocServer.begin();
         serverSocket != _config._blocHttp._vectorBlocServer.end(); ++serverSocket) {
        for (std::vector<listenData>::iterator vec_listen = serverSocket->_vectorListen.begin();
             vec_listen != serverSocket->_vectorListen.end(); ++vec_listen) {
            if (vec_listen->_serverSocketSocket == event.data.fd){
                return false;
            }
        }
    }
    itSetClient = _setClientConnected.find(event);
    if (itSetClient == _setClientConnected.end()){
        serverSocketException serverSocketException(strerror(errno), 404);
        throw serverSocketException;
    }
    return true;
}


bool serverSocket::isNotNewClient(epoll_event & event, std::set<client>::iterator & itSetClient) {
    if(isServerSocketAlreadyConnected(event, itSetClient))
        return true;
    client newClient(event);
    sockaddr_in                                     clientAddress = {};
    socklen_t                                       addressLen = sizeof(clientAddress);
    //@todo update to client
    event.data.fd = accept(event.data.fd, reinterpret_cast<struct sockaddr *>(&clientAddress), &addressLen);
    if (event.data.fd == -1) {
        serverSocketException serverSocketException(strerror(errno), 503);
        throw serverSocketException;
    }
    accessorSocketFlag(event.data.fd, F_SETFL, O_NONBLOCK);
    setEpollEvent(event.data.fd, _webservEvent, EPOLLIN | EPOLLET);
    setEpollCtl(EPOLL_CTL_ADD, event.data.fd);
    _setClientConnected.insert(newClient);
    _config._blocHttp._numberMaxEvents--;
    return false;
}

void serverSocket::disconnectClient(std::set<client>::iterator& itSetClient) {
    _config._blocHttp._numberMaxEvents++;
    setEpollCtl(EPOLL_CTL_DEL, client_socket);
    close(client_socket);
    _setClientConnected.erase(itSetClient);
}

void serverSocketSocket::manageEvent(epoll_event &event, webservSocket &sock) {

}
