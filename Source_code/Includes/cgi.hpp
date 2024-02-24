//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP
#include "configuration.hpp"
#include "headers.hpp"
#include "utils.hpp"
extern char** envp;
class CGI {
private:
  string _cgi_path;
  string _ressource_path;
  Headers _request;
  Server &_conf;
  Location &_location;
  map<string, string> _getParams();
  string _getQueryString();
  char **_convertParams(map<string, string> args);
  void _freeArgs(char **args);
  char *_newStr(string source);
  string _execCGI(char **args);
  char **_getExecArgs();
  string _getScriptName();
  string _removeQueryArgs(string query);

public:
  CGI();
  CGI(string cgi_path, string ressource_path, Headers request,
      Server &conf, Location &location);
  ~CGI();
  string getOutput();
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
