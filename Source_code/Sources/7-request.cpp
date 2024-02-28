//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/7-request.hpp"

/**
 * Creates a request interpretor from the request string and a server
 * configuration
 * @param request the string repreesentation of the HTTP request
 * @param serverConf the server configuration
 */
Request::Request()
    : _headers(), _cgi(), _client(NULL), _server(NULL), _location(NULL),
      _complete(false), manage(NULL) {}

Request::Request(Headers &headers, CGI &cgi)
    : _headers(&headers), _cgi(&cgi), _client(headers.getClient()),
      _server(_client->getServerByHost(headers.getHeaderFields()["Host"])),
      _location(_server->getLocationByRessource(headers.getFirstLine()[PATH])),
      _complete(false), manage(&Request::method) {}

Request::Request(const Request &other)
    : _headers(other._headers), _cgi(other._cgi), _client(other._client),
      _server(other._server), _location(other._location), _complete(false),
      manage(other.manage) {}

Request::~Request() {}

Request &Request::operator=(const Request &other) {
  if (this != &other) {
    _headers = other._headers;
    _cgi = other._cgi;
    _client = other._client;
    _server = other._server;
    _location = other._location;
    _complete = other._complete;
    manage = other.manage;
  }
  return (*this);
}
void Request::manageRequest() {
  if (_client->isEndRecv())
    return;
  while (!_complete)
    (this->*manage)();
  if (_headers->getFirstLine()[STATUS_CODE].empty())
    _complete = false;
  else
    _client->setReceived(true);
}

void Request::method() {
  map<string, manager> mapTmp;
  mapTmp["GET"] = &Request::_get;
  mapTmp["HEAD"] = &Request::_head;
  mapTmp["POST"] = &Request::_post;
  mapTmp["PUT"] = &Request::_put;
  mapTmp["DELETE"] = &Request::_delete;
  mapTmp["CONNECT"] = &Request::_connect;
  mapTmp["OPTIONS"] = &Request::_options;
  mapTmp["TRACE"] = &Request::_trace;
  setStrIt tmp = _location->methods.find(_headers->getFirstLine()[METHOD]);
  if (tmp != _location->methods.end())
    manage = mapTmp[*tmp];
  else {
    _headers->setFirstLine(STATUS_CODE, "505");
    _complete = true;
  }
}

bool Request::checkRessource() {
  string root = _location->root.empty() ? _server->root : _location->root;
  root += _headers->getFirstLine()[PATH];
  int type = pathType(root);
  if (!type)
    return false;
  if (type == 3)
}

bool Request::checkHTTPVersion() {}

void Request::_get() {
  vector<unsigned char> content_bytes;
  unsigned char *ressource_content;
  time_t file_date;
  try {
    content_bytes = readBinaryFile(ressource_path);
    ressource_content = reinterpret_cast<unsigned char *>(&content_bytes[0]);
    headers["Content-Type"] = _getMIMEType(ressource_path);
    pathType(ressource_path, &file_date);
    headers["Last-Modified"] = _formatTimestamp(file_date);
    if (send_body)
      return (_generateResponse(200, headers, ressource_content,
                                content_bytes.size()));
    return (_generateResponse(200, headers, ""));
  } catch (const exception &e) {
    return (_generateResponse(403, headers,
                              send_body ? _getErrorHTMLPage(403) : ""));
  }
  return (
      _generateResponse(500, headers, send_body ? _getErrorHTMLPage(500) : ""));
}

void Request::_head() { return (_get(ressource_path, headers, false)); }

