//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include "HttpReponse.class.hpp"
/*
*====================================================================================
*|                                       HeaderReponse                              |
*====================================================================================
*/

HeaderReponse::HeaderReponse(Execute & execute, Server& server)
        : _execute(execute), _server(server), _startLineVersion("HTTP/1.1"), _startLineStatusCode(), _mapHttpHeaders() {
    addStatusCode();
    addDate();
    addHttpHeaders("Server:", "webserv/1.0 (ubuntu)");
    addContentInfo();
    addConnectionClose();
}

HeaderReponse::HeaderReponse(const HeaderReponse & other)
        : _execute(other._execute), _server(other._server), _startLineVersion(other._startLineVersion), _startLineStatusCode(other._startLineStatusCode),
          _mapHttpHeaders(other._mapHttpHeaders) {}

HeaderReponse &HeaderReponse::operator=(const HeaderReponse & rhs) {
    this->_execute = rhs._execute;
    this->_server = rhs._server;
    this->_startLineVersion = rhs._startLineVersion;
    this->_startLineStatusCode = rhs._startLineStatusCode;
    this->_mapHttpHeaders = rhs._mapHttpHeaders;
    return *this;
}

void HeaderReponse::addStatusCode() {
    _startLineStatusCode = _server._config._Http._code.getStatusCode();
}

void HeaderReponse::addHttpHeaders(const std::string& token, const std::string& value) {
    _mapHttpHeaders[token] = value;
}

void HeaderReponse::addDate() {
    std::time_t now = std::time(0);
    std::tm* timeInfo = std::gmtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
    addHttpHeaders("Code:", buffer);
}

void HeaderReponse::addContentInfo() {
    if (!_execute.getReponse().empty()) {
        addHttpHeaders("Content-Type:", _execute.getContentType());
        addHttpHeaders("Content-Length:", intToString(_execute.getReponse().size()));
    }
}

void HeaderReponse::addConnectionClose() {
    addHttpHeaders("Connection:", "close");
}

const std::string &HeaderReponse::getHeaderReponse() {
    _startLineVersion += " ";
    _startLineVersion += _startLineStatusCode;
    _startLineVersion += "\r\n";
    for (std::map<std::string, std::string>::iterator  i = _mapHttpHeaders.begin();
         i != _mapHttpHeaders.end(); ++i) {
        _startLineVersion += i->first;
        _startLineVersion += " ";
        _startLineVersion += i->second;
        _startLineVersion += "\r\n";
    }
    _startLineVersion += "\r\n";
    return _startLineVersion;
}





HttpReponse::HttpReponse(Socket& socket, Execute & execute, Server& server)
        : _server(server), _socket(socket), _execute(execute), _bytesSend(), _buffer(), _headReponse(execute, server){
    chunckMessage();
    sendMessage();
}

HttpReponse::~HttpReponse() {}

HttpReponse::HttpReponse(const HttpReponse & other)
        : _server(other._server),_socket(other._socket), _execute(other._execute), _bytesSend(other._bytesSend), _buffer(other._buffer),
          _headReponse(other._headReponse) {}

HttpReponse &HttpReponse::operator=(const HttpReponse &rhs) {
    this->_server = rhs._server;
    this->_socket = rhs._socket;
    this->_execute = rhs._execute;
    this->_bytesSend = rhs._bytesSend;
    this->_buffer = rhs._buffer;
    this->_headReponse = rhs._headReponse;
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/



void HttpReponse::sendMessage() {
    for(std::vector<std::string>::iterator it = _buffer.begin();
    it != _buffer.end(); ++it){
        sendData(*it);
    }
}

bool HttpReponse::messageIsNotComplete() {
    return _bytesSend < (ssize_t) _execute.getReponse().size();
}


void HttpReponse::checkBytesSend() {
    if (_bytesSend == 0 )//close connection
        throw HttpReponse::httpReponseException(strerror(errno));
    if (_bytesSend == -1)//bad request
        throw HttpReponse::httpReponseException(strerror(errno));
    if (_bytesSend > 1024)//check headrs befor throw
        throw HttpReponse::httpReponseException(strerror(errno));
}

void HttpReponse::chunckMessage() {
    std::string buffer = _headReponse.getHeaderReponse() + _execute.getReponse();
    size_t Pos = 0;

    while (Pos < buffer.size()) {
        _buffer.push_back(buffer.substr(Pos, 1024));
        Pos += 1024;
    }
}

void HttpReponse::sendData(const std::string& message){
    _bytesSend += send(_socket.getSocket(), message.data(), 1024, 0);
    checkBytesSend();
    std::cout << " client  >> " << _socket.getSocket() << " send >>> \n" << message <<  "\n"<<std::endl;
}




/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

HttpReponse::httpReponseException::httpReponseException(const char * message) : _message(message) {}

HttpReponse::httpReponseException::~httpReponseException() throw() {}

const char * HttpReponse::httpReponseException::what() const throw() { return _message.c_str(); }

HttpReponse::httpReponseException::httpReponseException(const HttpReponse::httpReponseException & other) : _message(other._message) {}

HttpReponse::httpReponseException &HttpReponse::httpReponseException::operator=(const HttpReponse::httpReponseException &rhs) {
    this->_message = rhs._message;
    return *this;
}
