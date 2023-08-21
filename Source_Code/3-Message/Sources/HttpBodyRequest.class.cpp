//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Includes/HttpBodyRequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpBodyRequest::HttpBodyRequest(const AHttpMessage& base, const std::string & data)
: AHttpMessage(base), _buffer(_config._clientBodyBufferSize), _totalBytesRecv(),
_methodeToRecv((_isChunked) ? &HttpBodyRequest::recvHeaderChunck : &HttpBodyRequest::recvBody){
    _body = data;
    _totalBytesRecv = _body.size();
    (this->*(_methodeToRecv))();
    if (!data.empty()){
        _buffer.assign(_body.begin(),
                       (_body.size() > static_cast<std::size_t>(_config._clientBodyBufferSize)) ?
                       _body.begin() + _config._clientBodyBufferSize : _body.end());
        if (_body.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
            _body = _body.substr(0, _config._clientBodyBufferSize);
        else
            _body.clear();
    }
}

HttpBodyRequest::~HttpBodyRequest() {}

HttpBodyRequest::HttpBodyRequest(const HttpBodyRequest & other)
: AHttpMessage(other), _buffer(other._buffer), _totalBytesRecv(other._totalBytesRecv),
_methodeToRecv(other._methodeToRecv){

}

HttpBodyRequest &HttpBodyRequest::operator=(const HttpBodyRequest &rhs) {
    if ( this != & rhs) {
       AHttpMessage::operator=(rhs);
       this->_buffer = rhs._buffer;
       this->_totalBytesRecv = rhs._totalBytesRecv;
       this->_methodeToRecv = rhs._methodeToRecv;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode                                  |
*====================================================================================
*/

bool HttpBodyRequest::continueManageEvent() {
    (this->*(_methodeToRecv))();
    if (_requestBodyIsComplete) {
        close(_pipeFdIn[STDOUT_FILENO]);
        _methode = new HttpBodyReponse(*this);
        return true;
    }
    return false;
}

/*
*====================================================================================
*|                                  Private Methode to recvMessage                         |
*====================================================================================
*/

void HttpBodyRequest::recvHeaderChunck(){
    std::size_t chunkSize;
    std::size_t bytesRecv;
    std::size_t posCRLF;

    while (!_requestBodyIsComplete) {
        if (_buffer.empty()) {
            bytesRecv = recv(_socketClient.getSocket(), _buffer.data(), _buffer.size(), 0);
            if (checkErrorBytesExchange(bytesRecv)) {
                return;
            }
            _body.append(_buffer.begin(), _buffer.end());
            _buffer.clear();
        }
        if (findHeaderChunck()) {
            std::size_t size = std::min(_contentLength, static_cast<std::size_t>(_config._clientBodyBufferSize));
            size = std::min(_body.size(), size);
            checkErrorBytesExchange((_body.size() >= size) ? size : _body.size());
            _buffer.assign(_body.begin(), (_body.size() >= size) ? _body.begin() + size : _body.end());
            if (_body.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
                _body = _body.substr(0, _config._clientBodyBufferSize);
            else
                _body.clear();
            write(_pipeFdIn[STDOUT_FILENO], _buffer.data(), size);
            _contentLength -= size;
            _buffer.clear();
            if (_contentLength > 0) {
                _methodeToRecv = &HttpBodyRequest::recvBodyChunck;
                break;
            }
        }
    }
}

void HttpBodyRequest::recvBodyChunck(){
    std::size_t chunkSize;
    std::size_t bytesRecv;
    std::size_t totalBytesRecv;
    std::size_t posCRLF;

    while (_contentLength > 0) {
        bytesRecv = recv(_socketClient.getSocket(), _buffer.data(), _buffer.size(), 0);
        if (checkErrorBytesExchange(bytesRecv)) {
            return;
        }
        _totalBytesRecv += bytesRecv;
        if (_totalBytesRecv > _contentLength)
            throw Exception("Request chunck size exceeds content length", 413);
        _body.append(_buffer.begin(), _buffer.end());
        _buffer.clear();
        posCRLF = _body.find("\r\n");
        if(posCRLF == std::string::npos) {
            std::size_t size = std::min(_contentLength, static_cast<std::size_t>(_config._clientBodyBufferSize));
            size = std::min(_body.size(), size);
            checkErrorBytesExchange((_body.size() >= size) ? size : _body.size());
            _buffer.assign(_body.begin(), (_body.size() >= size) ? _body.begin() + size : _body.end());
            if (_body.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
                _body = _body.substr(0, _config._clientBodyBufferSize);
            else
                _body.clear();
            write(_pipeFdIn[STDOUT_FILENO], _buffer.data(), size);
            _contentLength -= size;
            _buffer.clear();
            continue;
        }else {
            std::size_t size = std::min(_contentLength, static_cast<std::size_t>(_config._clientBodyBufferSize));
            size = std::min(_body.size(), size);
            checkErrorBytesExchange((_body.size() >= size) ? size : _body.size());
            _buffer.assign(_body.begin(), (_body.size() >= size) ? _body.begin() + size : _body.end());
            if (_body.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
                _body = _body.substr(0, _config._clientBodyBufferSize);
            else
                _body.clear();
            write(_pipeFdIn[STDOUT_FILENO], _buffer.data(), size);
            _contentLength -= size;
            }
        }
    }
}

bool HttpBodyRequest::findHeaderChunck() {
    std::size_t posCRLF = _body.find("\r\n");
    if(posCRLF == std::string::npos) {
        _buffer.clear();
        return false;
    }
    _contentLength = stringToSizet(_body.substr(0, posCRLF));
    _body = _body.substr(0, posCRLF + 2);
    if (_contentLength == 0) {
        _requestBodyIsComplete = true;
        return false;
    }
    return true;
}

void HttpBodyRequest::recvBody() {
    while (!_body.empty()) {
        std::size_t size = (_contentLength > static_cast<std::size_t>(_config._clientBodyBufferSize)) ? _config._clientBodyBufferSize : _contentLength;
        checkErrorBytesExchange(size);
        _buffer.assign(_body.begin(),
                       (_body.size() > size) ?
                       _body.begin() + _config._clientBodyBufferSize : _body.end());
        if (_body.size() > size)
            _body = _body.substr(0, size);
        else
            _body.clear();
        write(_pipeFdIn[STDOUT_FILENO], _buffer.data(), size);
        _buffer.clear();
    }
    recvAndWriteData(_pipeFdIn[STDOUT_FILENO], _socketClient.getSocket(), _buffer, *this,
             &HttpBodyRequest::bodyIsComplete);
}

bool HttpBodyRequest::bodyIsComplete(std::size_t& bytesRecv){
    if ( _requestBodyIsComplete || checkErrorBytesExchange(bytesRecv))
        return false;
    if (_totalBytesRecv >= _contentLength) {
        _requestBodyIsComplete = true;
    }
    return true;
}

bool HttpBodyRequest::checkErrorBytesExchange(std::size_t bytesExchange){
    if (static_cast<int>(bytesExchange) == -1)
        return true;
    if (bytesExchange == 0 )
        throw Exception("recvMessage close connection", 0);
    _totalBytesRecv += bytesExchange;
    if (static_cast<int>(_totalBytesRecv) > _config._clientMaxBodySize)
        throw Exception("Request Max body size exceeds the maximum limit", 413);
}






