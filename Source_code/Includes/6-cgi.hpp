//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP

#include "5-headers.hpp"


class CGI {
private:
  Headers *_headers;
  int _fd[2];
  pid_t _pid;
  time_t  _time;


  map<string, string> _getParams();
  string _getQueryString();
  char **_convertParams(map<string, string> args);
  void _freeArgs(char **args);
  char *_newStr(string source);
  char **_getExecArgs();
  string _getScriptName();
  string _removeQueryArgs(string query);

public:
  CGI();
  CGI(Headers &headers);
  ~CGI();

  bool launchChild();
};

class CGIException : public exception {
private:
  string _msg;

public:
  CGIException(string message = "Unable to execute CGI.")
      : _msg(message){};
  ~CGIException() throw(){};
  const char *what() const throw() { return (_msg.c_str()); };
};

#endif // WEBSERV_CGI_HPP
