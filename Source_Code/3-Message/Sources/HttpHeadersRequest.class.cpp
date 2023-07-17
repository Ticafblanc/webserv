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
        : AHttpMessage(config, socketClient), _buffer(config._clientHeaderBufferSize), _totalBytesRecv() {}

HttpHeadersRequest::~HttpHeadersRequest() {}

HttpHeadersRequest::HttpHeadersRequest(const HttpHeadersRequest & other)
        : AHttpMessage(other), _totalBytesRecv(){}

HttpHeadersRequest &HttpHeadersRequest::operator=(const HttpHeadersRequest &rhs) {
    if ( this != & rhs) {
        AHttpMessage::operator=(rhs);
        this->_header = rhs._header;
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
        _body = _header.substr(doubleCRLFpos);
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
    std::cout <<"start     >>>>   " << _startLineURL <<std::endl;

}






