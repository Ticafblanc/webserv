//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpDELETERequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpDELETERequest::HttpDELETERequest(const AHttpMessage& base, const std::string & data)
        : AHttpMessage(base), _peg(data){}

HttpDELETERequest::~HttpDELETERequest() {}

HttpDELETERequest::HttpDELETERequest(const HttpDELETERequest & other)
        : AHttpMessage(other) {}

HttpDELETERequest &HttpDELETERequest::operator=(const HttpDELETERequest &rhs) {
    if ( this != & rhs) {
        AHttpMessage::operator=(rhs);
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode Override                         |
*====================================================================================
*/

bool HttpDELETERequest::continueManageEvent() {

    try {
        extractData();
        if (!checkIsAllowedMethode(1, 3, 5))
            throw Exception("Method GET Not Allowed ", 405);
        findRessource();

        return true;
    }catch (Exception& e) {
        _config._accessLog.failure();
        _config._errorLog.writeMessageLogFile(e.what());
        setStatusCode(e.getCode());
    }catch (std::exception& e){
        _config._accessLog.failure();
        _config._errorLog.writeMessageLogFile(e.what());
        setStatusCode(400);
    }
    _methode = new HttpReponse(*this);
    return false;
}

/*
*====================================================================================
*|                                  select Methode                                  |
*====================================================================================
*/


void HttpDELETERequest::extractData() {
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty() && !_requestHeadersIsComplete)
        _peg.findToken(*this,  0);
}

/*
*====================================================================================
*|                                  Information Methode                             |
*====================================================================================
*/

std::string HttpDELETERequest::Host(std::string & token){
    addToMapHttpHeader(token);
    std::string serverName = _mapHttpHeaders.find(token)->second;
    if (serverName.empty())
        throw Exception("No host in request", 400);
    std::string serverToken = _socketClient.getServer()->findServerName(serverName);
    findBestConfig(_config._mapTokenVectorUriConfig.find(serverToken)->second);
    return std::string();
}

void HttpDELETERequest::findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig) {
    std::vector<std::pair<std::string, Config> >::iterator bestLocation = UriConfig.end() - 1;
    for (std::vector<std::pair<std::string, Config> >::iterator itvec = UriConfig.begin();
         itvec != UriConfig.end(); ++itvec) {
        if (_startLineURL.find(itvec->first) == 0 && itvec->first.length() > bestLocation->first.length())
            bestLocation = itvec;
    }
    _startLineURL = bestLocation->second._root +
                    _startLineURL.substr(bestLocation->first.length() - 1);
    setConfig(bestLocation->second);
}

void HttpDELETERequest::findRessource() {
    if (!isFile(_startLineURL)) {
        if (!isDirectory(_startLineURL)) {
            if (!_config._autoindex) {
                throw Exception("root/Uri not found", 404);
            } else {
                if (pipe(_pipeFdOut) == -1)
                    throw Exception("error to create pipe", 500);
                autoIndexToHtml();
                _statusCode = 200;
            }
        } else {
            if ( removeDirectory(_startLineURL))
                _statusCode = 204;
        }
    } else {
        if (removeFile(_startLineURL))
            _statusCode = 204;
    }
}

std::string HttpDELETERequest::ContentLength(std::string &token) {
    addToMapHttpHeader(token);
    return std::string();
}

std::string HttpDELETERequest::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    return std::string();
}

std::string HttpDELETERequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    addMapHttpHeaders(std::make_pair(token, data));
    return std::string();
}

std::string HttpDELETERequest::endHeader(std::string& token) {
    (void)token;
    _data =  _data.substr(_data.find("\r\n\r\n") + 4);
    _requestHeadersIsComplete = true;
    return "";
}



