//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/2-exception.hpp"

ErrnoException::ErrnoException(const string &msg) throw()
    : _msg(msg), _errno(strerror(errno)) {}

ErrnoException::ErrnoException(const ErrnoException &e) throw()
    : _msg(e._msg) {}
ErrnoException &ErrnoException::operator=(const ErrnoException &e) throw() {
  if (this != &e) {
    _msg = e._msg;
  }
  return *this;
}

ErrnoException::~ErrnoException() throw() {}

const char *ErrnoException::what() const throw() { return _msg.c_str(); }

const char *ErrnoException::whatErrno() const throw() { return _errno.c_str(); }

void ErrnoException::print() const {
  cerr << "\033[1m\033[31mERROR \033[0m: " << _msg << "  [" << _errno << "]"
       << endl;
}
