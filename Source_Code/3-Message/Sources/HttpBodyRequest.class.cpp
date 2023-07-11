//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpBodyRequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpBodyRequest::HttpBodyRequest(const AHttpMessage& base, const std::string & data)
: AHttpMessage(base), _buffer(_config._clientBodyBufferSize), _totalBytesRecv(),
_methodeToRecv((_isChunked) ? &HttpBodyRequest::recvHeaderChunck : &HttpBodyRequest::recvBody){
    _data = data;
    _totalBytesRecv = _data.size();
    (this->*(_methodeToRecv))();
    if (!data.empty()){
        _buffer.assign(_data.begin(),
                       (_data.size() > static_cast<std::size_t>(_config._clientBodyBufferSize)) ?
                       _data.begin() + _config._clientBodyBufferSize : _data.end());
        if (_data.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
            _data = _data.substr(0, _config._clientBodyBufferSize);
        else
            _data.clear();
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
            _data.append(_buffer.begin(), _buffer.end());
            _buffer.clear();
        }
        if (findHeaderChunck()) {
            std::size_t size = std::min(_contentLength, static_cast<std::size_t>(_config._clientBodyBufferSize));
            size = std::min(_data.size(),  size);
            checkErrorBytesExchange((_data.size() >= size) ? size : _data.size());
            _buffer.assign(_data.begin(),(_data.size() >= size) ? _data.begin() + size : _data.end());
            if (_data.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
                _data = _data.substr(0, _config._clientBodyBufferSize);
            else
                _data.clear();
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
        totalBytesRecv += bytesRecv;
        if (totalBytesRecv > _contentLength)
            throw Exception("Request chunck size exceeds content length", 413);
        _data.append(_buffer.begin(), _buffer.end());
        _buffer.clear();
        posCRLF = _data.find("\r\n");
        if(posCRLF == std::string::npos) {
            std::size_t size = std::min(_contentLength, static_cast<std::size_t>(_config._clientBodyBufferSize));
            size = std::min(_data.size(),  size);
            checkErrorBytesExchange((_data.size() >= size) ? size : _data.size());
            _buffer.assign(_data.begin(),(_data.size() >= size) ? _data.begin() + size : _data.end());
            if (_data.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
                _data = _data.substr(0, _config._clientBodyBufferSize);
            else
                _data.clear();
            write(_pipeFdIn[STDOUT_FILENO], _buffer.data(), size);
            _contentLength -= size;
            _buffer.clear();
            continue;
        }else {
            std::size_t size = std::min(_contentLength, static_cast<std::size_t>(_config._clientBodyBufferSize));
            size = std::min(_data.size(),  size);
            checkErrorBytesExchange((_data.size() >= size) ? size : _data.size());
            _buffer.assign(_data.begin(),(_data.size() >= size) ? _data.begin() + size : _data.end());
            if (_data.size() > static_cast<std::size_t>(_config._clientBodyBufferSize))
                _data = _data.substr(0, _config._clientBodyBufferSize);
            else
                _data.clear();
            write(_pipeFdIn[STDOUT_FILENO], _buffer.data(), size);
            _contentLength -= size;
            }
        }
    }
}

bool HttpBodyRequest::findHeaderChunck() {
    std::size_t posCRLF = _data.find("\r\n");
    if(posCRLF == std::string::npos) {
        _buffer.clear();
        return false;
    }
    _contentLength = stringToSizet(_data.substr(0,posCRLF));
    _data = _data.substr(0,posCRLF + 2);
    if (_contentLength == 0) {
        _requestBodyIsComplete = true;
        return false;
    }
    return true;
}

void HttpBodyRequest::recvBody() {
    while (!_data.empty()) {
        std::size_t size = (_contentLength > static_cast<std::size_t>(_config._clientBodyBufferSize)) ? _config._clientBodyBufferSize : _contentLength;
        checkErrorBytesExchange(size);
        _buffer.assign(_data.begin(),
                       (_data.size() > size) ?
                       _data.begin() + _config._clientBodyBufferSize : _data.end());
        if (_data.size() > size)
            _data = _data.substr(0, size);
        else
            _data.clear();
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






