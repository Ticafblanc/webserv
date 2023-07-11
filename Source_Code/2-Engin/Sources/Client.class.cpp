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
: Socket(event, server), _config(config),
  _lastConnection(std::time(NULL)), _message(NULL){}

Client::~Client() {
    delete _message;
}

Client::Client(const Client &other)
: Socket(other), _config(other._config),
  _lastConnection(other._lastConnection), _message(other._message){}

Client& Client::operator=(const Client& rhs){
    if (this != &rhs){
        Socket::operator=(rhs);
        this->_lastConnection = rhs._lastConnection;
        this->_message = rhs._message;
    }
    return *this;
}

bool Client::operator==(const Client & rhs) {
    return Socket::operator==(rhs);
}

/*
*====================================================================================
*|                               public method                                      |
*====================================================================================
*/

void Client::recvEvent() {
    if (dynamic_cast<HttpReponse*>(_message) != NULL)
        return;
    do {
        selectRequestMessageMethode();
    }while (_message->continueManageEvent() && !_message->isComplete());
    updateClient();
}

void Client::sendEvent() {
    if (!_message || dynamic_cast<HttpReponse*>(_message) == NULL)
        return;
    while (_message->continueManageEvent());
    updateClient();
}

/*
*====================================================================================
*|                                    Accessor                                      |
*====================================================================================
*/


time_t Client::getLastConnection() const {
    return _lastConnection;
}

void Client::setLastConnection(time_t lastConnection) {
    _lastConnection = lastConnection;
}

uint32_t Client::getEvents() const {
    return _message->eventsStatus();
}

bool Client::isConnection() const {
    return _message->connectionStatus();
}

/*
*====================================================================================
*|                                    Private Methode                               |
*====================================================================================
*/

void Client::selectRequestMessageMethode() {
    if (!_message ) {
        _message = new HttpHeadersRequest(_config, *this);
    }else
        _message->updateClassMessage(_message);
}

void Client::updateClient() {
    if (_message->isComplete()){
        delete _message;
        _message = NULL;
    }
    setLastConnection(std::time(NULL));
}
