//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpRequest.class.hpp>
/*
*====================================================================================
*|                                       HeaderRequest                                     |
*====================================================================================
*/

HeaderRequest::HeaderRequest()
        : _peg(), _startLineMethode(), _startLineURL(), _startLineVersion(), _mapHttpHeaders(), _endHeader(false){}

HeaderRequest::HeaderRequest(std::string &message)
        : _peg(message), _startLineMethode(), _startLineURL(), _startLineVersion(),_mapHttpHeaders(), _endHeader(false){
    setMapTokenStartLine();
    _peg.findToken(*this, 0);
}

HeaderRequest::~HeaderRequest() {}

HeaderRequest::HeaderRequest(const HeaderRequest &) {}

HeaderRequest &HeaderRequest::operator=(const HeaderRequest & rhs) {
    this->_peg = rhs._peg;
    this->_startLineMethode = rhs._startLineMethode;
    this->_startLineURL = rhs._startLineURL;
    this->_startLineVersion = rhs._startLineVersion;
    this->_mapHttpHeaders = rhs._mapHttpHeaders;
    this->_endHeader = rhs._endHeader;
    return *this;
}

void HeaderRequest::setMapTokenStartLine() {
    _peg.setMapToken("GET", &HeaderRequest::addToStartLine);
    _peg.setMapToken("POST", &HeaderRequest::addToStartLine);
    _peg.setMapToken("DELETE", &HeaderRequest::addToStartLine);
}

void HeaderRequest::setMapTokenInformation() {
    _peg.clearMapToken();
    _peg.setMapToken("Accept:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Charset:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Datetime:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Encoding:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Language:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Patch:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Accept-Ranges:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Credentials:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Headers:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Methods:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Allow-Origin:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Expose-Headers:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Max-Age:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Request-Method:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Access-Control-Request-Headers:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Age:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Allow:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Alt-Svc:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Authorization:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Cache-Control:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Connection:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Disposition:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Encoding:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Language:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Length:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Location.class:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-MD5:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Range:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Content-Type:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Cookie:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("DASL:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Date:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("DAV:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Depth:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Destination:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("DNT (Do Not Track):", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("ETag:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Expect:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Expires:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Forwarded:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("From:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Host:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("If:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Match:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Modified-Since:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("If-None-Match:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Range:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("If-Unmodified-Since:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("IM (Instance Manipulation):", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Last-Modified:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Link:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Location.class:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Lock-Token:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Max-Forwards:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("MIME-Version:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Origin:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Overwrite:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("P3P (Platform for Privacy Preferences):", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Pragma:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Prefer:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Preference-Applied:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Proxy-Authenticate:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Proxy-Authorization:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Proxy-Connection:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Range:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Referer:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Retry-After:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Server.class:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Set-Cookie:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-Dest:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-Mode:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-Site:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Sec-Fetch-User:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("SLUG:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("SOAPAction:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Status-URI:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Strict-Transport-Security:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("TE:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Timeout:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Trailer:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Transfer-Encoding:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Upgrade:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("User-Agent:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Upgrade-Insecure-Requests:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Variant-Vary:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Vary:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("Via:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("WWW-Authenticate:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("X-Forwarded-For:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("X-Forwarded-Proto:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("X-Frame-Options:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("X-XSS-Protection:", &HeaderRequest::addToMapHttpHeader);
    _peg.setMapToken("\r\n\r\n", &HeaderRequest::endHeader);
}

std::string HeaderRequest::addToStartLine(std::string & token) {
    _startLineMethode = token;
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    setMapTokenInformation();
    while(!_peg.checkIsEmpty() && !_endHeader)
        _peg.findToken(*this,  0);
    return std::string();
}

std::string HeaderRequest::addToMapHttpHeader(std::string& token) {
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    _mapHttpHeaders.insert(std::make_pair(token, data));
    return std::string();
}

std::string HeaderRequest::endHeader(std::string& token) {
    _endHeader = true;
    return std::string();
}

const std::string &HeaderRequest::getStartLineMethode() const {
    return _startLineMethode;
}

std::string &HeaderRequest::getStartLineUrl(){
    return _startLineURL;
}

const std::string &HeaderRequest::getStartLineVersion() const {
    return _startLineVersion;
}

const std::map<const std::string, const std::string> &HeaderRequest::getMapHttpHeaders() const {
    return _mapHttpHeaders;
}





HttpRequest::HttpRequest(Socket& socket, Config& config)
        : _socket(socket), _config(config), _bytesRecv(), _contentLength(), _buffer(), _headRequest(){}

HttpRequest::~HttpRequest() {}

HttpRequest::HttpRequest(const HttpRequest & other)
        : _socket(other._socket), _config(other._config), _bytesRecv(other._bytesRecv),
          _contentLength(other._contentLength), _buffer(other._buffer), _headRequest(other._headRequest){}

HttpRequest &HttpRequest::operator=(const HttpRequest &rhs) {
    this->_socket = rhs._socket;
    this->_config = rhs._config;
    this->_bytesRecv = rhs._bytesRecv;
    this->_contentLength = rhs._contentLength;
    this->_buffer = rhs._buffer;
    this->_headRequest = rhs._headRequest;
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

void HttpRequest::recvMessage() {
    recvData();
    if (static_cast<int>(_buffer[0].find("\r\n\r\n")) > _config._clientHeaderBufferSize)
        throw Exception("Request headers size exceeds the maximum limit", 413);
    _headRequest = HeaderRequest(_buffer[0]);
    while(messageIsNotComplete()){
        recvData();
    }
}

void HttpRequest::recvData(){
    char buffer[1024];
    memset(buffer, '\0', 1024);
    int bytesRecv = recv(_socket.getSocket(), buffer, 1024, 0);
    _bytesRecv += bytesRecv;
    checkBytesRecv();
    buffer[bytesRecv] ='\0';
    _buffer.push_back(buffer);
}

bool HttpRequest::messageIsNotComplete() {
    if (_contentLength == 0) {
        std::string contentLength = getValueHeader("Content-Length:");
        if (!contentLength.empty())
            _contentLength = std::atoi(contentLength.c_str());
        if (_contentLength > _config._clientBodyBufferSize)
            throw Exception("Request body size exceeds the maximum limit", 413);
    }
    return _bytesRecv < _contentLength;
}

void HttpRequest::checkBytesRecv() const {
    if (_bytesRecv == 0 )
        throw Exception("recv close connection", 0);
    if (_bytesRecv == -1)
        throw Exception(strerror(errno), 500);
    if (_bytesRecv > _config._clientMaxBodySize)
        throw Exception("Request Max body size exceeds the maximum limit", 413);
}

std::string HttpRequest::getValueHeader(const std::string & token) {
    const std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, const std::basic_string<char> > > it =
            _headRequest.getMapHttpHeaders().find(token);
    if (it != _headRequest.getMapHttpHeaders().end())
        return it->second;
    return std::string();
}

std::string HttpRequest::getMethode() {
    return _headRequest.getStartLineMethode();
}

std::string& HttpRequest::getUrl() {
    return _headRequest.getStartLineUrl();
}

