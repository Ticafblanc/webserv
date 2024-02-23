//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CGI_HPP
#define WEBSERV_CGI_HPP
#include "configuration.hpp"
#include "headers.hpp"
#include "main.hpp"
#include "utils.hpp"

class CGI {
private:
  std::string _cgi_path;
  std::string _ressource_path;
  Headers _request;
  Configuration::server _conf;
  Configuration::location _location;
  std::map<std::string, std::string> _getParams();
  std::string _getQueryString();
  char **_convertParams(std::map<std::string, std::string> args);
  void _freeArgs(char **args);
  char *_newStr(std::string source);
  std::string _execCGI(char **args);
  char **_getExecArgs();
  std::string _getScriptName();
  std::string _removeQueryArgs(std::string query);

public:
  CGI();
  CGI(std::string cgi_path, std::string ressource_path, Headers request,
      Configuration::server conf, Configuration::location location);
  ~CGI();
  std::string getOutput();
};

class CGIException : public std::exception {
private:
  std::string _msg;

public:
  CGIException(std::string message = "Unable to execute CGI.")
      : _msg(message){};
  ~CGIException() throw(){};
  const char *what() const throw() { return (_msg.c_str()); };
};

#endif // WEBSERV_CGI_HPP
