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
        if (_isCGI) {
            if (!startCgi())
                throw Exception("error to create child process", 500);
            _methode = new HttpBodyReponse(*this);
            return false;
        } else {
            if (!extractFileToBuffer())
                throw Exception("error to extract file", 500);
            _mapHttpHeaders["Content-Length:"] = intToString(_body.size());
            _mapHttpHeaders["Content-Type:"] = _config._mapMimeType.at(_startLineURL.substr(_startLineURL.find_last_of('.') + 1));
            _statusCode = 200;
            _methode = new HttpHeadersReponse(*this);
        }
        return true;
    }catch (Exception& e) {
        _config._accessLog.failure();
        _config._errorLog.writeMessageLogFile(e.what());
        setStatusCode(e.getCode());
        _methode = new HttpBodyReponse(*this);
        return true;
    }catch (std::exception& e){
        _config._accessLog.failure();
        _config._errorLog.writeMessageLogFile(e.what());
        setStatusCode(400);
        _methode = new HttpBodyReponse(*this);
        return true;

    }
    return false;
}


/*
*====================================================================================
*|                                  select Methode                                  |
*====================================================================================
*/



bool HttpGETRequest::extractFileToBuffer() {
    std::ifstream is(_startLineURL.c_str(), std::ios::binary | std::ios::in);
    if (!is.is_open())
        return false;
    is.seekg(0, std::ios::end);
    _contentLength = is.tellg();
    is.seekg(0, std::ios::beg);
    _body.clear();
    _body.resize(_contentLength);
    is.read(_body.data(), _body.size());
//    std::cout <<_body.data()  << " size "<< _contentLength<< std::endl;
    return true;
}




