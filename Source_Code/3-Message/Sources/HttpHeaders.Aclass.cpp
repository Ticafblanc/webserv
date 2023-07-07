//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpHeaders.Aclass.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

AHttpHeaders::AHttpHeaders(Config& config, Socket& socketClient)
        : _config(config), _socketClient(socketClient), _connection(KEEP_ALIVE),
        _events(EPOLLIN | EPOLLET), _requestHeadersIsComplete(false), _requestBodyIsComplete(true),
        _bodyReponseIsComplete(true), _headersReponseIsComplete(false), _isComplete(false), _mapHttpHeaders(){}

AHttpHeaders::~AHttpHeaders() {}

AHttpHeaders::AHttpHeaders(const AHttpHeaders & other)
        : _config(other._config), _socketClient(other._socketClient), _connection(KEEP_ALIVE), _events(EPOLLIN | EPOLLET),
        _requestHeadersIsComplete(other._requestHeadersIsComplete), _requestBodyIsComplete(other._requestBodyIsComplete),
        _bodyReponseIsComplete(other._bodyReponseIsComplete), _headersReponseIsComplete(other._headersReponseIsComplete),
        _isComplete(other._isComplete), _mapHttpHeaders() {}

AHttpHeaders &AHttpHeaders::operator=(const AHttpHeaders &rhs) {
    if ( this != & rhs) {
        this->_config = rhs._config;
        this->_socketClient = rhs._socketClient;
        this->_connection = rhs._connection;
        this->_events = rhs._events;
        this->_requestHeadersIsComplete = rhs._requestHeadersIsComplete;
        this->_requestBodyIsComplete = rhs._requestBodyIsComplete;
        this->_bodyReponseIsComplete = rhs._bodyReponseIsComplete;
        this->_headersReponseIsComplete = rhs._headersReponseIsComplete;
        this->_isComplete = rhs._isComplete;
        this->_mapHttpHeaders = rhs._mapHttpHeaders;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Member Fonction Override                         |
*====================================================================================
*/

uint32_t AHttpHeaders::eventsStatus() {
    return _events;
}

bool AHttpHeaders::connectionStatus() {
    return _connection;
}

void AHttpHeaders::setConnection(bool connection) {
    _connection = connection;
}

void AHttpHeaders::setEvents(uint32_t events) {
    _events = events;
}


void AHttpHeaders::setConfig(Config &config) {
    _config = config;
}

void AHttpHeaders::addMapHttpHeaders(const std::pair<std::string, std::string> &pairHeader) {
    _mapHttpHeaders[pairHeader.first] = pairHeader.second;
}

bool AHttpHeaders::requestHeadersIsComplete() {
    return _requestHeadersIsComplete;
}

bool AHttpHeaders::requestBodyIsComplete() {
    return _requestBodyIsComplete;
}

bool AHttpHeaders::bodyReponseIsComplete() {
    return _bodyReponseIsComplete;
}

bool AHttpHeaders::headersReponseIsComplete() {
    return _headersReponseIsComplete;
}

bool AHttpHeaders::isComplete() {
    return _isComplete;
}

void AHttpHeaders::setStatusCode(int statusCode) {
    _statusCode = statusCode;
}

