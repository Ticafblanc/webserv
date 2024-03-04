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
  string _boundary;
  Client *_client;
  istringstream _header;
  bool _complete;
  mapStrStr _statusCode;
  mapStrStr _mimeType;

  void _setMapStatus();
  void _setMapMimeType();
  void _extractData();
  void _extractFirstLine();
  void _extractUri();
  void _extractQueryString();
  void _extractPath();
  void _extractExt();

public:
  Headers();
  explicit Headers(Client &clt);
  Headers(const Headers &copy);
  ~Headers();
  Headers &operator=(const Headers &op);

  void parse();
  vector<char *> getCgiEnv();
  vector<char *> getCgiArg();

  vecStr &getFirstLine();
  void setFirstLine(const int &pos, const string &value);
  void setHead();
  void setGet();
  void setDelete();
  void setPost();

  void setStatus(const string &value);
  mapStrStr &getHeaderFields();
  size_t getContentLength() ;
  void setHeaderFields(const string &token, const string &value);
  string getHeaderField(const string &token);
  Client *getClient();

  bool isCloseRequest();
  bool isDataForm() ;
  bool isValidMimeType();
};

ostream &operator<<(ostream &out, const Headers &hb);

#endif // WEBSERV_HEADERS_HPP
