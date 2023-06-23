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
          _contentLength(), _headerIsComplete(false), _chunkedIsComplete(true),
          _buffer(_config._clientHeaderBufferSize), _data(), _peg(), _startLineMethode(), _startLineURL(),
          _startLineVersion(), _mapHttpHeaders(){}//@todo to update

HttpRequest::~HttpRequest() {}

HttpRequest::HttpRequest(const HttpRequest & other)
        : _config(other._config), _socketClient(other._socketClient), _bytesRecv(other._bytesRecv),
          _totalBytesRecv(other._totalBytesRecv), _contentLength(other._contentLength), _chunkedIsComplete(other._chunkedIsComplete), _crlf(other._crlf),
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
*|                                       Methode                                    |
*====================================================================================
*/

void HttpRequest::recvRequest() {
    if (selectRecvMethode())
        *this = HttpRequest(_config, _socketClient);
}

void HttpRequest::sendRequest() {

}

/*
*====================================================================================
*|                                  Private Methode                                 |
*====================================================================================
*/

bool HttpRequest::selectRecvMethode() {
    if (!_headerIsComplete)
        return recvHeader();
    else if (!_chunkedIsComplete)
        return recvChunck();
    else
        return recvBody();
}

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

bool HttpRequest::recvHeader() {
    if (recvData(&HttpRequest::headerIsComplete)) {
        _peg.setStringStream(convertBufferToString());
        _peg.setMapTokenHeaderStartLine();
        _peg.findToken(*this, 0);
        return (_chunkedIsComplete && _bodyIsComplete);
    }
    return false;
}

bool HttpRequest::headerIsComplete(std::string & str){
    _data += str;
    if (str.find("\r\n\r\n") != std::string::npos){
        return _headerIsComplete == true;
    }
    return false;
}

bool HttpRequest::recvChunck() {
    if (recvData(&HttpRequest::chunkIsComplete)) {
       //lauch
        return true;
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
            _data += str.substr(chunkSize + 2);
            recvData(&HttpRequest::bodyIsComplete);
            _contentLength = 0;
            _data += _data.substr(0, str.size() - 2);
        }
    }
    return false;
}

bool HttpRequest::recvBody() {
    if (recvData(&HttpRequest::bodyIsComplete)) {
        //launch
        return true;
    }
    return false;
}

bool HttpRequest::bodyIsComplete(std::string & str){
    _data += str;
    if (str.size() >= _contentLength){
        return true;
    }
    return false;
}

bool HttpRequest::bodyIsNotComplete(){
    return _bytesRecv < _contentLength;
}

std::string HttpRequest::bufferToDataString() {
    std::string stringBuffer(_buffer.begin(), _buffer.end());
    std::size_t startPosCRLF = stringBuffer.find(_crlf);
    if (startPosCRLF == std::string::npos)
        throw Exception("Request headers size exceeds the maximum limit", 413);
    _data += stringBuffer.substr(startPosCRLF + _crlf.size(),
                                 stringBuffer.size() - (startPosCRLF + _crlf.size()) - _crlf.size());
    return stringBuffer;
}













std::string HttpRequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    _mapHttpHeaders.insert(std::make_pair(token, data));
    return std::string();
}

void HttpRequest::extractHeaderData() {
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty())
        _peg.findToken(*this,  0);
}

std::string HttpRequest::Host(std::string & token){
    addToMapHttpHeader(token);
    std::string serverName = _mapHttpHeaders.find(token)->second;
    if (serverName.empty())
        throw Exception("No host in request", 400);
    else{
        std::string serverToken = _socketClient.getServer()->findServerName(serverName);
        if (_serverToken.empty())
            _serverToken = serverToken;
        if (_serverToken.empty() || _serverToken != serverToken)
            throw Exception("server name not found", 404);
    }
    findBestConfig();
    findRessource();
    return std::string();
}