void Request::_post() {
  // struct stat   buffer;
  int fd = -1;
  int rtn = 0;
  int type;
  string path;

  //  if (_location.upload_path.size() > 0)
  //  {
  //    string file = string(_header_block.getRequestLine()._request_target,
  //    _location.name.size()); path = _location.upload_path + "/" + file;
  //  }
  //  else
  path = ressource_path;
  DEBUG("POST path: " + path);
  type = pathType(path, NULL);
  try {
    if (type == 1) {
      if ((fd = open(path.c_str(), O_WRONLY | O_TRUNC, 0644)) == -1)
        throw(throwMessageErrno("TO CHANGE"));
      write(fd, _header_block.getContent().c_str(),
            _header_block.getContent().length());
      close(fd);
      rtn = 200;
      //      headers["Content-Location"] =
      //          _header_block.getRequestLine()._request_target;
    } else if (type == 0) {
      if ((fd = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1)
        return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
      write(fd, _header_block.getContent().c_str(),
            _header_block.getContent().length());
      close(fd);
      rtn = 201;
      //      headers["Location"] =
      //      _header_block.getRequestLine()._request_target;
    } else
      return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
  } catch (exception &ex) {
    throwError(ex);
  }
  return (_generateResponse(rtn, headers, ""));
}

void Request::_put() {
  int fd = -1;
  int rtn = 0;
  int type;
  string path;

  //  if (_location.upload_path.size() > 0)
  //  {
  //    string file = string(_header_block.getRequestLine()._request_target,
  //    _location.name.size()); path = _location.upload_path + "/" + file;
  //  }
  //  else
  path = ressource_path;
  DEBUG("PUT path: " + path);
  type = pathType(path, NULL);
  try {
    if (type == 0) {
      if ((fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
        throw(throwMessageErrno("TO CHANGE"));
      write(fd, _header_block.getContent().c_str(),
            _header_block.getContent().length());
      close(fd);
      rtn = 201;
    } else if (type == 1) {
      if ((fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        throw(throwMessageErrno("Create file on put"));
      write(fd, _header_block.getContent().c_str(),
            _header_block.getContent().length());
      close(fd);
      rtn = 204;
    } else
      return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
    //    headers["Content-Location"] =
    //        _header_block.getRequestLine()._request_target;
  } catch (exception &ex) {
    throwError(ex);
    return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
  }
  return (_generateResponse(rtn, headers, ""));
}

void Request::_delete() {
  int type;

  type = pathType(ressource_path, NULL);
  if (type == 1) {
    unlink(ressource_path.c_str());
    return (_generateResponse(200, headers, ""));
  }
  return (_generateResponse(404, headers, _getErrorHTMLPage(404)));
}

void Request::_connect() {
  _headers->setFirstLine(STATUS_CODE, "200");
  _complete = true;
}

void Request::_trace() {
  headers["Content-Type"] = "message/http";
  return (_generateResponse(200, headers, _header_block.getPlainRequest()));
}

/**
 * Performs an OPTIONS request.
 * @param headers a map representing HTTP headers of the reponse.
 * @return the string representation of the HTTP response
 */
string Request::_options(map<string, string> headers) {
  headers.erase("Content-Type");
  string allowed;

  for (size_t i = 0; i < _location.methods.size(); ++i) {
    //    allowed += _location.methods[i];
    if (i < _location.methods.size() - 1)
      allowed += ", ";
  }
  headers["Allow"] = allowed;
  return (_generateResponse(200, headers, ""));
}

string Request::getResponse(void) {
  //  map<string, string> headers;
  //  string method = _header_block.getRequestLine()._method;
  //  string ressource_path;
  //
  //  headers["Content-Type"] = _getMIMEType("a.html");
  //  if (_header_block.getContent().size() > _conf.clientMaxBodySize)
  //    return (_generateResponse(413, headers,
  //                              method != "HEAD" ? _getErrorHTMLPage(413) :
  //                              ""));
  //  if (!_isMethodAllowed(method))
  //    return (_wrongMethod());
  //  if (method == "TRACE")
  //    return (_trace(headers));
  //  else if (method == "OPTIONS")
  //    return (_options(headers));
  //  else if (method == "CONNECT")
  //    return (_generateResponse(200, headers, ""));
  //  ressource_path = _location.root;
  //  if (ressource_path[ressource_path.size() - 1] == '/')
  //    ressource_path = string(ressource_path, 0, ressource_path.size() - 1);
  //  ressource_path += _ressource;
  //  DEBUG("ressource path: " + ressource_path);
  //  if (pathType(ressource_path, NULL) == 2) {
  //    DEBUG("ressource path: " + ressource_path +
  //          ((ressource_path[ressource_path.length() - 1] == '/') ? "" : "/")
  //          + _location.index);
  //    if (_location.index.length() > 0)
  //      ressource_path =
  //          ressource_path +
  //          ((ressource_path[ressource_path.length() - 1] == '/') ? "" : "/")
  //          + _location.index;
  //    else {
  //      if (_location.autoindex)
  //        return (_generateResponse(
  //            200, headers,
  //            method != "HEAD" ? _getListingHTMLPage(ressource_path,
  //            _ressource)
  //                             : ""));
  //      else
  //        return (_generateResponse(
  //            403, headers, method != "HEAD" ? _getErrorHTMLPage(403) : ""));
  //    }
  //  }
  //  if (pathType(ressource_path, NULL) == 0 && method != "PUT" &&
  //      method != "POST")
  //    return (_generateResponse(404, headers,
  //                              method != "HEAD" ? _getErrorHTMLPage(404) :
  //                              ""));
  //  if (_shouldCallCGI(ressource_path)) {
  //    DEBUG("call CGI for this request");
  //    try {
  //      return (_addCGIHeaders(CGI(_location.cgiPath, ressource_path,
  //                                 _header_block, _conf, _location)
  //                                 .getOutput()));
  //    } catch (const exception &e) {
  //      cerr << e.what() << endl;
  //      return (_generateResponse(
  //          500, headers, method != "HEAD" ? _getErrorHTMLPage(500) : ""));
  //    }
  //  }
  //  if (method == "GET")
  //    return _get(ressource_path, headers);
  //  else if (method == "HEAD")
  //    return _head(ressource_path, headers);
  //  else if (method == "POST")
  //    return _post(ressource_path, headers);
  //  else if (method == "PUT")
  //    return (_put(ressource_path, headers));
  //  else if (method == "DELETE")
  //    return (_delete(ressource_path, headers));
  return ("");
}

/**
 * Returns a 405 response in case of not allowed method
 * @return the string representation of the HTTP response
 */
// string Request::_wrongMethod {
//   map<string, string> headers;
//   string allowed;
//
//   for (size_t i = 0; i < _location.methods.size(); ++i) {
//     //    allowed += _location.methods[i];
//     if (i < _location.methods.size() - 1)
//       allowed += ", ";
//   }
//   headers["Allow"] = allowed;
//   return "";/*(_generateResponse(405, headers,
//                             _header_block.getRequestLine()._method != "HEAD"
//                                 ? _getErrorHTMLPage(405)
//                                 : ""));*/
// }

/**
 * Creates a HTTP response based on given code and content
 * @param code the status code of the response
 * @param headers headers to inject in response
 * @param content an unsigned char array of the content to send
 * @param size the size in bytes of the content
 * @return the string representation of a HTTP response
 */
string Request::_generateResponse(size_t code, map<string, string> headers,
                                  const unsigned char *content,
                                  size_t content_size) {
  string response;
  map<string, string>::iterator it;

  headers["Content-Length"] = uIntegerToString(content_size);
  headers["Select"] = "webserv";
  headers["Date"] = _getDateHeader();
  response += "HTTP/1.1 ";
  response += uIntegerToString(code) + " ";
  response += _getStatusDescription(code) + "\r\n";
  it = headers.begin();
  while (it != headers.end()) {
    response += it->first + ": " + it->second + "\r\n";
    ++it;
  }
  response += "\r\n";
  for (size_t i = 0; i < content_size; ++i)
    response += content[i];
  return (response);
}

/**
 * Creates a HTTP response based on given code and ASCII content
 * @param code the status code of the response
 * @param headers headers to inject in response
 * @param content the string representation of the content
 * @return the string representation of a HTTP response
 */
string Request::_generateResponse(size_t code, map<string, string> headers,
                                  string content) {
  return (_generateResponse(
      code, headers, reinterpret_cast<const unsigned char *>(content.c_str()),
      content.size()));
}

/**
 * Get the status description following the rfc 7231 section 6.1
 * @param code the HTTP status code
 * @return the corresponding reason description
 */
string Request::_getStatusDescription(size_t code) {
  map<size_t, string> m;

  m[100] = "Continue";
  m[101] = "Switching Protocols";
  m[200] = "OK";
  m[201] = "Created";
  m[202] = "Accepted";
  m[203] = "Non-Authoritative Information";
  m[204] = "No Content";
  m[205] = "Reset Content";
  m[206] = "Partial Content";
  m[300] = "Multiple Choices";
  m[301] = "Moved Permanently";
  m[302] = "Found";
  m[303] = "See Other";
  m[304] = "Not Modified";
  m[305] = "Use Proxy";
  m[307] = "Temporary Redirect";
  m[400] = "Bad Request";
  m[401] = "Unauthorized";
  m[402] = "Payment Required";
  m[403] = "Forbidden";
  m[404] = "Not Found";
  m[405] = "Method Not Allowed";
  m[406] = "Not Acceptable";
  m[407] = "Proxy Authentication Required";
  m[408] = "Request Timeout";
  m[409] = "Conflict";
  m[410] = "Gone";
  m[411] = "Length Required";
  m[412] = "Precondition Failed";
  m[413] = "Payload Too Large";
  m[414] = "URI Too Long";
  m[415] = "Unsupported Media Type";
  m[416] = "Range Not Satisfiable";
  m[417] = "Expectation Failed";
  m[426] = "Upgrade Required";
  m[500] = "Internal Select Error";
  m[501] = "Not Implemented";
  m[502] = "Bad Gateway";
  m[503] = "Service Unavailable";
  m[504] = "Gateway Timeout";
  m[505] = "HTTP Version Not Supported";
  return m[code];
  return ("Error");
}

/**
 * Get the HTML page for a given status error
 * @param status the status of the response
 * @return a HTML page describing the error
 */
string Request::_getErrorHTMLPage(size_t code) {
  string base;

  if (_conf.errorPages.count(code) > 0)
    return (readFile(_conf.errorPages[code]));
  base = readFile("./assets/error.html");
  base = replace(base, "$1", uIntegerToString(code));
  base = replace(base, "$2", _getStatusDescription(code));
  return (base);
}

/**
 * Get the directory listing HTML page
 * @param path the full path of the directory to list on the disk
 * @param ressource the ressource the user tried to reach
 * @return a HTML page that lists the content of the given directory
 */
string Request::_getListingHTMLPage(string path, string ressource) {
  string base;
  string listing;
  string link_base;
  //  size_t i;
  struct dirent *en;
  DIR *dr;

  base = readFile("./assets/listing.html");
  base = replace(base, "$1", ressource);
  dr = opendir(path.c_str());
  //  i = 0;
  //  while (_header_block.getRequestLine()._request_target[i] &&
  //         _header_block.getRequestLine()._request_target[i] != '?')
  //    link_base += _header_block.getRequestLine()._request_target[i++];
  if (link_base[link_base.size() - 1] != '/')
    link_base += '/';
  while ((en = readdir(dr)) != 0)
    listing += "<li><a href=\"" + link_base + string(en->d_name) + "\">" +
               string(en->d_name) + "</a></li>";
  closedir(dr);
  base = replace(base, "$2", listing);
  return (base);
}

/**
 * Get the content type based on filename
 * @param filename
 * @return the MIME type for the given filename
 */
string Request::_getMIMEType(string filename) {
  map<string, string> m;
  string ext;
  size_t i;

  i = filename.size() - 1;
  while (i > 0 && filename[i] != '.')
    --i;
  if (i == 0)
    return ("text/plain");
  ext = string(filename, i + 1, filename.size() - i);
  m["aac"] = "audio/aac";
  m["abw"] = "application/x-abiword";
  m["arc"] = "application/octet-stream";
  m["avi"] = "video/x-msvideo";
  m["azw"] = "application/vnd.amazon.ebook";
  m["bin"] = "application/octet-stream";
  m["bmp"] = "image/bmp";
  m["bz"] = "application/x-bzip";
  m["bz2"] = "application/x-bzip2";
  m["csh"] = "application/x-csh";
  m["css"] = "text/css";
  m["csv"] = "text/csv";
  m["doc"] = "application/msword";
  m["docx"] = "application/"
              "vnd.openxmlformats-officedocument.wordprocessingml.document";
  m["eot"] = "application/vnd.ms-fontobject";
  m["epub"] = "application/epub+zip";
  m["gif"] = "image/gif";
  m["htm"] = "text/html";
  m["html"] = "text/html";
  m["ico"] = "image/x-icon";
  m["ics"] = "text/calendar";
  m["jar"] = "application/java-archive";
  m["jpeg"] = "image/jpeg";
  m["jpg"] = "image/jpeg";
  m["js"] = "application/javascript";
  m["json"] = "application/json";
  m["mid"] = "audio/midi";
  m["midi"] = "audio/midi";
  m["mpeg"] = "video/mpeg";
  m["mpkg"] = "application/vnd.apple.installer+xml";
  m["odp"] = "application/vnd.oasis.opendocument.presentation";
  m["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
  m["odt"] = "application/vnd.oasis.opendocument.text";
  m["oga"] = "audio/ogg";
  m["ogv"] = "video/ogg";
  m["ogx"] = "application/ogg";
  m["otf"] = "font/otf";
  m["png"] = "image/png";
  m["pdf"] = "application/pdf";
  m["ppt"] = "application/vnd.ms-powerpoint";
  m["pptx"] = "application/"
              "vnd.openxmlformats-officedocument.presentationml.presentation";
  m["rar"] = "application/x-rar-compressed";
  m["rtf"] = "application/rtf";
  m["sh"] = "application/x-sh";
  m["svg"] = "image/svg+xml";
  m["swf"] = "application/x-shockwave-flash";
  m["tar"] = "application/x-tar";
  m["tif"] = "image/tiff";
  m["tiff"] = "image/tiff";
  m["ts"] = "application/typescript";
  m["ttf"] = "font/ttf";
  m["vsd"] = "application/vnd.visio";
  m["wav"] = "audio/x-wav";
  m["weba"] = "audio/webm";
  m["webm"] = "video/webm";
  m["webp"] = "image/webp";
  m["woff"] = "font/woff";
  m["woff2"] = "font/woff2";
  m["xhtml"] = "application/xhtml+xml";
  m["xls"] = "application/vnd.ms-excel";
  m["xlsx"] =
      "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
  m["xml"] = "application/xml";
  m["xul"] = "application/vnd.mozilla.xul+xml";
  m["zip"] = "application/zip";
  m["3gp"] = "audio/3gpp";
  m["3g2"] = "audio/3gpp2";
  m["7z"] = "application/x-7z-compressed";
  if (m.count(ext))
    return (m[ext]);
  return ("application/octet-stream");
}

/**
 * Get the right location in configuration based on the asked ressource
 * @param ressource the asked ressource
 * @return the location configuration object
 * @example ressource "/" in configurations "/wordpress", "/upload" and "/"
 * will return "/"
 * @example ressource "/wordpress/index.php" in configurations "/wordpress",
 * "/upload" and "/" will return "/wordpress"
 */

/**
 * Get the current HTTP formatted date
 * @return a string representing the current date formatted for HTTP header
 */
string Request::_getDateHeader() {
  struct timeval now;
  struct timezone tz;

  gettimeofday(&now, &tz);
  return (_formatTimestamp(now.tv_sec + tz.tz_minuteswest * 60));
}

/**
 * Format a timestamp to a HTTP formatted date
 * @param timestamp the timestamp in second of the date
 * @return a string representation of the date according to HTTP standard
 */
string Request::_formatTimestamp(time_t timestamp) {
  (void)timestamp;
  char buffer[33];
  //  struct tm *ts;
  //  size_t last;

  //  ts   = localtime(&timestamp);
  //  last = strftime(bufferuffer, 32, "%a, %d %b %Y %T GMT", ts);
  //  buffer[last] = '\0';
  return (string(buffer));
}

/**
 * Is a method available on current location
 * @param method the HTTP method
 * @return wether the method is accepted on this location or not
 */
bool Request::_isMethodAllowed(string method) {
  (void)method;
  for (size_t i = 0; i < _location.methods.size(); ++i) {
    //    if (_location.methods[i] == method)
    //      return (true);
  }
  return (false);
}

/**
 * Remove location name and arguments from ressource
 * @param ressource
 * @return ressource without location name and args
 * @example "/wordpress/index.php?page_id=12" with location "/wordpress"
 * will give "/index.php"
 */
string Request::_formatRessource(string ressource) {
  string res;
  size_t i;

  i = 0;
  res = ressource;
  res.replace(0, _location.path.size(), "/");
  res = replace(res, "//", "/");
  while (res[i] && res[i] != '?')
    ++i;
  res = string(res, 0, i);
  return (res);
}

/**
 * Detect if we should use a CGI for this file
 * @return wether we should use the CGI for the current request
 */
bool Request::_shouldCallCGI(string ressource_path) {
  size_t i;
  string ext;

  if (_location.cgiPath.size() == 0)
    return (false);
  i = ressource_path.size() - 1;
  while (i > 0 && ressource_path[i] != '.')
    --i;
  if (i >= ressource_path.size())
    return (false);
  ext = string(ressource_path, i + 1, ressource_path.size() - i);
  for (size_t j = 0; j < _location.cgiExtension.size(); ++j) {
    if (_location.cgiExtension[j] == ext)
      return (true);
  }
  return (false);
}

/**
 * Add mendatory server headers to a CGI HTTP response, if status is
 * returned we get it to form HTTP status
 * @param response the HTTP response out of the CGI
 * @return the same HTTP response with additional headers
 */
string Request::_addCGIHeaders(string response) {
  string res;
  size_t size;
  int header_char_count = 0;

  string headers = response;
  if (response.find("\r\n\r\n") != string::npos)
    headers = response.substr(0, response.find("\r\n\r\n"));
  if (headers != "") {
    for (size_t i = 0; i < headers.length(); i++)
      if (headers[i] != '\n' && headers[i] != '\r')
        header_char_count++;
  }
  size = response.size() - count(response.begin(), response.end(), '\n') -
         count(response.begin(), response.end(), '\r') - header_char_count;
  res = response;
  res = "Content-Length: " + uIntegerToString(size) + "\r\n" + res;
  res = "Date: " + _getDateHeader() + "\r\n" + res;
  if (_getCGIStatus(response).size() > 0)
    res = "HTTP/1.1 " + _getCGIStatus(response) + "\r\n" + res;
  else
    res = "HTTP/1.1 200 OK\r\n" + res;
  return (res);
}

/**
 * Get CGI response status if any
 * @param response the CGI response
 * @return a string containing the code and status if found, an empty string
 * if not
 */
string Request::_getCGIStatus(string response) {
  vector<string> splits;

  for (size_t i = 0; i < countLines(response); ++i) {
    splits = splitWhitespace(getLine(response, i));
    if (splits.size() == 3 && splits[0] == "Status:")
      return (splits[1] + " " + splits[2]);
  }
  return ("");
}
// bool Headers::isValidFirstLine() {
//   if (_firstLine[METHOD])
//     if (_firstLine[HTTP_V] == "HTTP/1.1")
//       _firstLine[STATUS_CODE] = "505";
//
//   return true;
// }
// bool Headers::findRessource() {
//   _server = _client->getServerByHost(_headerFields["Host"]);
//   _location = _server->getLocationByRessource(_firstLine[PATH]);
//   return true;
// }