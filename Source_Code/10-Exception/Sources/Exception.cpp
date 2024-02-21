//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#include "../Includes/Exception.hpp"

Exception::Exception(const char * message, int code)
        : _message(message), _code(code){}

Exception::~Exception() throw() {}

const char * Exception::what() const throw() { return _message.c_str(); }

Exception::Exception(const Exception & other) throw()
        : _message(other._message), _code(other._code) {}

Exception &Exception::operator=(const Exception &rhs) {
    this->_message = rhs._message;
    this->_code = rhs._code;
    return *this;
}

int Exception::getCode() const {
    return _code;
}
