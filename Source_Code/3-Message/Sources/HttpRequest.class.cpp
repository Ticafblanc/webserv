//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpRequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpRequest::HttpRequest(Config& config, Socket& socketClient)
        : _config(config), _socketClient(socketClient), _serverToken(), _bytesRecv(), _totalBytesRecv(),
          _contentLength(), _headerIsComplete(false), _chunkedIsComplete(true), _requestIsComplete(false),
          _buffer(_config._clientHeaderBufferSize), _data(), _peg(), _startLineMethode(), _startLineURL(),
          _startLineVersion(), _mapHttpHeaders(){}//@todo to update

HttpRequest::~HttpRequest() {}

HttpRequest::HttpRequest(const HttpRequest & other)
        : _config(other._config), _socketClient(other._socketClient), _bytesRecv(other._bytesRecv),
          _totalBytesRecv(other._totalBytesRecv), _contentLength(other._contentLength), _chunkedIsComplete(other._chunkedIsComplete),
          _buffer(other._buffer), _data(), _peg(other._peg){}

HttpRequest &HttpRequest::operator=(const HttpRequest &rhs) {
    if ( this != & rhs) {
        this->_config = rhs._config;
        this->_socketClient = rhs._socketClient;
        this->_serverToken = rhs._serverToken;
        this->_bytesRecv = rhs._bytesRecv;
        this->_contentLength = rhs._contentLength;
        this->_headerIsComplete = rhs._headerIsComplete;
        this->_chunkedIsComplete = rhs._chunkedIsComplete;
        this->_buffer = rhs._buffer;
        this->_peg = rhs._peg;
        this->_startLineMethode = rhs._startLineMethode;
        this->_startLineURL = rhs._startLineURL;
        this->_startLineVersion = rhs._startLineVersion;
        this->_mapHttpHeaders = rhs._mapHttpHeaders;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode                                  |
*====================================================================================
*/

bool HttpRequest::recvRequest() {
    if (!_headerIsComplete)
        return recvHeader();
    else if (!_chunkedIsComplete)
        return recvChunck();
    else
        return recvBody();
}

bool HttpRequest::sendRequest() {
    if (_requestIsComplete)

}

bool HttpRequest::sendRequest(int code) {
    _statusCode = code;
    setContent();

}

/*
*====================================================================================
*|                                  Private Methode                                 |
*====================================================================================
*/


bool HttpRequest::recvHeader() {
    if (recvData(&HttpRequest::headerIsComplete)) {
        _peg.setStringStream(_data);
        _peg.setMapTokenHeaderStartLine();
        _peg.findToken(*this, 0);
        return (_requestIsComplete);
    }
    return false;
}

bool HttpRequest::headerIsComplete(std::string & str){
    _data += str;
    if (str.find("\r\n\r\n") != std::string::npos){
        return true;
    }
    return false;
}

bool HttpRequest::recvChunck() {
    if (recvData(&HttpRequest::chunkIsComplete)) {
        if (!executeCGI())
            throw Exception("impossible to open file", 403);
        return _requestIsComplete = true;
    }
    return false;
}

bool HttpRequest::chunkIsComplete(std::string & str){
    std::size_t startPosCRLF = str.find("\r\n");
    if (startPosCRLF != std::string::npos) {
        std::size_t chunkSize = stringToSizet(_data.substr(0, startPosCRLF)) + 2;
        if (chunkSize == 0)
            return (_chunkedIsComplete = true);
        else {
            _contentLength = chunkSize;
            _data += str.substr(chunkSize + 2);
            recvData(&HttpRequest::bodyIsComplete);
            _data += _data.substr(0, str.size() - 2);
        }
    }
    return false;
}

bool HttpRequest::recvBody() {
    if (_data.size() >= _contentLength || recvData(&HttpRequest::bodyIsComplete)) {
        if (!executeCGI())
            throw Exception("CGI in GET fail", 500);
        return _requestIsComplete = true;
    }
    return false;
}

bool HttpRequest::bodyIsComplete(std::string & str){
    _data += str;
    if (_data.size() >= _contentLength)
        return true;
    return false;
}

/*
*====================================================================================
*|                                  Recv Methode                                    |
*====================================================================================
*/

bool HttpRequest::recvData(bool (HttpRequest::*dataIsComplete)(std::string &)){
    std::string str;
    while (true) {
        _buffer.clear();
        _bytesRecv = recv(_socketClient.getSocket(), _buffer.data(), _buffer.size(), 0);
        if (checkErrorBytesRecv())
            return false;
        str.append(_buffer.begin(), _buffer.end());
        if ((this->*(dataIsComplete))(str))
            return true;
    }
}

bool HttpRequest::checkErrorBytesRecv(){
    if (static_cast<int>(_bytesRecv) == -1)
        return true;
    if (_bytesRecv == 0 )
        throw Exception("recvRequest close connection", 0);
    _totalBytesRecv += _bytesRecv;
    if (static_cast<int>(_totalBytesRecv) > _config._clientMaxBodySize)
        throw Exception("Request Max body size exceeds the maximum limit", 413);
}

/*
*====================================================================================
*|                                  select Methode                                  |
*====================================================================================
*/



std::string HttpRequest::methodeGET(std::string & token) {
    extractHeaderData();
    if (!checkIsAllowedMethode(1, 3, 5))
        throw Exception("Method GET Not Allowed ", 405);
    std::string cgi = checkIsCgi();
    if (!cgi.empty()) {
        if (executCgi()) {
            throw Exception("CGI in GET fail", 500);
        }
    }
    else if (_oss.str().empty()) {
        if (setFile(_request.getUrl())) {
            throw Exception("impossible to open file", 403);
        }
    }
    _mapHttpHeaders.clear();
    setContent();
    return std::string();
}

std::string HttpRequest::methodePOST(std::string & token) {
    extractHeaderData();
    if (!checkIsAllowedMethode(2, 3, 6))
        throw Exception("Method Post Not Allowed ", 405);
    std::string cgi = checkIsCgi();
    if (cgi.empty())
        throw Exception("Method Post has not a cgi ", 405);
    if (!_chunkedIsComplete)
        recvChunck();
    else if (!_bodyIsComplete)
        recvBody();
    if (_requestIsComplete)
        setContent();
    return std::string();
}

std::string HttpRequest::methodeDELETE(std::string & token) {
    extractHeaderData();
    if (!checkIsAllowedMethode(4, 5, 6))
        throw Exception("Method GET Not Allowed ", 405);
    if (_oss.str().empty()) {
        if (!removeDirectory(_startLineURL))
            throw Exception("fail to remove ressource", 500);
        _statusCode = 204;
    }
    return std::string();
}

bool HttpRequest::checkIsAllowedMethode(int allow, int dual1, int dual2) const{
    return(_location->_allowMethods == 7 ||
           _location->_allowMethods == allow ||
           _location->_allowMethods == dual1 ||
           _location->_allowMethods == dual2);
};

void HttpRequest::extractHeaderData() {
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty() && !_headerIsComplete)
        _peg.findToken(*this,  0);
    findRessource();
}

/*
*====================================================================================
*|                                  Information Methode                             |
*====================================================================================
*/

std::string HttpRequest::Host(std::string & token){
    addToMapHttpHeader(token);
    std::string serverName = _mapHttpHeaders.find(token)->second;
    if (serverName.empty())
        throw Exception("No host in request", 400);
    std::string serverToken = _socketClient.getServer()->findServerName(serverName);
    findBestConfig(_config._mapTokenVectorUriConfig.find(serverToken)->second);
    return std::string();
}

void HttpRequest::findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig) {
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

void HttpRequest::findRessource() {
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

bool HttpRequest::setIndex(){
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

bool HttpRequest::setAutoIndex(){
    _contentType = "text/html";
    _statusCode = 200;
    return autoIndexToHtml(_location->_root, _startLineURL, _oss);
}

std::string HttpRequest::checkIsCgi() {
    std::map<std::string, std::string> mapCGI;
    mapCGI["php"] = "/usr/bin/php";
    mapCGI["py"] = "/usr/bin/python";
    mapCGI["sh"] = "/usr/bin/bash";
    std::string & url = _startLineURL;
    std::size_t pos = url.find_last_of('.');
    if (pos != std::string::npos) {
        std::map<std::string, std::string>::iterator cgi = mapCGI.find(url.substr(pos + 1));
        if (cgi != _config._mapMimeType.end()){
            return cgi->second;
        }
    }
    return "";
}

std::string HttpRequest::ContentLength(std::string &token) {
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

std::string HttpRequest::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    _startLineMethode = token;
    std::string chunked = getValueHeader("Transfer-Encoding:");
    if (chunked == "chunked" )
        _chunkedIsComplete = false;
    return std::string();
}

std::string HttpRequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    _mapHttpHeaders.insert(std::make_pair(token, data));
    return std::string();
}

std::string HttpRequest::getValueHeader(const std::string & token) {
    const std::map<std::string, std::string>::iterator it = _mapHttpHeaders.find(token);
    if (it != _mapHttpHeaders.end())
        return it->second;
    return std::string();
}

std::string HttpRequest::endHeader(std::string& token) {
    _data =  _data.substr(_data.find("\r\n\r\n") + 4);
    _headerIsComplete = true;
    return "";
}

/*
*====================================================================================
*|                                       Execute Methode                            |
*====================================================================================
*/

void HttpRequest::errorPage(){
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

void HttpRequest::redirection(){
    _mapHttpHeaders["Location:"] = _location->_code.getStatusPage(_statusCode);
}

void HttpRequest::addMapHttpHeader(){
    for (std::map<std::string, std::string>::iterator  i = _mapHttpHeaders.begin();
         i != _mapHttpHeaders.end(); ++i) {
        if (!i->second.empty())
            _data += i->first + " " + i->second + "\r\n";
    }
}

void HttpRequest::setContent(){
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
    if (!_oss.str().empty()) {
        if (static_cast<int>(_oss.str().size()) >= (_location->_clientMaxBodySize / 2)) {
            _data += "Transfer-Encoding: chunked\r\n";
            for (int i = 0; i < _oss.str().size() ; i += (_location->_clientMaxBodySize / 2)) {


            }
        } else {
            _data += "Content-Length: " + intToString(_oss.str().size()) + "\r\n";
        }
        _data += "Content-Type: " + _contentType + "\r\n";
    }
    addMapHttpHeader();
    _data += "\r\n" + _oss.str();
}



