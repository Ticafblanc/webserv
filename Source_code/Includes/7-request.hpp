//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_REQUEST_HPP
#define WEBSERV_REQUEST_HPP

#include "6-cgi.hpp"

class Request {
private:
  Headers *_headers;
  CGI *_cgi;
  string _ressource;
  Headers _header_block;
  Server _conf;
  Location _location;
  string _get(string ressource_path,
                   map<string, string> headers,
                   bool send_body = true);
  string _head(string ressource_path,
                    map<string, string> headers);
  string _post(string ressource_path,
                    map<string, string> headers);
  string _put(string ressource_path,
                   map<string, string> headers);
  string _delete(string ressource_path,
                      map<string, string> headers);
  string _trace(map<string, string> headers);
  string _options(map<string, string> headers);
  string _wrongMethod();
  string _generateResponse(size_t code,
                                map<string, string> headers,
                                string content);
  string _generateResponse(size_t code,
                                map<string, string> headers,
                                const unsigned char *content,
                                size_t content_size);
  string _getStatusDescription(size_t code);
  string _getErrorHTMLPage(size_t code);
  string _getListingHTMLPage(string path, string ressource);
  string _getMIMEType(string filename);
  string _getDateHeader();
  string _formatTimestamp(time_t timestamp);
//  Location _getLocation(string ressource);
  bool _isMethodAllowed(string method);
  string _formatRessource(string ressource);
  bool _shouldCallCGI(string ressource_path);
  string _addCGIHeaders(string response);
  string _getCGIStatus(string response);

public:
  Request();
  Request(Headers &headers, CGI &cgi);
  Request(const Request &other);
  Request &operator=(const Request &other);
  ~Request();
  string getResponse();
};

#endif // WEBSERV_REQUEST_HPP
