//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/3-Message/Includes/HttpHeadersRequest.class.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

HttpHeadersRequest::HttpHeadersRequest(Config& config, Socket& socketClient)
        : AHttpMessage(config, socketClient), _buffer(config._clientHeaderBufferSize), _totalBytesRecv(), _isCGI(false) {}

HttpHeadersRequest::~HttpHeadersRequest() {}

HttpHeadersRequest::HttpHeadersRequest(const HttpHeadersRequest & other)
        : AHttpMessage(other), _totalBytesRecv(), _isCGI(false){}

HttpHeadersRequest &HttpHeadersRequest::operator=(const HttpHeadersRequest &rhs) {
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

bool HttpHeadersRequest::continueManageEvent() {
    recvData(_socketClient.getSocket(), _buffer, *this,
             &HttpHeadersRequest::headerIsNotComplete);
    if (_requestHeadersIsComplete) {
        try {
            _requestHeadersIsComplete = false;
            _peg.setStringStream(_header);
            _peg.setMapTokenHeaderStartLine();
            _peg.findToken(*this, 0);
            return true;
        }catch (Exception& e) {
            _config._accessLog.failure();
            _config._errorLog.writeMessageLogFile(e.what());
            setStatusCode(e.getCode());
            _methode = new HttpBodyReponse(*this);
        }catch (std::exception& e){
            _config._accessLog.failure();
            _config._errorLog.writeMessageLogFile(e.what());
            setStatusCode(400);
            _methode = new HttpBodyReponse(*this);
        }
    }
    return false;
}


/*
*====================================================================================
*|                                  Private Methode to recvMessage                         |
*====================================================================================
*/

bool HttpHeadersRequest::headerIsNotComplete(std::size_t& bytesExchange){
    if (checkErrorBytesExchange(bytesExchange))
        return false;
    _header.append(_buffer.begin(), _buffer.end());
    _buffer.clear();
    std::size_t doubleCRLFpos = _header.find("\r\n\r\n");
    if (doubleCRLFpos != std::string::npos){
        _body.assign(_header.begin() + doubleCRLFpos + 4, _header.end());
        _requestHeadersIsComplete = true;
        return false;
    }
    return true;
}

bool HttpHeadersRequest::checkErrorBytesExchange(std::size_t& bytesExchange){
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

std::string HttpHeadersRequest::methodeGET(std::string & token) {
    (void)token;
    extractHeaderData();
    extractData();
    if (!checkIsAllowedMethode(1, 3, 5))
        throw Exception("Method GET Not Allowed ", 405);
    findRessource();
    if (_isCGI) {
        if (!startCgi())
            throw Exception("error to create child process", 500);
        _methode = new HttpBodyReponse(*this);
        return false;
    } else {

    _methode = new HttpGETRequest(*this, _peg.getStr());
    return std::string();
}

std::string HttpHeadersRequest::methodePOST(std::string & token) {
    (void)token;
    extractHeaderData();
    _methode = new HttpPOSTRequest(*this, _peg.getStr());
    return std::string();
}

std::string HttpHeadersRequest::methodeDELETE(std::string & token) {
    (void)token;
    extractHeaderData();
    _methode = new HttpDELETERequest(*this, _peg.getStr());
    return std::string();
}

void HttpHeadersRequest::extractHeaderData() {
    _startLineURL = _peg.extractData(' ');
    _startLineVersion = _peg.extractData('\n');
    _startLineVersion.erase(_startLineVersion.size() - 1);
    if (_startLineVersion != "HTTP/1.1")
        throw Exception("Version protocole not supprted", 505);
}

/*
*====================================================================================
*|                                  Information Methode                             |
*====================================================================================
*/

void HttpHeadersRequest::extractData() {
    _peg.setMapTokenHeadersInformation();
    while(!_peg.checkIsEmpty() && !_requestHeadersIsComplete) {
        _peg.findToken(*this, 0);
    }
}


std::string HttpHeadersRequest::Host(std::string & token){
    addToMapHttpHeader(token);
    std::string serverName = _mapHttpHeaders.find(token)->second;
    if (serverName.empty()) {
        throw Exception("No host in request", 400);
    }
    std::string serverToken = _socketClient.getServer()->findServerName(serverName);
    if (serverToken.empty())
        throw Exception("Host not found", 404);
    findBestConfig(_config._mapTokenVectorUriConfig.find(serverToken)->second);
    redirection();
    return std::string();
}

void HttpHeadersRequest::findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig) {
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

void HttpHeadersRequest::findRessource() {
    if (!isExec(_startLineURL)) {
        if (!isFile(_startLineURL)) {
            if (!isDirectory(_startLineURL) || !setIndex()) {
                if (!_config._autoindex) {
                    throw Exception("root/Uri not found", 404);
                } else {
                    if (pipe(_pipeFdOut) == -1)
                        throw Exception("error to create pipe", 500);
//                    autoIndexToHtml();
                }
            }
        }
    }else{
        if (!checkIsPHP())
            throw Exception("exec is not PHP file", 403);
        _isCGI = true;
    }
}

bool HttpHeadersRequest::setIndex(){
    for (std::set<std::string>::iterator  itSet = _config._index.begin();
         itSet != _config._index.end() ; ++itSet) {
        std::string Url = _startLineURL;
        Url += *itSet;
        if (isFile(Url)){
            _startLineURL = Url;
            return true;
        }
    }
    return false;
}

bool HttpHeadersRequest::checkIsPHP() {
//    std::string & url = _startLineURL;
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

std::string HttpHeadersRequest::ContentLength(std::string &token) {
    addToMapHttpHeader(token);
    return std::string();
}

std::string HttpHeadersRequest::TransfereEncoding(std::string &token) {
    addToMapHttpHeader(token);
    return std::string();
}

std::string HttpHeadersRequest::addToMapHttpHeader(std::string& token) {
    _peg.deleteMapToken(token);
    std::string data = _peg.extractData('\n');
    data.erase(data.size() - 1);
    addMapHttpHeaders(std::make_pair(token, data));
    return std::string();
}

std::string HttpHeadersRequest::endHeader(std::string& token) {
    (void)token;
//    _body =  _body.substr(_body.find("\r\n\r\n") + 4);
    _requestHeadersIsComplete = true;
    return "";
}

bool HttpHeadersRequest::startCgi() {
    if (launchChild(_pipeFdIn, _pipeFdOut, _pid,
                    setArgv("/usr/bin/php", _startLineURL),
                    setPhpEnv(_startLineMethode, _queryString, _mapHttpHeaders)))
        return false;
    close(_pipeFdIn[STDIN_FILENO]);
    close(_pipeFdOut[STDOUT_FILENO]);
    return true;
}

