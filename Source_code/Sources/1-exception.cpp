//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/1-exception.hpp"

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

string ErrnoException::print() {
  string str(_msg + "  [" + _errno + "]");
  cerr << "\033[1m\033[31mERROR \033[0m: " << str << endl;
  return str;
}

Exception::Exception(const string &msg) throw()
    : ErrnoException(msg), _sd(), _errorPage() {}

Exception::Exception(const string &msg, const int &sd,
                     const string &errorPage) throw()
    : ErrnoException(msg), _sd(sd), _errorPage(errorPage) {}

Exception::Exception(const Exception &e) throw()
    : ErrnoException(e), _sd(e._sd), _errorPage(e._errorPage) {}

Exception &Exception::operator=(const Exception &e) throw() {
  if (this != &e) {
    ErrnoException::operator=(e);
    _sd = e._sd;
    _errorPage = e._errorPage;
  }
  return *this;
}
int Exception::getSd() const { return _sd; }
const string &Exception::getErrorPage() const { return _errorPage; }

Exception::~Exception() throw() {}

string Exception::print()  {
  ostringstream oss;
  oss << "Socket [" << _sd << "] " <<  ErrnoException::print() << endl;
  cerr << "\033[1m\033[31mClient \033[0m: " << _sd << " code return ["
       << _errorPage << "]" << endl;
  return oss.str();
}
