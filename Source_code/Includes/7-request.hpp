//
// Created by Matthis DoQuocBao on 2024-02-22.
//
//bool isValidFirstLine();
//bool findRessource();
#ifndef WEBSERV_REQUEST_HPP
#define WEBSERV_REQUEST_HPP

#include "6-cgi.hpp"

class Request {
private:
  Headers *_headers;
  CGI *_cgi;
  Client* _client;
  bool _complete;
  typedef void (Request::*pManage)();
  pManage _manage;

  void _method();
  void _checkRessource(bool (*p)(const string &));
  void _head();
  void _get();
  void _delete();
  void _post();
  void _continuePost();

public:
  Request();
  Request(Headers &headers, CGI &cgi);
  Request(const Request &other);
  Request &operator=(const Request &other);
  ~Request();
  void manager();
  bool manageIsNull() const;
  void resetManage(pManage m = NULL);
};

#endif // WEBSERV_REQUEST_HPP
