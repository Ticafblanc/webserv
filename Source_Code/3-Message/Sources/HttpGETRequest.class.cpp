//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpGETRequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpGETRequest::HttpGETRequest(const AHttpMessage base, PegParser<AHttpMessage>& peg)
        : AHttpMessage(base), _peg(peg), _isCGI(false){}

HttpGETRequest::~HttpGETRequest() {}

//HttpGETRequest::HttpGETRequest(const HttpGETRequest & other)
//        : AHttpMessage(other), _queryString(other._queryString), _isCGI(other._isCGI){}

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
        _peg.setStringStream(_data);
        _peg.setMapTokenHeaderStartLine();
        _peg.findToken(*this, 0);
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
    return false;
}


/*
*====================================================================================
*|                                  Private Methode to recvMessage                         |
*====================================================================================
*/




bool HttpGETRequest::headerIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytesExchange(bytesExchange))
        return false;
    _data.append(_buffer.begin(), _buffer.end());
    _buffer.clear();
    if (_data.find("\r\n\r\n") == std::string::npos){
        _requestHeadersIsComplete = true;
        return false;
    }
    return true;
}

bool HttpGETRequest::checkErrorBytesExchange(std::size_t& bytesExchange){
    if (static_cast<int>(bytesExchange) == -1)
        return true;
    if (bytesExchange == 0 ) {
        setConnection(CLOSE);
        return true;
    }
    _totalBytesRecv += bytesExchange;
    if (static_cast<int>(_totalBytesRecv) > _config._clientMaxBodySize){
        setStatusCode(413);
        return true;
    }
    return false;
}

/*
*====================================================================================
*|                                  select Methode                                  |
*====================================================================================
*/

std::string HttpGETRequest::methodeGET(std::string & token) {
    (void)token;
    extractHeaderData();
    if (!checkIsAllowedMethode(1, 3, 5))
        throw Exception("Method GET Not Allowed ", 405);
    findRessource();
    if (_isCGI){
        if (launchChild(_pipeFdIn, _pipeFdOut, _pid,
                        setArgv("/usr/bin/php", _startLineURL),
                        setPhpEnv(_startLineMethode, _queryString, _mapHttpHeaders)))
            throw Exception("error to create child process", 500);
        close(_pipeFdIn[STDIN_FILENO]);
        close(_pipeFdOut[STDOUT_FILENO]);
    }
    return std::string();
}

std::string HttpGETRequest::methodePOST(std::string & token) {
    (void)token;
    extractHeaderData();
    if (!checkIsAllowedMethode(2, 3, 6))
        throw Exception("Method Post Not Allowed ", 405);
    findRessource();
    _requestBodyIsComplete = false;
    if (_isCGI){
        if (launchChild(_pipeFdIn, _pipeFdOut, _pid,
                        setArgv("/usr/bin/php", _startLineURL),
                        setPhpEnv(_startLineMethode, _queryString, _mapHttpHeaders)))
            throw Exception("error to create child process", 500);
        close(_pipeFdIn[STDIN_FILENO]);
        close(_pipeFdOut[STDOUT_FILENO]);
    }
    return std::string();
}

std::string HttpGETRequest::methodeDELETE(std::string & token) {
    (void)token;
    extractHeaderData();
    if (!checkIsAllowedMethode(4, 5, 6))
        throw Exception("Method GET Not Allowed ", 405);
    findRessource();
    return std::string();
}



void HttpGETRequest::extractHeaderData() {
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty() && !_requestHeadersIsComplete)
        _peg.findToken(*this,  0);
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
    int icontentLength = 0 ;
    if (!_isChunked) {
        std::string contentLength = getValueHeader("Content-Length:");
        if (!contentLength.empty())
            icontentLength = std::atoi(contentLength.c_str());
        if (static_cast<int>(icontentLength) > _config._clientMaxBodySize)
            throw Exception("Request body size exceeds the maximum limit", 413);
    }
    return std::string();
}

std::string HttpGETRequest::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    _startLineMethode = token;
    std::string chunked = getValueHeader("Transfer-Encoding:");
    if (chunked == "chunked" )
        _isChunked = true;
    return std::string();
}

std::string HttpGETRequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    addMapHttpHeaders(std::make_pair(token, data));
    return std::string();
}

void HttpGETRequest::addMapHttpHeaders(const std::pair<std::string, std::string> &pairHeader){
    _mapHttpHeaders.insert(pairHeader);
}

std::string HttpGETRequest::getValueHeader(const std::string & token) {
    const std::map<std::string, std::string>::iterator it = _mapHttpHeaders.find(token);
    if (it != _mapHttpHeaders.end())
        return it->second;
    return std::string();
}

std::string HttpGETRequest::endHeader(std::string& token) {
    (void)token;
    _data =  _data.substr(_data.find("\r\n\r\n") + 4);
    _requestHeadersIsComplete = true;
    return "";
}



