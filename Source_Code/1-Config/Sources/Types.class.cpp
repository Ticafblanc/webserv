//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#include <Source_Code/1-Config/Includes/Types.class.hpp>


Types::Types(const std::string& pathFile) : _peg(pathFile.c_str()), _mapMimeType(){
    parseBlocTypes();
}

Types::~Types() {}

Types::Types(const Types & other) : _peg(), _mapMimeType(other._mapMimeType){}

Types &Types::operator=(const Types &rhs) {
    this->_peg = rhs._peg;
    this->_mapMimeType = rhs._mapMimeType;
    return *this;
}

std::string Types::parseBlocTypes() {
    std::string value;
    std::string token;

    while (!_peg.checkIsEndOfBloc('}')) {
        value = _peg.extractData(0);
        token = _peg.extractData(';');
        _mapMimeType[token] = value;
    }
    return std::string();
}

const std::map<std::string, std::string> &Types::getMime() {
    return _mapMimeType;
}
