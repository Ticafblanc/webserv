//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#include <Source_Code/0-Main/Includes/Exception.hpp>

Exception::Exception(const char * message)
        : _message(message) {}

Exception::~Exception() throw() {}

const char * Exception::what() const throw() { return _message.c_str(); }

Exception::Exception(const Exception & other) : _message(other._message) {}

Exception &Exception::operator=(const Exception &rhs) {
    this->_message = rhs._message;
    return *this;
}
