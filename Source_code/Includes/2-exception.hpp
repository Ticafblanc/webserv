//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include "1-utils.hpp"

class ErrnoException : public exception {
protected:
  string _msg;
  string _errno;

public:
  ErrnoException(const string &msg) throw();

  ErrnoException(const ErrnoException &) throw();
  ErrnoException &operator=(const ErrnoException &) throw();
  virtual ~ErrnoException() throw();
  virtual const char *what() const throw();
  const char *whatErrno() const throw();
  void print() const;
};

class Exception : public ErrnoException {
private:
  int _sd;
  string _errorPage;

public:
  Exception(const string &msg) throw();
  Exception(const string &msg, const int &sd,
            const string &errorPage) throw();
  Exception(const Exception &) throw();
  Exception &operator=(const Exception &) throw();
  virtual ~Exception() throw();
  void print() const;
  int getSd() const;
  const string &getErrorPage() const;
};

#endif // WEBSERV_PARSER_HPP
