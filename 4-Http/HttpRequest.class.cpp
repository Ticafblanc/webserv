//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include "HttpRequest.class.hpp"
/*
*====================================================================================
*|                                       HeaderRequest                                     |
*====================================================================================
*/

HeaderRequest::HeaderRequest()
        : _peg(), _startLineMethode(), _startLineURL(), _startLineVersion(), _mapHttpHeaders(), _mapTokenListAction(){
    return;
}

HeaderRequest::HeaderRequest(string &message)
        : _peg(message), _startLineMethode(), _startLineURL(), _startLineVersion(),_mapHttpHeaders(), _mapTokenListAction(){
    setMapTokenStartLine();
    _peg.findToken(*this, _mapTokenListAction, 0);
}

HeaderRequest::~HeaderRequest() {

}

HeaderRequest::HeaderRequest(const HeaderRequest &) {

}

HeaderRequest &HeaderRequest::operator=(const HeaderRequest & rhs) {
    this->_peg = rhs._peg;
    this->_startLineMethode = rhs._startLineMethode;
    this->_startLineURL = rhs._startLineURL;
    this->_startLineVersion = rhs._startLineVersion;
    this->_mapHttpHeaders = rhs._mapHttpHeaders;
    return *this;
}

void HeaderRequest::setMapTokenStartLine() {
    _mapTokenListAction["GET"] = &HeaderRequest::addToStartLine;
    _mapTokenListAction["POST"] = &HeaderRequest::addToStartLine;
    _mapTokenListAction["DELETE"] = &HeaderRequest::addToStartLine;
}

