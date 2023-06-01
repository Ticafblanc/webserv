/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/server.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

server::server(configWebserv& config) : _config(config), _epollInstance(), _numberTriggeredEvents(), _webservEvent(),
                                         _serverEvents(new struct epoll_event[config._blocHttp._numberMaxEvents]){}

server::~server() {
    delete[] _serverEvents;
}

server::server(const server& other) : _config(other._config), _epollInstance(other._epollInstance),
                                      _numberTriggeredEvents(other._numberTriggeredEvents),
                                      _webservEvent(other._webservEvent), _serverEvents(other._serverEvents){}
                                      
server& server::operator=(const server& rhs){
    this->_config = rhs._config;
    this->_epollInstance = rhs._epollInstance;
    this->_numberTriggeredEvents = rhs._numberTriggeredEvents;
    this->_webservEvent = rhs._webservEvent;
    this->_serverEvents = rhs._serverEvents;
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

server::serverException::serverException(const char * message, int statusCode)
: _message(message), _statusCode(statusCode) {}

server::serverException::~serverException() throw() {}

const char * server::serverException::what() const throw() { return _message.c_str(); }

server::serverException::serverException(const server::serverException & other) : _message(other._message) {}

server::serverException &server::serverException::operator=(const server::serverException &rhs) {
    this->_message = rhs._message;
    return *this;
}


/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

void server::launcher() {
    std::set<client>::iterator          itSetClient;

    setEpoll();
    while(true) {
        setEpollWait();
        for (int i = 0; i < _numberTriggeredEvents; ++i) {
            try {
                if(isNotNewClient(_serverEvents[i], itSetClient))
                    if (itSetClient.manageEvent())
                        disconnectClient(itSetClient);
            } catch (const std::exception &e) {
                writeLogFile(e.what(), "/webserv/config_content_server/for_var/log/log_error.txt");
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

void server::setEpoll(){
    createEpoll();
    for (std::vector<blocServer>::iterator server = _config._blocHttp._vectorBlocServer.begin();
    server != _config._blocHttp._vectorBlocServer.end(); ++server){
        for (std::vector<listenData>::iterator vecListen = server->_vectorListen.begin();
             vecListen != server->_vectorListen.end(); ++vecListen) {
            setEpollEvent(vecListen->_serverSocket, _webservEvent, EPOLLIN);
            setEpollCtl(EPOLL_CTL_ADD, vecListen->_serverSocket);
        }
    }
}

void server::createEpoll() {
    _epollInstance = epoll_create(1);
    if (_epollInstance == -1)
        throw serverException(strerror(errno), 200);
}

void server::setEpollEvent(int & server_socket, struct epoll_event & event, int events){
    event.data.fd = server_socket;
    event.events = events;
}

void server::setEpollCtl(int option, int serverSocket) {
    if(epoll_ctl(_epollInstance, option, serverSocket, &_webservEvent) == -1){
        serverException serverException(strerror(errno), 200);
        throw serverException;
    }
}

void server::setEpollWait() {
    _numberTriggeredEvents = epoll_wait(_epollInstance, _serverEvents, _config._blocHttp._numberMaxEvents, -1);//@todo manage limit connectiuon
    if (_numberTriggeredEvents == -1)
        throw server::serverException(strerror(errno), 200);
}



int server::accessorSocketFlag(int & serverSocket, int command, int flag){
    int returnFlag = fcntl(serverSocket, command, flag);
    if (returnFlag < 0)
        throw server::serverException(strerror(errno), 200);
    return returnFlag;
}

bool server::isServerSocketAlreadyConnected(epoll_event & event, std::set<client>::iterator & itSetClient){
    for (std::vector<blocServer>::iterator server = _config._blocHttp._vectorBlocServer.begin();
         server != _config._blocHttp._vectorBlocServer.end(); ++server) {
        for (std::vector<listenData>::iterator vec_listen = server->_vectorListen.begin();
             vec_listen != server->_vectorListen.end(); ++vec_listen) {
            if (vec_listen->_serverSocket == event.data.fd){
                return false;
            }
        }
    }
    itSetClient = _setClientConnected.find(event);
    if (itSetClient == _setClientConnected.end()){
        serverException serverException(strerror(errno), 404);
        throw serverException;
    }
    return true;
}


bool server::isNotNewClient(epoll_event & event, std::set<client>::iterator & itSetClient) {
    if(isServerSocketAlreadyConnected(event, itSetClient))
        return true;
    client newClient(event);
    sockaddr_in                                     clientAddress = {};
    socklen_t                                       addressLen = sizeof(clientAddress);
    //@todo update to client
    event.data.fd = accept(event.data.fd, reinterpret_cast<struct sockaddr *>(&clientAddress), &addressLen);
    if (event.data.fd == -1) {
        serverException serverException(strerror(errno), 503);
        throw serverException;
    }
    accessorSocketFlag(event.data.fd, F_SETFL, O_NONBLOCK);
    setEpollEvent(event.data.fd, _webservEvent, EPOLLIN | EPOLLET);
    setEpollCtl(EPOLL_CTL_ADD, event.data.fd);
    _setClientConnected.insert(newClient);
    _config._blocHttp._numberMaxEvents--;
    return false;
}

void server::disconnectClient(std::set<client>::iterator& itSetClient) {
    _config._blocHttp._numberMaxEvents++;
    setEpollCtl(EPOLL_CTL_DEL, client_socket);
    close(client_socket);
    _setClientConnected.erase(itSetClient);
}
