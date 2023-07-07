//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpMessage.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpMessage::HttpMessage(Config& config, Socket& socketClient)
        : _config(config), _socketClient(socketClient), _serverToken(), _totalBytesExchange(),
          _contentLength(), _headerIsComplete(false), _chunkedIsComplete(true), _requestIsComplete(false),
          _data(), _peg(), _startLineMethode(), _startLineURL(),
          _startLineVersion(), _mapHttpHeadersRequest(){}//@todo to update

HttpMessage::~HttpMessage() {}

HttpMessage::HttpMessage(const HttpMessage & other)
        : _config(other._config), _socketClient(other._socketClient),
          _totalBytesExchange(other._totalBytesExchange), _contentLength(other._contentLength), _chunkedIsComplete(other._isChunked),
          _data(), _peg(other._peg){}

HttpMessage &HttpMessage::operator=(const HttpMessage &rhs) {
    if ( this != & rhs) {
        this->_config = rhs._config;
        this->_socketClient = rhs._socketClient;
        this->_serverToken = rhs._serverToken;
        this->_contentLength = rhs._contentLength;
        this->_headerIsComplete = rhs._headerIsComplete;
        this->_isChunked = rhs._isChunked;
        this->_peg = rhs._peg;
        this->_startLineMethode = rhs._startLineMethode;
        this->_startLineURL = rhs._startLineURL;
        this->_startLineVersion = rhs._startLineVersion;
        this->_mapHttpHeadersRequest = rhs._mapHttpHeadersRequest;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode                                  |
*====================================================================================
*/

bool HttpMessage::recvMessage() {
    if (!_headerIsComplete)
        return recvHeader();
    else
        return continueBody();
}

bool HttpMessage::sendMessage() {
    if (_requestIsComplete)

}

bool HttpMessage::sendMessage(int code) {
    _statusCode = code;
    setContent();

}

/*
*====================================================================================
*|                                  Private Methode to recvMessage                         |
*====================================================================================
*/


bool HttpMessage::recvHeader() {//add resetSend()
    recvData(_socketClient.getSocket(), _buffer, *this,
             &HttpMessage::headerIsNotComplete);
    if (_headerIsComplete) {
        _peg.setStringStream(_data);
        _peg.setMapTokenHeaderStartLine();
        _peg.findToken(*this, 0);
        return (_requestIsComplete);
    }
    return false;
}

bool HttpMessage::continueBody(){
    recvAndWriteData(_pipeFdIn[STDOUT_FILENO], _socketClient.getSocket(),
                     _buffer, *this,_methodeToRecv);
    if (_bodyIsComplete){
        close(_pipeFdIn[STDOUT_FILENO]);
        int status;
        waitpid(_pid, &status,0);
        if (status != 0)
            throw Exception("CGI in GET fail", 500);
        ::readData(_pipeFdOut[STDIN_FILENO], _buffer, *this,
                   &HttpMessage::readDataIsNotComplete);
        close(_pipeFdOut[STDIN_FILENO]);
        controleHeader();
        setContent();
        return true;
    }
    return false;
};

bool HttpMessage::headerIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytesExchange(bytesExchange))
        return false;
    _data.append(_buffer.begin(), _buffer.end());
    _buffer.clear();
    if (_data.find("\r\n\r\n") == std::string::npos){
        _headerIsComplete = true;
        return false;
    }
    return true;
}

bool HttpMessage::checkErrorBytesExchange(std::size_t& bytesExchange){
    if (static_cast<int>(bytesExchange) == -1)
        return true;
    if (bytesExchange == 0 )
        throw Exception("recvMessage close connection", 0);
    _totalBytesExchange += bytesExchange;
    if (static_cast<int>(_totalBytesExchange) > _config._clientMaxBodySize)
        throw Exception("Request Max body size exceeds the maximum limit", 413);
}

bool HttpMessage::chunkIsComplete(std::string & str){
    while (!str.empty()) {
        recvData(int socket, std::vector<char>& buffer, T& base,
                bool (T::*dataIsNotComplete)(std::size_t&))
        std::size_t startPosCRLF = str.find("\r\n");
        if (startPosCRLF != std::string::npos) {
            std::size_t chunkSize = stringToSizet(str.substr(0, startPosCRLF));
            if (chunkSize == 0)
                return (_chunkedIsComplete = true);
            else {
                str = str.substr(startPosCRLF + 2);
                _contentLength = chunkSize;
                if (bodyChunkIsComplete(<#initializer#>))
                    continue;
                if (!recvData(&HttpMessage::bodyChunkIsComplete))
                    return false;
            }
        }
    }
    return false;
}

bool HttpMessage::bodyIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytesExchange(bytesExchange))
        return false;
    if (_totalBytesExchange >= _contentLength) {
        _bodyIsComplete = true;
        return false;
    }
    return true;
}

/*
*====================================================================================
*|                                  Private Methode to read write                   |
*====================================================================================
*/