void HeaderRequest::setMapTokenInformation() {
    _mapTokenListAction.clear();
    _mapTokenListAction["Accept:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Accept-Charset:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Accept-Datetime:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Accept-Encoding:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Accept-Language:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Accept-Patch:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Accept-Ranges:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Allow-Credentials:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Allow-Headers:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Allow-Methods:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Allow-Origin:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Expose-Headers:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Max-Age:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Request-Method:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Access-Control-Request-Headers:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Age:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Allow:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Alt-Svc:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Authorization:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Cache-Control:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Connection:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-Disposition:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-Encoding:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-Language:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-Length:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-Location.class:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-MD5:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-Range:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Content-Type:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Cookie:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["DASL:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Date:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["DAV:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Depth:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Destination:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["DNT (Do Not Track):"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["ETag:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Expect:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Expires:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Forwarded:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["From:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Host:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["If:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["If-Match:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["If-Modified-Since:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["If-None-Match:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["If-Range:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["If-Unmodified-Since:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["IM (Instance Manipulation):"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Last-Modified:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Link:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Location.class:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Lock-Token:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Max-Forwards:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["MIME-Version:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Origin:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Overwrite:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["P3P (Platform for Privacy Preferences):"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Pragma:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Prefer:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Preference-Applied:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Proxy-Authenticate:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Proxy-Authorization:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Proxy-Connection:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Range:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Referer:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Retry-After:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Server.class:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Set-Cookie:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Sec-Fetch-Dest:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Sec-Fetch-Mode:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Sec-Fetch-Site:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Sec-Fetch-User:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["SLUG:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["SOAPAction:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Status-URI:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Strict-Transport-Security:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["TE:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Timeout:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Trailer:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Transfer-Encoding:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Upgrade:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["User-Agent:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Upgrade-Insecure-Requests:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Variant-Vary:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Vary:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["Via:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["WWW-Authenticate:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["X-Forwarded-For:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["X-Forwarded-Proto:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["X-Frame-Options:"] = &HeaderRequest::addToMapHttpHeader;
    _mapTokenListAction["X-XSS-Protection:"] = &HeaderRequest::addToMapHttpHeader;
}

std::string HeaderRequest::addToStartLine(string & token) {
    _startLineMethode = token;
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    if (_startLineVersion != "HTTP/1.1\r")
        throw HeaderRequest::headerException(strerror(errno));
    setMapTokenInformation();
    while(!_peg.checkIsEmpty())
        _peg.findToken(*this, _mapTokenListAction, 0);
    return std::string();
}

std::string HeaderRequest::addToMapHttpHeader(string& token) {
    _mapHttpHeaders.insert(std::make_pair(token, _peg.extractData('\n')));
    return std::string();
}

const string &HeaderRequest::getStartLineMethode() const {
    return _startLineMethode;
}

const string &HeaderRequest::getStartLineUrl() const {
    return _startLineURL;
}

const string &HeaderRequest::getStartLineVersion() const {
    return _startLineVersion;
}

const std::map<const std::string, const std::string> &HeaderRequest::getMapHttpHeaders() const {
    return _mapHttpHeaders;
}

HeaderRequest::headerException::headerException(const char * message) : _message(message) {}

HeaderRequest::headerException::~headerException() throw() {}

const char * HeaderRequest::headerException::what() const throw() { return _message.c_str(); }

HeaderRequest::headerException::headerException(const HeaderRequest::headerException & other) : _message(other._message) {}

HeaderRequest::headerException &HeaderRequest::headerException::operator=(const HeaderRequest::headerException &rhs) {
    this->_message = rhs._message;
    return *this;
}





HttpRequest::HttpRequest(Socket& socket, Server& server)
        : _socket(socket), _server(server), _bytesRecv(), _contentLength(), _buffer(), _headRequest(){
    recvMessage();
}

HttpRequest::~HttpRequest() {}

HttpRequest::HttpRequest(const HttpRequest & other)
        : _socket(other._socket), _server(other._server), _bytesRecv(other._bytesRecv),
          _contentLength(other._contentLength), _buffer(other._buffer), _headRequest(other._headRequest){}

HttpRequest &HttpRequest::operator=(const HttpRequest &rhs) {
    this->_socket = rhs._socket;
    this->_server = rhs._server;
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
    _headRequest = HeaderRequest(_buffer[0]);
    while(messageIsNotComplete()){
        recvData();
    }
}

void HttpRequest::recvData(){
    char buffer[1024 + 1];//@todo update value
    _bytesRecv += recv(_socket.getSocket(), buffer, 1024, 0);
    checkBytesRecv();
    buffer[_bytesRecv] ='\0';
    _buffer.push_back(buffer);
    std::cout << " client  >> " << _socket.getSocket() << " recv >>> \n" << buffer << _buffer.size() << _bytesRecv << "\n" << std::endl;
}

bool HttpRequest::messageIsNotComplete() {
    if (_contentLength == 0) {
        std::string contentLength = getValueHeader("Content-Length:");
        if (!contentLength.empty())
            _contentLength = std::atoi(contentLength.c_str());
    }
    return _bytesRecv < _contentLength;
}


void HttpRequest::checkBytesRecv() const {
    if (_bytesRecv == 0 )//close connection
        throw HttpRequest::httpRequestException(strerror(errno));
    if (_bytesRecv == -1)//bad request
        throw HttpRequest::httpRequestException(strerror(errno));
    if (_bytesRecv > 1024)//check headrs befor throw
        throw HttpRequest::httpRequestException(strerror(errno));
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

std::string HttpRequest::getUrl() {
    return _headRequest.getStartLineUrl();
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

HttpRequest::httpRequestException::httpRequestException(const char * message) : _message(message) {}

HttpRequest::httpRequestException::~httpRequestException() throw() {}

const char * HttpRequest::httpRequestException::what() const throw() { return _message.c_str(); }

HttpRequest::httpRequestException::httpRequestException(const HttpRequest::httpRequestException & other) : _message(other._message) {}

HttpRequest::httpRequestException &HttpRequest::httpRequestException::operator=(const HttpRequest::httpRequestException &rhs) {
    this->_message = rhs._message;
    return *this;
}
