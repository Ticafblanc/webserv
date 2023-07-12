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
    if (_isChunked){
        chunkData();
    }
    setData(setHeader());
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
    return false;
}



bool HttpReponse::reponseIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytesExchange(bytesExchange))
        return false;
    std::pop_heap(_buffers.begin(), _buffers.begin());
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
    for (; _header.empty();) {
        std::vector<char> buffer;
        size = std::min(static_cast<std::size_t>(_config._clientHeaderBufferSize), _header.size());
        buffer.assign(_header.begin(), _header.begin() + size);
        _header = _header.substr(size);
        _buffers.push_back(buffer);
    }
    return size;
}

void HttpReponse::chunkData() {
    std::vector<char>& endHeader = _buffers.back();
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
    if (!_body.empty()){
        std::size_t newSize= std::min(_body.size(), static_cast<std::size_t>(_config._clientHeaderBufferSize));
        _buffers.back().insert(_buffers.back().begin() + headerSize + 1, _body.begin(), _body.begin() + newSize);
        _body = _body.substr(newSize);
        std::size_t size;
        for (; !_body.empty();) {
            std::vector<char> buffer;
            size = std::min(static_cast<std::size_t>(_config._clientBodyBufferSize), _body.size());
            buffer.assign(_body.begin(), _body.begin() + size);
            _body = _body.substr(size);
            _buffers.push_back(buffer);
        }
    }

}
