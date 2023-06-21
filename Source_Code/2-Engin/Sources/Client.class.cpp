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

Client::Client(epoll_event &event, Config& config)
: Socket(event), _config(config), _server(event.data.fd), _connection(true), _statusCode(0),
  _content(), _contentType(), _serverToken(), _lastConnection(std::time(NULL)) {}

Client::~Client() {}

Client::Client(const Client &other)
: Socket(other), _config(other._config), _server(other._server), _connection(other._connection), _statusCode(other._statusCode), _content(other._content),
          _contentType(other._contentType), _serverToken(other._serverToken), _lastConnection(other._lastConnection){}

Client& Client::operator=(const Client& rhs){
    if (this != &rhs){
        this->_server = rhs._server;
        this->_connection = rhs._connection;
        this->_statusCode = rhs._statusCode;
        this->_content = rhs._content;
        this->_contentType = rhs._contentType;
        this->_serverToken = rhs._serverToken;
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

bool Client::isConnection() const {
    return _connection;
}

int Client::getServer() const {
    return _server;
}

time_t Client::getLastConnection() const {
    return _lastConnection;
}

void Client::setConnection(bool connection) {
    _connection = connection;
}

void Client::setLastConnection(time_t lastConnection) {
    _lastConnection = lastConnection;
}
