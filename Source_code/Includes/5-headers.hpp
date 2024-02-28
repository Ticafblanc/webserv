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
  istringstream _header;

  bool extractData();
  bool extractFirstLine() ;

public:
  Headers();
  explicit Headers(Client & clt);
  Headers(const Headers &copy);
  ~Headers();
  Headers &operator=(const Headers &op);

  void parse();
  vector<char*> getCgiEnv();

  vecStr &getFirstLine();
  void setFirstLine(const int & pos, const string &value);
  mapStrStr &getHeaderFields();
  Client *getClient() ;
};

ostream &operator<<(ostream &out, const Headers &hb);

#endif // WEBSERV_HEADERS_HPP