void HttpRequest::findBestConfig() {
    std::vector<std::pair<std::string, Config> >::iterator bestLocation;
    for (std::vector<std::pair<std::string, Config> >::iterator itvec = _config._mapTokenVectorUriConfig.find(_serverToken)->second.begin();
         itvec != _config._mapTokenVectorUriConfig.find(_serverToken)->second.end(); ++itvec) {
        if (_startLineURL.find(itvec->first) == 0 && itvec->first.length() > bestLocation->first.length())
            bestLocation = itvec;
    }
    _startLineURL = bestLocation->second._root +
            _startLineURL.substr(bestLocation->first.length() - 1);
}

void HttpRequest::findRessource() {
    if (isDirectory(_startLineURL))
        setIndex();
    if (isFile(_startLineURL))
        _cgi = checkIsCgi();
    else if (_location->_autoindex)
        setAutoIndex();
    else
        throw Exception("Uri not found", 404);
}


std::string HttpRequest::checkIsCgi() {
    std::string & url = _startLineURL;
    std::size_t pos = url.find_last_of('.');
    if (pos != std::string::npos) {
        std::map<std::string, std::string>::iterator cgi = _mapCGI.find(url.substr(pos + 1));
        if (cgi != _config._mapMimeType.end()){
            return cgi->second;
        }
    }
    return "";
}

void HttpRequest::setIndex(){
    std::string saveUrl = _request.getUrl();
    for (std::set<std::string>::iterator  itSet = _location->_index.begin();
         itSet != _location->_index.end() ; ++itSet) {
        _request.getUrl() += "/" ;
        _request.getUrl() += *itSet;
        if (isFile(_request.getUrl()))
            break;
        _request.getUrl() = saveUrl;
    }
}

void HttpRequest::setAutoIndex(){
    if (autoIndexToHtml(_location->_root.c_str(), _startLineURL, _oss) < 0)
        throw Exception("fail to create autoindex", 404);
    _client.getclient()._contentType = "text/html";
}

std::string HttpRequest::ContentLength(std::string &token) {
    addToMapHttpHeader(token);
    std::string contentLength = getValueHeader("Content-Length:");
    if (!contentLength.empty())
        _contentLength = std::atoi(contentLength.c_str());
    if (_contentLength > _config._clientBodyBufferSize)
        throw Exception("Request body size exceeds the maximum limit", 413);
    return std::string();
}

std::string HttpRequest::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    _startLineMethode = token;
    std::string chunked = getValueHeader("Transfer-Encoding:");
    if (chunked == "chunked" )
        _chunkedIsComplete = true;
    return std::string();
}


std::string HttpRequest::methodeGET(std::string & token) {
    extractHeaderData();

    findRessource();
    if (!checkIsAllowedMethode(1, 3, 5))
        throw Exception("Method GET Not Allowed ", 405);
    if (!_cgi.empty())
        executCgi();
    else
        setFile(_request.getUrl());
    setContent();

    return std::string();
}

std::string HttpRequest::methodePOST(std::string & token) {
    extractHeaderData();;
    return std::string();
}

std::string HttpRequest::methodeDELETE(std::string & token) {
    extractHeaderData();
    return std::string();
}


/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

bool HttpRequest::messageIsNotComplete() {

}

void HttpRequest::setContentLenght() {

}

void HttpRequest::recvMessage() {
    _buffer.resize(_config._clientBodyBufferSize);
    while(messageIsNotComplete()){
        _buffer.clear();
        recvData();
    }
}











std::string HttpRequest::getValueHeader(const std::string & token) {
    const std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, const std::basic_string<char> > > it =
            _mapHttpHeaders.find(token);
    if (it != _mapHttpHeaders.end())
        return it->second;
    return std::string();
}

std::string HttpRequest::getMethode() {
    return _startLineMethode;
}

std::string& HttpRequest::getUrl() {
    return _startLineURL;
}

bool HttpRequest::isComplete() const {
    return _complete;
}





