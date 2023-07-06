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
: Socket(event, server), _config(config), _connection(KEEP_ALIVE), _events(EPOLLIN | EPOLLET),
_lastConnection(std::time(NULL)), _message(NULL) {}

Client::~Client() {
    if (_message) {
        delete _message;
    }
}

Client::Client(const Client &other)
: Socket(other), _config(other._config), _connection(other._connection), _events(other._events),
_lastConnection(other._lastConnection), _message() {}

Client& Client::operator=(const Client& rhs){
    if (this != &rhs){
        Socket::operator=(rhs);
        this->_connection = rhs._connection;
        this->_events = rhs._events;
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
    }while (_message->continueManageEvent());
    updateClient();
}

void Client::sendEvent() {
    if (dynamic_cast<HttpReponse*>(_message) == NULL)
        return;
    while (_message && _message->continueManageEvent());
    updateClient();
}

/*
*====================================================================================
*|                                    Accessor                                      |
*====================================================================================
*/


bool Client::isConnection() const {
    return _connection;
}


time_t Client::getLastConnection() const {
    return _lastConnection;
}

void Client::setLastConnection(time_t lastConnection) {
    _lastConnection = lastConnection;
}

uint32_t Client::getEvents() const {
    return _events;
}

void Client::setEvents(int events) {
    _events = events;
}

/*
*====================================================================================
*|                                    Private Methode                               |
*====================================================================================
*/

void Client::selectRequestMessageMethode() {
    if (!_message ) {
        _message = new HttpHeadersRequest(_config, *this);
    }else if (_message->requestHeadersIsComplete() && !_message->requestBodyIsComplete()
                && dynamic_cast<HttpBodyRequest*>(_message) == NULL) {
        IHttpMessage* tmp = new HttpBodyRequest(_message);
        std::swap(tmp, _message);
        delete tmp;
    }else if (_message->requestHeadersIsComplete() && _message->requestBodyIsComplete()
                && dynamic_cast<HttpBodyReponse*>(_message) == NULL) {
        IHttpMessage* tmp = new HttpBodyReponse(_message);
        std::swap(tmp, _message);
        delete tmp;
    }else if (_message->bodyReponseIsComplete() && !_message->headersReponseIsComplete()
                && dynamic_cast<HttpBodyReponse*>(_message) == NULL) {
        IHttpMessage* tmp = new HttpHeadersReponse(_message);
        std::swap(tmp, _message);
        delete tmp;
    }else if (_message->bodyReponseIsComplete() && _message->headersReponseIsComplete()
                && dynamic_cast<HttpReponse*>(_message) == NULL) {
        IHttpMessage* tmp = new HttpReponse(_message);
        std::swap(tmp, _message);
        delete tmp;
    }
}

void Client::updateClient() {
    _connection = _message->connectionStatus();
    _events = _message->eventsStatus();
    setLastConnection(std::time(NULL));
}
