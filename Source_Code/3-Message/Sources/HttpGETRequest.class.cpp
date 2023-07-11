//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpGETRequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpGETRequest::HttpGETRequest(const AHttpMessage& base, const std::string & data)
        : AHttpMessage(base), _peg(data), _isCGI(false){}

HttpGETRequest::~HttpGETRequest() {}

HttpGETRequest::HttpGETRequest(const HttpGETRequest & other)
        : AHttpMessage(other), _queryString(other._queryString), _isCGI(other._isCGI){}

HttpGETRequest &HttpGETRequest::operator=(const HttpGETRequest &rhs) {
    if ( this != & rhs) {
        AHttpMessage::operator=(rhs);
        this->_queryString = rhs._queryString;
        this->_isCGI = rhs._isCGI;
    }
    return *this;
}

/*
*====================================================================================
*|                                  Public Methode Override                         |
*====================================================================================
*/

bool HttpGETRequest::continueManageEvent() {
    try {
        extractData();
        if (!checkIsAllowedMethode(1, 3, 5))
            throw Exception("Method GET Not Allowed ", 405);
        findRessource();
        if (_isCGI) {
            if (!startCgi())
                throw Exception("error to create child process", 500);
        } else {
            if (pipe(_pipeFdOut) == -1)
                throw Exception("error to create pipe", 500);
            //open and write in fd out
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
    _methode = new HttpBodyReponse(*this);
    return false;
}


/*
*====================================================================================
*|                                  select Methode                                  |
*====================================================================================
*/


void HttpGETRequest::extractData() {
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty() && !_requestHeadersIsComplete)
        _peg.findToken(*this,  0);
}

bool HttpGETRequest::startCgi() {
    if (launchChild(_pipeFdIn, _pipeFdOut, _pid,
                    setArgv("/usr/bin/php", _startLineURL),
                    setPhpEnv(_startLineMethode, _queryString, _mapHttpHeaders)))
        return false;
    close(_pipeFdIn[STDIN_FILENO]);
    close(_pipeFdIn[STDOUT_FILENO]);
    close(_pipeFdOut[STDOUT_FILENO]);
    return true;
}

/*
*====================================================================================
*|                                  Information Methode                             |
*====================================================================================
*/

std::string HttpGETRequest::Host(std::string & token){
    addToMapHttpHeader(token);
    std::string serverName = _mapHttpHeaders.find(token)->second;
    if (serverName.empty())
        throw Exception("No host in request", 400);
    std::string serverToken = _socketClient.getServer()->findServerName(serverName);
    findBestConfig(_config._mapTokenVectorUriConfig.find(serverToken)->second);
    return std::string();
}

void HttpGETRequest::findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig) {
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

void HttpGETRequest::findRessource() {
    if (!isExec(_startLineURL)) {
        if (!isFile(_startLineURL)) {
            if (!isDirectory(_startLineURL) && !setIndex()) {
                if (!_config._autoindex) {
                    throw Exception("root/Uri not found", 404);
                } else {
                    if (pipe(_pipeFdOut) == -1)
                        throw Exception("error to create pipe", 500);
                    autoIndexToHtml();
                }
            }
        }
    }else{
        if (!checkIsPHP())
            throw Exception("exec is not PHP file", 403);
        _isCGI = true;
    }
}

bool HttpGETRequest::setIndex(){
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

bool HttpGETRequest::checkIsPHP() {
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

std::string HttpGETRequest::ContentLength(std::string &token) {
    addToMapHttpHeader(token);
    return std::string();
}

std::string HttpGETRequest::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    return std::string();
}

std::string HttpGETRequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    addMapHttpHeaders(std::make_pair(token, data));
    return std::string();
}

std::string HttpGETRequest::endHeader(std::string& token) {
    (void)token;
    _data =  _data.substr(_data.find("\r\n\r\n") + 4);
    _requestHeadersIsComplete = true;
    return "";
}



