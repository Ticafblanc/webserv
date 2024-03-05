//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP

#include "5-headers.hpp"


class CGI {
protected:
  Headers *_headers;
  int _fd[2];
  pid_t _pid;
  time_t  _time;

public:
  CGI();
  explicit CGI(Headers &headers);
  virtual ~CGI();
  CGI(const CGI& copy);
  CGI &operator=(const CGI& rhs);

  virtual void manager() = 0;
};

class CGIChild : public CGI{
public:
  CGIChild();
  explicit CGIChild(Headers &headers);
  ~CGIChild();

  CGIChild(const CGIChild& copy);
  CGIChild &operator=(const CGIChild& rhs);

  void manager();
};

class CGIParent : public CGI {
public:
  CGIParent();
  explicit CGIParent(Headers &headers);
  ~CGIParent();

  CGIParent(const CGIParent& copy);
  CGIParent &operator=(const CGIParent& rhs);

  void manager();
};



#endif // WEBSERV_CGI_HPP