bool HttpMessage::readDataIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytes(bytesExchange))
        return false;
    _data.append(_buffer.begin(), _buffer.end());
    _buffer.clear();
    return true;
}

bool HttpMessage::checkErrorBytes(std::size_t& bytesExchange){
    if (static_cast<int>(bytesExchange) == -1)
        throw Exception("link with child fail", 500);
    if (bytesExchange == 0 )
        return true;
    _totalBytesExchange += bytesExchange;
    if (static_cast<int>(_totalBytesExchange) > _config._clientMaxBodySize)
        throw Exception("Reponse Max body size exceeds the maximum limit", 413);
}

bool HttpMessage::writeDataIsNotComplete(std::size_t& bytesExchange){
    if (static_cast<int>(bytesExchange) == -1 || static_cast<int>(bytesExchange) == 0)
        throw Exception("link with child fail", 500);
    _data = _data.substr(0, _buffer.size());
    _buffer.clear();
    if (_data.empty())
        return false;
    std::size_t count = std::min(_data.size(), _buffer.size());
    std::copy(_data.begin(), _data.begin() + count, _buffer.begin());
    return true;
}


/*
*====================================================================================
*|                                  select Methode                                  |
*====================================================================================
*/

std::string HttpMessage::methodeGET(std::string & token) {
    extractHeaderData();
    if (!checkIsAllowedMethode(1, 3, 5))
        throw Exception("Method GET Not Allowed ", 405);
    if(_location->_cgiPass.empty() || !checkIsPHP()) {
        findRessource();
        if (_oss.str().empty()) {
            if (setFile(_startLineURL, _oss)) {
                throw Exception("impossible to open file", 403);
            }
        }
        setContent();
        return "";
    }
    executePhp();
    return std::string();
}

std::string HttpMessage::methodePOST(std::string & token) {
    extractHeaderData();
    if (!checkIsAllowedMethode(2, 3, 6))
        throw Exception("Method Post Not Allowed ", 405);
    if(!checkIsPHP()) {
        findPostRessource();
    }
    executePhp();
    return std::string();
}

std::string HttpMessage::methodeDELETE(std::string & token) {
    extractHeaderData();
    if (!checkIsAllowedMethode(4, 5, 6))
        throw Exception("Method GET Not Allowed ", 405);
    findRessource();
    if (!removeDirectory(_startLineURL))
        throw Exception("fail to remove ressource", 500);
    _statusCode = 204;
    return std::string();
}

bool HttpMessage::checkIsAllowedMethode(int allow, int dual1, int dual2) const{
    return(_location->_allowMethods == 7 ||
           _location->_allowMethods == allow ||
           _location->_allowMethods == dual1 ||
           _location->_allowMethods == dual2);
};

void HttpMessage::extractHeaderData() {
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty() && !_headerIsComplete)
        _peg.findToken(*this,  0);
}

/*
*====================================================================================
*|                                  Information Methode                             |
*====================================================================================
*/

std::string HttpMessage::Host(std::string & token){
    addToMapHttpHeader(token);
    std::string serverName = _mapHttpHeadersRequest.find(token)->second;
    if (serverName.empty())
        throw Exception("No host in request", 400);
    std::string serverToken = _socketClient.getServer()->findServerName(serverName);
    findBestConfig(_config._mapTokenVectorUriConfig.find(serverToken)->second);
    return std::string();
}

void HttpMessage::findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig) {
    std::vector<std::pair<std::string, Config> >::iterator bestLocation = UriConfig.end() - 1;
    for (std::vector<std::pair<std::string, Config> >::iterator itvec = UriConfig.begin();
         itvec != UriConfig.end(); ++itvec) {
        if (_startLineURL.find(itvec->first) == 0 && itvec->first.length() > bestLocation->first.length())
            bestLocation = itvec;
    }
    _startLineURL = bestLocation->second._root +
                    _startLineURL.substr(bestLocation->first.length() - 1);
    _location = &bestLocation->second;
}

void HttpMessage::findRessource() {
    if (!isFile(_startLineURL)){
        if (!isDirectory(_startLineURL)) {
            if (!setIndex()) {
                if (!_location->_autoindex || !setAutoIndex()) {
                    throw Exception("root/Uri not found", 404);
                }
            }
        }
    }

}

void HttpMessage::findPostRessource() {
    if (!isExec(_startLineURL)) {
        findRessource();
        if (_oss.str().empty())
            throw Exception("Method Post has not an exec ", 405);
    }
}

bool HttpMessage::setIndex(){
    for (std::set<std::string>::iterator  itSet = _location->_index.begin();
         itSet != _location->_index.end() ; ++itSet) {
        std::string Url = _startLineURL;
        Url += "/" + *itSet;
        if (isFile(Url)){
            _startLineURL = Url;
            return true;
        }
    }
    return false;
}

bool HttpMessage::setAutoIndex(){
    _contentType = "text/html";
    _statusCode = 200;
    return autoIndexToHtml(_location->_root, _startLineURL, _oss);
}

