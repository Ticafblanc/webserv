//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpReponse.class.hpp>

/*
*====================================================================================
*|                                       HeaderReponse                              |
*====================================================================================
*/

HeaderReponse::HeaderReponse(SocketClient & client, Config& config)
        : _client(client), _config(config), _startLineVersion("HTTP/1.1"), _startLineStatusCode(), _mapHttpHeaders() {}

HeaderReponse::HeaderReponse(const HeaderReponse & other)
        : _client(other._client), _config(other._config), _startLineVersion(other._startLineVersion), _startLineStatusCode(other._startLineStatusCode),
          _mapHttpHeaders(other._mapHttpHeaders) {}

HeaderReponse &HeaderReponse::operator=(const HeaderReponse & rhs) {
    this->_client = rhs._client;
    this->_startLineVersion = rhs._startLineVersion;
    this->_startLineStatusCode = rhs._startLineStatusCode;
    this->_mapHttpHeaders = rhs._mapHttpHeaders;
    return *this;
}

void HeaderReponse::buildHeader() {
    addStatusCode();
    addDate();
    addHttpHeaders("Server.class:", "webserv/1.0 (ubuntu)");
    addContentInfo();
    addConnectionClose();
}

void HeaderReponse::buildHeaderStatus() {
    addStatusCode();
    addDate();
    addHttpHeaders("Server.class:", "webserv/1.0 (ubuntu)");
    addHttpHeaders("Content-Type:", _client._contentType);
    addHttpHeaders("Content-Length:", intToString(_client._content.size()));
    addConnectionClose();
}

void HeaderReponse::addStatusCode() {
    _startLineStatusCode = _config._code.getStatusCode();
}

void HeaderReponse::addHttpHeaders(const std::string& token, const std::string& value) {
    _mapHttpHeaders[token] = value;
}

void HeaderReponse::addDate() {
    std::time_t now = std::time(0);
    std::tm* timeInfo = std::gmtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
    addHttpHeaders("Code.class:", buffer);
}

void HeaderReponse::addContentInfo() {
    if (!_client._content.empty()) {
        addHttpHeaders("Content-Type:", _client._contentType);
        addHttpHeaders("Content-Length:", intToString(_client._content.size()));
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


HttpReponse::HttpReponse(Socket& client, Config& config)
        : _client(client),  _config(config), _bytesSend(), _buffer(),
        _headReponse(client.getclient(), _config){}

HttpReponse::~HttpReponse() {}

HttpReponse::HttpReponse(const HttpReponse & other)
        : _client(other._client), _config(other._config), _bytesSend(other._bytesSend),
        _buffer(other._buffer), _headReponse(other._headReponse) {}

HttpReponse &HttpReponse::operator=(const HttpReponse &rhs) {
    this->_client = rhs._client;
    this->_config = rhs._config;
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

void HttpReponse::sendStatusPage() {

}

void HttpReponse::sendMessage() {
//    std::cout << "send" << std::endl;
    _headReponse.buildHeader();
    chunckMessage();
    for(std::vector<std::string>::iterator it = _buffer.begin();
    it != _buffer.end(); ++it){
        sendData(*it);
    }
}

bool HttpReponse::messageIsNotComplete() {
    return _bytesSend < (ssize_t) _client.getclient()._content.size();
}


void HttpReponse::checkBytesSend() {
    if (_bytesSend == 0 )//close connection
        throw HttpReponse::httpReponseException("send close connection");
    if (_bytesSend == -1)//bad request
        throw HttpReponse::httpReponseException("send bad request");
    if (_bytesSend > 1024)//check headrs befor throw
        throw HttpReponse::httpReponseException("send size error");
}

void HttpReponse::chunckMessage() {
    std::string buffer = _headReponse.getHeaderReponse() + _client.getclient()._content;
    size_t Pos = 0;

    while (Pos < buffer.size()) {
        _buffer.push_back(buffer.substr(Pos, 1024));
        Pos += 1024;
    }
}

void HttpReponse::sendData(const std::string& message){
    _bytesSend = send(_client.getSocket(), message.data(), 1024, 0);
    checkBytesSend();
//    std::cout << " client  >> " << _client.getSocket() << " send >>> \n" << message <<  "\n"<<std::endl;
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
