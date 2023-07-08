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
  _lastConnection(std::time(NULL)), _request(NULL), _reponse(NULL) {}

Client::~Client() {
    delete _request;
    delete _reponse;
}

Client::Client(const Client &other)
: Socket(other), _config(other._config),
  _lastConnection(other._lastConnection), _request(other._request), _reponse(other._reponse) {}

Client& Client::operator=(const Client& rhs){
    if (this != &rhs){
        Socket::operator=(rhs);
        this->_lastConnection = rhs._lastConnection;
        this->_request = rhs._request;
        this->_reponse = rhs._reponse;
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
    if (dynamic_cast<HttpReponse*>(_request) != NULL)
        return;
    do {
        selectRequestMessageMethode();
    }while (_request->continueManageEvent() && !_request->isComplete());
    updateClient();
}

void Client::sendEvent() {
    if (!_request || dynamic_cast<HttpReponse*>(_request) == NULL)
        return;
    while (_request->continueManageEvent());
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
    return _request->eventsStatus();
}

bool Client::isConnection() const {
    return _request->connectionStatus();
}

/*
*====================================================================================
*|                                    Private Methode                               |
*====================================================================================
*/

void Client::selectRequestMessageMethode() {
    if (!_request ) {
        _request = new HttpHeadersRequest(_config, *this);
    }else if (_request->requestHeadersIsComplete()) {
        _request->updateClassMessage(_request);
    }else if (_request->requestHeadersIsComplete() && _request->requestBodyIsComplete()
              && !_request->bodyReponseIsComplete() && dynamic_cast<HttpBodyReponse*>(_request) == NULL) {
        IHttpMessage* tmp = new HttpBodyReponse(_request);
        std::swap(tmp, _request);
        delete tmp;
    }else if (_request->bodyReponseIsComplete() && !_request->headersReponseIsComplete()
              && dynamic_cast<HttpBodyReponse*>(_request) == NULL) {
        IHttpMessage* tmp = new HttpHeadersReponse(_request);
        std::swap(tmp, _request);
        delete tmp;
    }else if (_request->bodyReponseIsComplete() && _request->headersReponseIsComplete()
              && dynamic_cast<HttpReponse*>(_request) == NULL) {
        IHttpMessage* tmp = new HttpReponse(_request);
        std::swap(tmp, _request);
        delete tmp;
    }
}

void Client::updateClient() {
    if (_request.isComplete()){
        delete _request;
        _request = NULL;
    }
    setLastConnection(std::time(NULL));
}
