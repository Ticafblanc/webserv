//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpBodyReponse.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpBodyReponse::HttpBodyReponse(const AHttpMessage& base)
: AHttpMessage(base), _buffer(_config._clientMaxBodySize), _totalBytesRecv(){
    _body.clear();
    if (_statusCode < 300 && _statusCode >= 200)
        _methodeToRecv = &HttpBodyReponse::recvBody;
    else if (_statusCode >= 400)
        _methodeToRecv = &HttpBodyReponse::setDefaultPage;
}

HttpBodyReponse::HttpBodyReponse(const AHttpMessage& base, int statusCode)
        : AHttpMessage(base), _buffer(_config._clientMaxBodySize), _totalBytesRecv(){
    _body.clear();
    if (_statusCode < 300 && _statusCode >= 200)
        _methodeToRecv = &HttpBodyReponse::recvBody;
    else if (_statusCode >= 400)
        _methodeToRecv = &HttpBodyReponse::setDefaultPage;
}

HttpBodyReponse::~HttpBodyReponse() {}

HttpBodyReponse::HttpBodyReponse(const HttpBodyReponse & other)
        : AHttpMessage(other), _buffer(other._buffer), _totalBytesRecv(other._totalBytesRecv){}

HttpBodyReponse &HttpBodyReponse::operator=(const HttpBodyReponse &rhs) {
    if ( this != & rhs) {
        AHttpMessage::operator=(rhs);
        this->_buffer = rhs._buffer;
        this->_totalBytesRecv = rhs._totalBytesRecv;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode Override                         |
*====================================================================================
*/

bool HttpBodyReponse::continueManageEvent() {
    if ((_statusCode < 300 && _statusCode >= 200) || _statusCode >= 400) {
        try {
            close(_pipeFdOut[STDOUT_FILENO]);
            (this->*(_methodeToRecv))();
            _mapHttpHeaders["Content-Length:"] = intToString(_body.size());
            _methode = new HttpHeadersReponse(*this);
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
    return false;
}

/*
*====================================================================================
*|                                  Private Methode                                 |
*====================================================================================
*/

void HttpBodyReponse::recvBody(){
    if (_pid) {
        struct timespec delay = {5, 0};
        nanosleep(&delay, NULL);
        int status;
        waitpid(_pid, &status, WNOHANG);
        if (status == 0)
            kill(_pid, SIGKILL);
        if (status <= 0 )
            throw Exception("CGI in GET fail", 500);
    }
    readData(_pipeFdOut[STDIN_FILENO], _buffer, *this,
             &HttpBodyReponse::readDataIsNotComplete);
    close(_pipeFdOut[STDIN_FILENO]);
}

void HttpBodyReponse::setDefaultPage(){
    std::stringstream ss;
    std::string path(_config._code.getStatusPage(_statusCode));
    std::ifstream htmlPage(path.c_str());
    if(htmlPage.is_open()) {
        ss << htmlPage.rdbuf();
        _mapHttpHeaders["Content-Type:"] = _config._mapMimeType.at(path.substr(path.find_last_of('.')));
    }
    else {
        ss << "<!DOCTYPE html><html><head><title>" +
                     _config._code.getStatusCode(_statusCode) + "</title></head><body><h1>" +
                     _config._code.getStatusCode(_statusCode) + "</h1><p>Sorry</p></body></html>";
        _mapHttpHeaders["Content-Type:"] = "text/html";
    }
//    _body = ss.str();
}

bool HttpBodyReponse::readDataIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytes(bytesExchange)) {
        return false;
    }
//    std::size_t size = std::min(bytesExchange, _buffer.size());
//    _body.append(_buffer.begin(), _buffer.begin() + size);
    _buffer.clear();
    return true;
}

bool HttpBodyReponse::checkErrorBytes(std::size_t& bytesExchange){
    if (static_cast<int>(bytesExchange) == -1)
        throw Exception("link with child fail", 500);
    if (bytesExchange == 0 )
        return true;
    _totalBytesRecv += bytesExchange;
    if (static_cast<int>(_totalBytesRecv) > _config._clientMaxBodySize)
        throw Exception("Reponse Max body size exceeds the maximum limit", 413);
    return false;
}







