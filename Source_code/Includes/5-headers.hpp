//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_HEADERS_HPP
#define WEBSERV_HEADERS_HPP

#include "4-socket.hpp"

class Headers {
private:
  vecStr _firstLine;
  mapStrStr _headerFields;
  Client *_client;

  bool extractData();

public:
  Headers();
  explicit Headers(Client & clt);
  Headers(const Headers &copy);
  ~Headers();
  Headers &operator=(const Headers &op);

  void parse();

  vecStr &getFirstLine();
  mapStrStr &getHeaderFields();
  Client *getClient() ;
};

ostream &operator<<(ostream &out, const Headers &hb);

#endif // WEBSERV_HEADERS_HPP
