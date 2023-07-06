//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#include <Source_Code/4-Headers/Includes/HttpBody.Aclass.hpp>

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

AHttpbody::AHttpbody(Config& config, Socket& socketClient)
        : _config(config), _socketClient(socketClient), _startLineVersion(), _mapHttpHeaders(){}

AHttpbody::~AHttpbody() {}

AHttpbody::AHttpbody(const AHttpbody & other)
        : _config(other._config), _socketClient(other._socketClient), _startLineVersion(other._startLineVersion), _mapHttpHeaders() {}

AHttpbody &AHttpbody::operator=(const AHttpbody &rhs) {
    if ( this != & rhs) {
        this->_config = rhs._config;
        this->_socketClient = rhs._socketClient;
        this->_startLineVersion = rhs._startLineVersion;
        this->_mapHttpHeaders = rhs._mapHttpHeaders;
    }
    return *this;
}




