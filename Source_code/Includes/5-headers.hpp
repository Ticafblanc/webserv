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
  bool _isRequest;
  Client *_client;
  string _content;
  string _rawRequest;


  void getLines(string msg, vector<string> *lines);
  void getRequestLine(vector<string> lines);
  void getStatusLine(vector<string> lines);
  int getHeaderFileds(vector<string> lines);

public:
  Headers();
  Headers(Client & clt);
  Headers(const Headers &copy);
  ~Headers();
  Headers &operator=(const Headers &op);

  bool isRequest(void) const;
  void pushContent(string buffer);

  struct request_line getRequestLine(void) const;
  struct status_line getStatusLine(void) const;
  vector<struct header_field> getHeaderFields(void) const;
  string getContent(void) const;
  string getClientIP(void) const;
  string getPlainRequest(void) const;
};

ostream &operator<<(ostream &out, const Headers &hb);

#endif // WEBSERV_HEADERS_HPP
