//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpHeadersReponse.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpHeadersReponse::HttpHeadersReponse(const AHttpMessage& base) : AHttpMessage(base){
    _isChunked = false;
}

HttpHeadersReponse::HttpHeadersReponse(const AHttpMessage& base, std::string& cgiHeader) : AHttpMessage(base){
    _isChunked = false;
    updateMapHeaders(cgiHeader);
}

HttpHeadersReponse::~HttpHeadersReponse() {}

HttpHeadersReponse::HttpHeadersReponse(const HttpHeadersReponse & other) : AHttpMessage(other){}

HttpHeadersReponse &HttpHeadersReponse::operator=(const HttpHeadersReponse &rhs) {
    if ( this != & rhs) {
        AHttpMessage::operator=(rhs);
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode Override                         |
*====================================================================================
*/

bool HttpHeadersReponse::continueManageEvent() {
    if ((_statusCode < 300 && _statusCode >= 200) || _statusCode >= 400) {
        try {
            setHeaders();
            return true;
        } catch (Exception &e) {
            _config._accessLog.failure();
            _config._errorLog.writeMessageLogFile(e.what());
            setStatusCode(e.getCode());
            return true;
        } catch (std::exception &e) {
            _config._accessLog.failure();
            _config._errorLog.writeMessageLogFile(e.what());
            setStatusCode(400);
            return true;
        }
    }
    _methode = new HttpReponse(*this);
    return false;
}

/*
*====================================================================================
*|                                       Public Methode                             |
*====================================================================================
*/

void HttpHeadersReponse::updateMapHeaders(std::string& cgiHeader){
    std::stringstream ss(cgiHeader);
    std::string line;

    while (std::getline(ss, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 2);
            _mapHttpHeaders[key] = value;
        }
    }

}

void HttpHeadersReponse::startLine() {
    _header = _startLineVersion + " " + _config._code.getStatusCode(_statusCode) + "\r\n";
}

void HttpHeadersReponse::addDate() {
    if (_mapHttpHeaders.find("Date:") == _mapHttpHeaders.end()) {
        std::time_t now = std::time(0);
        std::tm *timeInfo = std::gmtime(&now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
        _header += "Date: " + std::string(buffer) + "\r\n";
    }
}

void HttpHeadersReponse::addServer() {
    if (_mapHttpHeaders.find("Server:") == _mapHttpHeaders.end())
        _mapHttpHeaders.erase("Server:");
    _header += "Server: webserv/1.0 (ubuntu)\r\n";
}

void HttpHeadersReponse::setHeaders(){
    startLine();
    addDate();
    addServer();
    if (getValueHeader("Transfer-Encoding:") == "chunked") {
        _mapHttpHeaders.erase("Content-Length:");
        _isChunked = true;
    }
    for (std::map<std::string, std::string>::iterator  i = _mapHttpHeaders.begin();
         i != _mapHttpHeaders.end(); ++i) {
        if (!i->second.empty())
            _header += i->first + " " + i->second + "\r\n";
    }
    _header += "\r\n";
}



