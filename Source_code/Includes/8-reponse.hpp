//
// Created by Matthis DoQuocBao on 2024-02-25.
//

#ifndef WEBSERV_REPONSE_HPP
#define WEBSERV_REPONSE_HPP

#include "7-request.hpp"

class Response {
private:
  Headers *_headers;
  Client* _client;

public:
  Response();
  Response(Headers &headers);
  Response(const Response &other);
  Response &operator=(const Response &other);
  ~Response();
  void manager();
};

#endif // WEBSERV_REPONSE_HPP
