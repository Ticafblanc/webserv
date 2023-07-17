//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpReponse.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpReponse::HttpReponse(const AHttpMessage & base) : AHttpMessage(base) {
    _totalBytesSend = 0;
    if (_isChunked){
        chunkData();
    }
    setData(setHeader());
    setEvents(EPOLLOUT | EPOLLET);
}

HttpReponse::~HttpReponse() {}

HttpReponse::HttpReponse(const HttpReponse & other) : AHttpMessage(other), _buffers(other._buffers){}

HttpReponse &HttpReponse::operator=(const HttpReponse &rhs) {
    if ( this != & rhs) {
        AHttpMessage::operator=(rhs);
       this->_buffers = rhs._buffers;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode Override                         |
*====================================================================================
*/

bool HttpReponse::continueManageEvent() {
    try {
        sendData(_socketClient.getSocket(), _buffers, *this, &HttpReponse::reponseIsNotComplete);
        return false;
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



bool HttpReponse::reponseIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytesExchange(bytesExchange))
        return false;
    _buffers.erase(_buffers.begin(), _buffers.begin() + 1);
    if (_buffers.empty()){
        _isComplete = true;
        return false;
    }
    return true;
}

bool HttpReponse::checkErrorBytesExchange(std::size_t& bytesExchange){
    if (static_cast<int>(bytesExchange) == -1)
        return true;
    if (bytesExchange == 0 )
        throw Exception("recvMessage close connection", 0);
    _totalBytesSend += bytesExchange;
    if (static_cast<int>(_totalBytesSend) > _config._clientMaxBodySize)
        throw Exception("Request Max body size exceeds the maximum limit", 413);
    return false;
}

std::size_t  HttpReponse::setHeader() {
    std::size_t size;
    while (!_header.empty()) {
        std::vector<char> buffer;
        size = std::min(static_cast<std::size_t>(_config._clientHeaderBufferSize), _header.size());
        buffer.assign(_header.begin(), _header.begin() + size);
        _header = _header.substr(size);
        _buffers.push_back(buffer);
    }
    return (_config._clientHeaderBufferSize - size);
}

void HttpReponse::chunkData() {
    std::ostringstream oss;
    for (size_t i = 0; i < _body.size(); i += _config._clientBodyBufferSize) {
        size_t chunkSize = std::min(static_cast<std::size_t>(_config._clientBodyBufferSize), _body.size() - i);
        oss << std::hex << chunkSize << "\r\n";
        oss << _body.substr(i, chunkSize) << "\r\n";
    }
    oss << "0\r\n\r\n";
    _body = oss.str();
}

void HttpReponse::setData(std::size_t headerSize) {
    (void)headerSize;
    if (!_body.empty()){
//        std::size_t newSize= std::min(_body.size(), headerSize);
//        _buffers.back().insert(_buffers.back().end(), _body.begin(), _body.begin() + newSize);
//        _body = _body.substr(newSize);
        std::size_t size;
        while (!_body.empty()) {
            std::vector<char> buffer;
            size = std::min(static_cast<std::size_t>(_config._clientBodyBufferSize), _body.size());
            buffer.assign(_body.begin(), _body.begin() + size);
            _body = _body.substr(size);
            _buffers.push_back(buffer);
        }
    }
}
