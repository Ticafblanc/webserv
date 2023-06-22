//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpRequest.class.hpp>

void HttpRequest::setMapTokenStartLine() {
    _peg.setMapToken("GET", &HttpRequest::methodeGET);
    _peg.setMapToken("POST", &HttpRequest::methodePOST);
    _peg.setMapToken("DELETE", &HttpRequest::methodeDELETE);
}

void HttpRequest::setMapTokenInformation() {
    _peg.clearMapToken();
    _peg.setMapToken("Accept:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Charset:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Datetime:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Encoding:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Language:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Patch:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Ranges:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Credentials:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Headers:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Methods:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Origin:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Expose-Headers:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Max-Age:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Request-Method:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Request-Headers:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Age:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Allow:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Alt-Svc:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Authorization:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Cache-Control:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Connection:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Disposition:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Encoding:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Language:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Length:", &HttpRequest::ContentLength);
    _peg.setMapToken("Content-Location.class:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-MD5:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Range:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Type:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Cookie:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("DASL:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Date:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("DAV:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Depth:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Destination:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("DNT (Do Not Track):", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("ETag:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Expect:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Expires:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Forwarded:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("From:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Host:", &HttpRequest::Host);
    _peg.setMapToken("If:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Match:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Modified-Since:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("If-None-Match:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Range:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Unmodified-Since:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("IM (Instance Manipulation):", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Last-Modified:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Link:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Location.class:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Lock-Token:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Max-Forwards:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("MIME-Version:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Origin:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Overwrite:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("P3P (Platform for Privacy Preferences):", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Pragma:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Prefer:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Preference-Applied:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Proxy-Authenticate:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Proxy-Authorization:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Proxy-Connection:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Range:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Referer:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Retry-After:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Server.class:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Set-Cookie:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-Dest:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-Mode:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-Site:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-User:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("SLUG:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("SOAPAction:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Status-URI:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Strict-Transport-Security:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("TE:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Timeout:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Trailer:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Transfer-Encoding:", &HttpRequest::TransfereEncoding);
    _peg.setMapToken("Upgrade:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("User-Agent:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Upgrade-Insecure-Requests:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Variant-Vary:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Vary:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("Via:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("WWW-Authenticate:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("X-Forwarded-For:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("X-Forwarded-Proto:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("X-Frame-Options:", &HttpRequest::addToMapHttpHeader);
    _peg.setMapToken("X-XSS-Protection:", &HttpRequest::addToMapHttpHeader);
}

void HttpRequest::extractHeaderData() {
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    setMapTokenInformation();
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
    if (isDirectory())
        setIndex();
    if (isFile(_request.getUrl()))
        _cgi = checkIsCgi();
    else if (_location->_autoindex)
        setAutoIndex();
    else
        throw Exception("Uri not found", 404);
}

bool HttpRequest::isDirectory() {
    struct stat statbuf;
    if (stat(_request.getUrl().c_str(), &statbuf) != 0)
        return false;
    return S_ISDIR(statbuf.st_mode);
}

bool HttpRequest::isFile(std::string & path) {
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
        return false;
    return S_ISREG(statbuf.st_mode);
}

std::string HttpRequest::checkIsCgi() {
    std::string & url = _request.getUrl();
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
    DIR* directory = opendir(_location->_root.c_str());
    if (!directory)
        throw Exception("fail to create autoindex", 404);
    _oss << "<!DOCTYPE html><html><head><title>Auto Index of " << _request.getUrl()
         << "</title></head><body><h1>Auto Index of " << _request.getUrl() << "</h1><ul>";
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        _oss << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name << "</a></li>";
    }
    _oss << "</ul></body></html>";
    closedir(directory);
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
        _chunked = true;
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
    _startLineMethode = token;
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    setMapTokenInformation();
    while(!_peg.checkIsEmpty())
        _peg.findToken(*this,  0);
    return std::string();
}

std::string HttpRequest::methodeDELETE(std::string & token) {
    _startLineMethode = token;
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    setMapTokenInformation();
    while(!_peg.checkIsEmpty())
        _peg.findToken(*this,  0);
    return std::string();
}

std::string HttpRequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    _mapHttpHeaders.insert(std::make_pair(token, data));
    return std::string();
}


HttpRequest::HttpRequest(Config& config, Socket& socket)
: _config(config), _socketClient(socket), _serverToken(), _bytesRecv(), _totalBytesRecv(), _contentLength(),
_chunked(false), _crlf("\r\n\r\n"), _buffer(), _data(), _peg(),
_startLineMethode(), _startLineURL(), _startLineVersion(), _mapHttpHeaders(), _complete(false){}//@todo to update

HttpRequest::~HttpRequest() {}

HttpRequest::HttpRequest(const HttpRequest & other)
: _config(other._config), _socketClient(other._socketClient), _bytesRecv(other._bytesRecv),
  _totalBytesRecv(other._totalBytesRecv), _contentLength(other._contentLength), _chunked(other._chunked), _crlf(other._crlf),
  _buffer(other._buffer), _data(), _peg(other._peg), _complete(other._complete){}

HttpRequest &HttpRequest::operator=(const HttpRequest &rhs) {
    if ( this != & rhs) {
        this->_config = rhs._config;
        this->_socketClient = rhs._socketClient;
        this->_serverToken = rhs._serverToken;
        this->_bytesRecv = rhs._bytesRecv;
        this->_contentLength = rhs._contentLength;
        this->_chunked = rhs._chunked;
        this->_crlf = rhs._crlf;
        this->_buffer = rhs._buffer;
        this->_peg = rhs._peg;
        this->_startLineMethode = rhs._startLineMethode;
        this->_startLineURL = rhs._startLineURL;
        this->_startLineVersion = rhs._startLineVersion;
        this->_mapHttpHeaders = rhs._mapHttpHeaders;
        this->_complete = rhs._complete;
    }
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

bool HttpRequest::messageIsNotComplete() {
    return _bytesRecv < _contentLength;
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

void HttpRequest::recvRequest() {
    _buffer.resize(_config._clientHeaderBufferSize);
    _buffer.clear();
    recvData();
    checkBytesRecv();
    if (_startLineMethode.empty())
        recvHeaderfirst();
    else
        recvHeaderChunck();
}

void HttpRequest::recvHeaderfirst() {
    _peg.setStringStream(convertBufferToString());
    setMapTokenStartLine();
    _peg.findToken(*this, 0);
}

void HttpRequest::recvHeaderChunck() {
    ssize_t chunkSize = 0;
    std::istringstream iss(convertBufferToString());
    iss >> std::hex >> chunkSize;
    if (chunkSize == 0) {//"\0\r\n"
        std::size_t startPosCRLF = _data.find("\r\n");
        if (startPosCRLF != std::string::npos)
            _data.erase(startPosCRLF);
    } else
        _contentLength = chunkSize;
}

void HttpRequest::recvData(){
    _bytesRecv = recv(_socketClient.getSocket(), _buffer.data(), _buffer.size(), 0);
}

void HttpRequest::checkBytesRecv(){
    if (_bytesRecv == 0 )
        throw Exception("recvRequest close connection", 0);
    if (_bytesRecv == -1)
        throw Exception(strerror(errno), -1);//add check errno
    _totalBytesRecv += _bytesRecv;
    if (_totalBytesRecv > _config._clientMaxBodySize)
        throw Exception("Request Max body size exceeds the maximum limit", 413);

}

std::string HttpRequest::convertBufferToString() {
    std::string stringBuffer(_buffer.begin(), _buffer.end());
    std::size_t startPosCRLF = stringBuffer.find(_crlf);
    if (startPosCRLF == std::string::npos)
        throw Exception("Request headers size exceeds the maximum limit", 413);
    _data += stringBuffer.substr(startPosCRLF + _crlf.size(),
                                 stringBuffer.size() - (startPosCRLF + _crlf.size()) - _crlf.size());
    return stringBuffer;
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



