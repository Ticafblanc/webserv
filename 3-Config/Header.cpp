//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#include "Header.hpp"

/*
*====================================================================================
*|                                       HeaderReponse                              |
*====================================================================================
*/

HeaderReponse::HeaderReponse() : _startLineVersion("HTTP/1.1"), _startLineStatusCode(), _mapHttpHeaders() {}

HeaderReponse::HeaderReponse(const HeaderReponse & other)
: _startLineVersion(other._startLineVersion), _startLineStatusCode(other._startLineStatusCode),
_mapHttpHeaders(other._mapHttpHeaders) {}

HeaderReponse &HeaderReponse::operator=(const HeaderReponse & rhs) {
    this->_startLineVersion = rhs._startLineVersion;
    this->_startLineStatusCode = rhs._startLineStatusCode;
    this->_mapHttpHeaders = rhs._mapHttpHeaders;
    return *this;
}

void HeaderReponse::setStartLineStatusCode(std::string & statusCode) {
    _startLineStatusCode = statusCode;
}

void HeaderReponse::setMapHttpHeaders(string &token, string &value) {
    _mapHttpHeaders[token] = value;
}

const std::string &HeaderReponse::getHeaderReponse() {
    _startLineVersion += " ";
    _startLineVersion += _startLineStatusCode;
    _startLineVersion += "\r\n";
    for (std::map<std::string, std::string>::iterator  i = _mapHttpHeaders.begin();
    i != _mapHttpHeaders.end(); ++i) {
        _startLineVersion += i->first;
        _startLineVersion += " ";
        _startLineVersion += i->second;
        _startLineVersion += "\r\n";
    }
    _startLineVersion += "\r\n";
    return _startLineVersion;
}
/*
*====================================================================================
*|                                       HeaderRequest                                     |
*====================================================================================
*/

HeaderRequest::HeaderRequest()
: _peg(), _startLineMethode(), _startLineURL(), _startLineVersion(), _mapTokenListAction(){}

HeaderRequest::HeaderRequest(string &message)
: _peg(message), _startLineMethode(), _startLineURL(), _startLineVersion(), _mapTokenListAction(){
    setMapTokenStartLine();
    _peg.findToken(*this, _mapTokenListAction, 0);
}

HeaderRequest::~HeaderRequest() {

}

HeaderRequest::HeaderRequest(const HeaderRequest &) {

}

HeaderRequest &HeaderRequest::operator=(const HeaderRequest &) {
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
    _mapTokenListAction["Content-Location:"] = &HeaderRequest::addToMapHttpHeader;
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
    _mapTokenListAction["Location:"] = &HeaderRequest::addToMapHttpHeader;
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
    _mapTokenListAction["Server:"] = &HeaderRequest::addToMapHttpHeader;
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
    _peg.findToken(*this, _mapTokenListAction, 0);
    return std::string();
}

std::string HeaderRequest::addToMapHttpHeader(string &token) {
    _mapHttpHeaders[token] = _peg.extractData('\n');
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

const std::map<std::string, std::string> &HeaderRequest::getMapHttpHeaders() const {
    return _mapHttpHeaders;
}



