/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-Client.Aclass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <Source_Code/2-Engin/Includes/Client.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

Client::Client(epoll_event &event, Config& config, Socket * server)
: Socket(event, server), _config(config), _connection(true), _events(EPOLLIN | EPOLLET),
_statusCode(0), _content(), _contentType(), _serverToken(), _lastConnection(std::time(NULL)), _request() {}

Client::~Client() {}

Client::Client(const Client &other)
: Socket(other), _config(other._config), _connection(other._connection), _events(other._events),
_statusCode(other._statusCode), _content(other._content), _contentType(other._contentType), _serverToken(other._serverToken),
_lastConnection(other._lastConnection), _request(other._request){}

Client& Client::operator=(const Client& rhs){
    if (this != &rhs){
        Socket::operator=(rhs);
        this->_connection = rhs._connection;
        this->_events = rhs._events;
        this->_statusCode = rhs._statusCode;
        this->_content = rhs._content;
        this->_contentType = rhs._contentType;
        this->_serverToken = rhs._serverToken;
        this->_request = rhs._request;
    }
    return *this;
}

bool Client::operator==(const Client & rhs) {
    if (this->_serverToken == rhs._serverToken && Socket::operator==(rhs))
        return true;
    return false;
}

/*
*====================================================================================
*|                               public method                                      |
*====================================================================================
*/

void Client::findTokenServer() {
    std::string serverName = _request.getValueHeader("Host:");
    if (serverName.empty())
        throw Exception("No host in request", 400);
    else{
        Socket & server = _config._mapFdSocket.at(_server);
        _serverToken = server.findServerName(serverName);
        if (_serverToken.empty())
            throw Exception("server name not found", 404);
    }
}


/*
*====================================================================================
*|                               public method                                      |
*====================================================================================
*/

void Client::recvEvent() {
    _request.recvRequest();
    if (_request.isComplete()){

    }

}

void Client::sendEvent() {

}

/*
*====================================================================================
*|                                    Accessor                                      |
*====================================================================================
*/


bool Client::isConnection() const {
    return _connection;
}

//Socket& Client::getServer()  {
//    return _server;
//}

time_t Client::getLastConnection() const {
    return _lastConnection;
}

void Client::setConnection(bool connection) {
    _connection = connection;
}

void Client::setLastConnection(time_t lastConnection) {
    _lastConnection = lastConnection;
}

int Client::getStatusCode() const {
    return _statusCode;
}

void Client::setStatusCode(int statusCode) {
    _statusCode = statusCode;
}

int Client::getEvents() const {
    return _events;
}

void Client::setEvents(int events) {
    _events = events;
}