bool HttpMessage::checkIsPHP() {
    std::string & url = _startLineURL;
    std::size_t slashPos = _startLineURL.find_last_of('/');
    std::size_t dotPos = _startLineURL.find_last_of('.');
    std::size_t questionPos = _startLineURL.find_last_of('?');
    if (dotPos != std::string::npos && dotPos < slashPos) {
        if (questionPos != std::string::npos) {
            _queryString = _startLineURL.substr(questionPos + 1);
            _startLineURL = _startLineURL.substr(0, questionPos);
        }
        if (_startLineURL.substr(dotPos + 1) == "php")
            return isExec(_startLineURL);
    }
    return false;
}

std::string HttpMessage::ContentLength(std::string &token) {
    addToMapHttpHeader(token);
    if (!_chunkedIsComplete) {
        std::string contentLength = getValueHeader("Content-Length:");
        if (!contentLength.empty())
            _contentLength = std::atoi(contentLength.c_str());
        if (static_cast<int>(_contentLength) > _config._clientMaxBodySize)
            throw Exception("Request body size exceeds the maximum limit", 413);
    }
    return std::string();
}

std::string HttpMessage::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    _startLineMethode = token;
    std::string chunked = getValueHeader("Transfer-Encoding:");
    if (chunked == "chunked" )
        _chunkedIsComplete = false;
    return std::string();
}

std::string HttpMessage::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    _mapHttpHeadersRequest.insert(std::make_pair(token, data));
    return std::string();
}

std::string HttpMessage::getValueHeader(const std::string & token) {
    const std::map<std::string, std::string>::iterator it = _mapHttpHeadersRequest.find(token);
    if (it != _mapHttpHeadersRequest.end())
        return it->second;
    return std::string();
}

std::string HttpMessage::endHeader(std::string& token) {
    _data =  _data.substr(_data.find("\r\n\r\n") + 4);
    _headerIsComplete = true;
    return "";
}

/*
*====================================================================================
*|                                       Execute Methode                            |
*====================================================================================
*/

bool HttpMessage::executePhp(){
    if (launchChild(_pipeFdIn, _pipeFdOut, _pid,
                    setArgv("/usr/bin/php", _startLineURL),
                setPhpEnv(_startLineMethode, _queryString, _mapHttpHeadersRequest)))
        throw Exception("error to create child process", 500);
    close(_pipeFdIn[STDIN_FILENO]);
    close(_pipeFdOut[STDOUT_FILENO]);
    writeData(_pipeFdIn[STDOUT_FILENO], _buffer, *this, &HttpMessage::writeDataIsNotComplete);
    return continueBody();
}

void HttpMessage::controleHeader(){
//    std::string line;
//    while (std::getline(_data, line)){
//
//    }

}



/*
*====================================================================================
*|                                       set Conetent                               |
*====================================================================================
*/

void HttpMessage::errorPage(){
    _oss.clear();
    std::string path(_location->_code.getStatusPage(_statusCode));
    if (!setFile(path, _oss)) {
        if (_oss.str().empty()) {
            _oss.str() = "<!DOCTYPE html><html><head><title>" +
            _config._code.getStatusCode(_statusCode) + "</title></head><body><h1>" +
            _config._code.getStatusCode(_statusCode) + "</h1><p>Sorry</p></body></html>";
        }
        _contentType = "text/html";
    }else {
        _contentType = _config._mapMimeType.at(path.substr(path.find_last_of('.')));
    }
}

void HttpMessage::redirection(){
    _mapHttpHeadersRequest["Location:"] = _location->_code.getStatusPage(_statusCode);
}

void HttpMessage::addMapHttpHeader(){
    for (std::map<std::string, std::string>::iterator  i = _mapHttpHeadersRequest.begin();
         i != _mapHttpHeadersRequest.end(); ++i) {
        if (!i->second.empty())
            _data += i->first + " " + i->second + "\r\n";
    }
}

void HttpMessage::setContent(){
    _data = _startLineVersion + " ";
    if (_location->_return != 0)
        _statusCode = _location->_return;
    if (_statusCode >= 400)
        errorPage();
    else if (_statusCode >= 300)
        redirection();
    _data += _location->_code.getStatusCode(_statusCode) + "\r\n";
    _data += "Date: " + addDate() + "\r\n";
    _data += "Server: webserv/1.0 (ubuntu)\r\n";
    addMapHttpHeader();
    if (!_oss.str().empty()) {
        if (static_cast<int>(_oss.str().size()) >= (_location->_clientMaxBodySize / 2)) {
            _data += "Transfer-Encoding: chunked\r\n";
            chunkData(_vecdata, _oss.str(), (_location->_clientMaxBodySize / 2));
        } else {
            _data += "Content-Length: " + intToString(_oss.str().size()) + "\r\n";
            _vecdata.push_back(_oss.str());
        }
        _data += "Content-Type: " + _contentType + "\r\n";
    }
    _data += "\r\n";
}



