//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpPOSTRequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpPOSTRequest::HttpPOSTRequest(const AHttpMessage& base, const std::string & data)
        : AHttpMessage(base), _peg(data), _isCGI(false){}

HttpPOSTRequest::~HttpPOSTRequest() {}

HttpPOSTRequest::HttpPOSTRequest(const HttpPOSTRequest & other)
        : AHttpMessage(other), _isCGI(other._isCGI){}

HttpPOSTRequest &HttpPOSTRequest::operator=(const HttpPOSTRequest &rhs) {
    if ( this != & rhs) {
        AHttpMessage::operator=(rhs);
        this->_isCGI = rhs._isCGI;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode Override                         |
*====================================================================================
*/

bool HttpPOSTRequest::continueManageEvent() {
    try {
        extractData();
        if (!checkIsAllowedMethode(2, 3, 6))
            throw Exception("Method Post Not Allowed ", 405);
        findRessource();
        if (_isCGI) {
            if (!startCgi())
                throw Exception("error to create child process", 500);
        } else {
            if (pipe(_pipeFdOut) == -1)
                throw Exception("error to create pipe", 500);
            //open and write data in
        }
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
    _methode = new HttpBodyRequest(*this, _peg.getStr());
    return false;
}


/*
*====================================================================================
*|                                  select Methode                                  |
*====================================================================================
*/


void HttpPOSTRequest::extractData() {
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty() && !_requestHeadersIsComplete)
        _peg.findToken(*this,  0);
}

bool HttpPOSTRequest::startCgi() {
    if (launchChild(_pipeFdIn, _pipeFdOut, _pid,
                    setArgv("/usr/bin/php", _startLineURL),
                    setPhpEnv(_startLineMethode, "", _mapHttpHeaders)))
        return false;
    close(_pipeFdIn[STDIN_FILENO]);
    close(_pipeFdOut[STDOUT_FILENO]);
    return true;
}

/*
*====================================================================================
*|                                  Information Methode                             |
*====================================================================================
*/

std::string HttpPOSTRequest::Host(std::string & token){
    addToMapHttpHeader(token);
    std::string serverName = _mapHttpHeaders.find(token)->second;
    if (serverName.empty())
        throw Exception("No host in request", 400);
    std::string serverToken = _socketClient.getServer()->findServerName(serverName);
    findBestConfig(_config._mapTokenVectorUriConfig.find(serverToken)->second);
    return std::string();
}

void HttpPOSTRequest::findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig) {
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

void HttpPOSTRequest::findRessource() {
    if (!isExec(_startLineURL)) {
        if (!isFile(_startLineURL)) {
            if (!isDirectory(_startLineURL) && !setIndex()) {
                if (!_config._autoindex) {
                    throw Exception("root/Uri not found", 404);
                }
            }
        }
    }else{
        if (!checkIsPHP())
            throw Exception("exec is not PHP file", 403);
        _isCGI = true;
    }
}

bool HttpPOSTRequest::setIndex(){
    for (std::set<std::string>::iterator  itSet = _config._index.begin();
         itSet != _config._index.end() ; ++itSet) {
        std::string Url = _startLineURL;
        Url += "/" + *itSet;
        if (isFile(Url)){
            _startLineURL = Url;
            return true;
        }
    }
    return false;
}

bool HttpPOSTRequest::checkIsPHP() {
    std::string & url = _startLineURL;
    std::size_t slashPos = _startLineURL.find_last_of('/');
    std::size_t dotPos = _startLineURL.find_last_of('.');
    if (dotPos != std::string::npos && dotPos < slashPos) {
        if (_startLineURL.substr(dotPos + 1) == "php")
            return isExec(_startLineURL);
    }
    return false;
}

std::string HttpPOSTRequest::ContentLength(std::string &token) {
    addToMapHttpHeader(token);
    if (!_isChunked) {
        std::string contentLength = getValueHeader("Content-Length:");
        if (!contentLength.empty())
            _contentLength = std::atoi(contentLength.c_str());
        if (static_cast<int>(_contentLength) > _config._clientMaxBodySize)
            throw Exception("Request body size exceeds the maximum limit", 413);
    }
    return std::string();
}

std::string HttpPOSTRequest::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    _startLineMethode = token;
    std::string chunked = getValueHeader("Transfer-Encoding:");
    if (chunked == "chunked" )
        _isChunked = true;
    return std::string();
}

std::string HttpPOSTRequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    addMapHttpHeaders(std::make_pair(token, data));
    return std::string();
}

std::string HttpPOSTRequest::endHeader(std::string& token) {
    (void)token;
    _data =  _data.substr(_data.find("\r\n\r\n") + 4);
    _requestHeadersIsComplete = true;
    return "";
}



