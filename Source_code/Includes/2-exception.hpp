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
  virtual ~ErrnoException() throw() ;
  virtual const char *what() const throw();
  const char *whatErrno() const throw() ;
  void print()const ;
};

#endif // WEBSERV_PARSER_HPP
