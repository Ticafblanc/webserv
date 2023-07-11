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
: AHttpMessage(base), _buffer(_config._clientBodyBufferSize), _totalBytesRecv(){
    _data.clear();
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
            close(_pipeFdIn[STDOUT_FILENO]);
            (this->*(_methodeToRecv))();
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
    _methode = new HttpHeaderReponse(*this);
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
    std::ostringstream oss;
    std::string path(_config._code.getStatusPage(_statusCode));
    if (!setFile(path, oss)) {
        if (oss.str().empty()) {
            oss.str() = "<!DOCTYPE html><html><head><title>" +
                         _config._code.getStatusCode(_statusCode) + "</title></head><body><h1>" +
                         _config._code.getStatusCode(_statusCode) + "</h1><p>Sorry</p></body></html>";
        }
        _mapHttpHeaders["Content-Length:"] = "text/html";
    }else {
        _mapHttpHeaders["Content-Length:"] = _config._mapMimeType.at(path.substr(path.find_last_of('.')));
    }
    _data = oss.str();
}
bool HttpBodyReponse::readDataIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytes(bytesExchange))
        return false;
    _data.append(_buffer.begin(), _buffer.end());
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
}







