//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

AHttpMessage::AHttpMessage(Config& config, Socket& socketClient)
        : _config(config), _socketClient(socketClient), _methode(NULL), _connection(KEEP_ALIVE),
        _events(EPOLLIN | EPOLLET),  _statusCode(0), _data(), _requestHeadersIsComplete(false), _requestBodyIsComplete(true),
        _bodyReponseIsComplete(true), _headersReponseIsComplete(false), _isComplete(false), _mapHttpHeaders(),
        _contentLength(), _isChunked(false), _contentType(), _pid(), _pipeFdIn(), _pipeFdOut() {}

AHttpMessage::~AHttpMessage() {}

AHttpMessage::AHttpMessage(const AHttpMessage & other)
        : _config(other._config), _socketClient(other._socketClient), _methode(other._methode), _connection(KEEP_ALIVE), _events(EPOLLIN | EPOLLET),
        _statusCode(other._statusCode), _data(other._data), _requestHeadersIsComplete(other._requestHeadersIsComplete),
        _requestBodyIsComplete(other._requestBodyIsComplete), _bodyReponseIsComplete(other._bodyReponseIsComplete),
        _headersReponseIsComplete(other._headersReponseIsComplete),_isComplete(other._isComplete), _mapHttpHeaders(),
        _contentLength(other._contentLength), _isChunked(other._isChunked), _contentType(other._contentType),
        _pid(other._pid), _pipeFdIn(), _pipeFdOut() {
    this->_pipeFdIn[0] = other._pipeFdIn[0];
    this->_pipeFdIn[1] = other._pipeFdIn[1];
    this->_pipeFdOut[0] = other._pipeFdOut[0];
    this->_pipeFdOut[1] = other._pipeFdOut[1];
}

AHttpMessage &AHttpMessage::operator=(const AHttpMessage &rhs) {
    if ( this != & rhs) {
        this->_config = rhs._config;
        this->_socketClient = rhs._socketClient;
        this->_methode = rhs._methode;
        this->_connection = rhs._connection;
        this->_events = rhs._events;
        this->_statusCode = rhs._statusCode;
        this->_data = rhs._data;
        this->_requestHeadersIsComplete = rhs._requestHeadersIsComplete;
        this->_requestBodyIsComplete = rhs._requestBodyIsComplete;
        this->_bodyReponseIsComplete = rhs._bodyReponseIsComplete;
        this->_headersReponseIsComplete = rhs._headersReponseIsComplete;
        this->_isComplete = rhs._isComplete;
        this->_startLineMethode = rhs._startLineMethode;
        this->_startLineURL = rhs._startLineURL;
        this->_startLineVersion = rhs._startLineVersion;
        this->_mapHttpHeaders = rhs._mapHttpHeaders;
        this->_contentLength = rhs._contentLength;
        this->_isChunked = rhs._isChunked;
        this->_contentType = rhs._contentType;
        this->_pipeFdIn[0] = rhs._pipeFdIn[0];
        this->_pipeFdIn[1] = rhs._pipeFdIn[1];
        this->_pipeFdOut[0] = rhs._pipeFdOut[0];
        this->_pipeFdOut[1] = rhs._pipeFdOut[1];

    }
    return *this;
}

/*
*====================================================================================
*|                                  Member Fonction Override                         |
*====================================================================================
*/

void AHttpMessage::updateClassMessage(IHttpMessage*& clientMethode){
    if (_methode == NULL)
        return ;
    std::swap(clientMethode, _methode);
    delete _methode;
    _methode = NULL;
}

uint32_t AHttpMessage::eventsStatus() {
    return _events;
}

bool AHttpMessage::connectionStatus() {
    return _connection;
}

void AHttpMessage::setConnection(bool connection) {
    _connection = connection;
}

void AHttpMessage::setEvents(uint32_t events) {
    _events = events;
}


void AHttpMessage::setConfig(Config &config) {
    _config = config;
}

bool AHttpMessage::requestHeadersIsComplete() {
    return _requestHeadersIsComplete;
}

bool AHttpMessage::requestBodyIsComplete() {
    return _requestBodyIsComplete;
}

bool AHttpMessage::bodyReponseIsComplete() {
    return _bodyReponseIsComplete;
}

bool AHttpMessage::headersReponseIsComplete() {
    return _headersReponseIsComplete;
}

bool AHttpMessage::isComplete() {
    return _isComplete;
}

void AHttpMessage::setStatusCode(int statusCode) {
    _statusCode = statusCode;
}

void AHttpMessage::addMapHttpHeaders(const std::pair<std::string, std::string> &pairHeader){
    _mapHttpHeaders.insert(pairHeader);
}

std::string AHttpMessage::getValueHeader(const std::string & token) {
    const std::map<std::string, std::string>::iterator it = _mapHttpHeaders.find(token);
    if (it != _mapHttpHeaders.end())
        return it->second;
    return std::string();
}

bool AHttpMessage::checkIsAllowedMethode(int allow, int dual1, int dual2) const{
    return(_config._allowMethods == 7 ||
           _config._allowMethods == allow ||
           _config._allowMethods == dual1 ||
           _config._allowMethods == dual2);
};