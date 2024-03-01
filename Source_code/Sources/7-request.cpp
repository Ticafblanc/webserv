//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/7-request.hpp"

Request::Request()
    : _headers(), _cgi(), _client(NULL), _complete(false), _manage(NULL) {}

Request::Request(Headers &headers, CGI &cgi)
    : _headers(&headers), _cgi(&cgi), _client(headers.getClient()),
      _complete(false), _manage(NULL) {}

Request::Request(const Request &other)
    : _headers(other._headers), _cgi(other._cgi), _client(other._client),
      _complete(false), _manage(other._manage) {}

Request::~Request() {}

Request &Request::operator=(const Request &other) {
  if (this != &other) {
    _headers = other._headers;
    _cgi = other._cgi;
    _client = other._client;
    _complete = other._complete;
    _manage = other._manage;
  }
  return (*this);
}
bool Request::manageIsNull() const { return !_manage; }
void Request::resetManage(pManage m) { _manage = m; }
void Request::manager() {
  cout << "request manager" << endl;
  if (manageIsNull()) {
    resetManage(&Request::_method);
  }
  _complete = false;
  while (!_complete)
    (this->*_manage)();
}

void Request::_method() {
  cout << "method" << endl;

  map<string, pManage> mapTmp;
  mapTmp["GET"] = &Request::_get;
  mapTmp["HEAD"] = &Request::_head;
  mapTmp["POST"] = &Request::_post;
  mapTmp["PUT"] = &Request::_put;
  mapTmp["DELETE"] = &Request::_delete;
  mapTmp["TRACE"] = &Request::_trace;
  setStrIt tmp =
      _client->getLocation()->methods.find(_headers->getFirstLine()[METHOD]);
  if (tmp != _client->getLocation()->methods.end())
    _manage = mapTmp[*tmp];
  else
    throw Exception("Method not allowed", _client->getSd(), "405");
}

void Request::_head() {
  cout << "get " << _headers->getFirstLine()[PATH] << " "
       << _client->getRessourcePath() << endl;
  _complete = true;
  if (!checkPermissionR(_client->getRessourcePath())) {
    if (!isFile(_client->getRessourcePath())) {
      throw Exception("uri not found", _client->getSd(), "404");
    }
    throw Exception("uri not found", _client->getSd(), "403");
  }
  _headers->setHead();
  _complete = true;
}

void Request::_get() {
  _head();
  ifstream ifs(_client->getRessourcePath().c_str());
  if (!ifs.is_open())
    throw Exception("fail to open file " + _client->getRessourcePath(),
                    _client->getSd(), "500");
  _client->getBody() = string((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  _headers->setGet();
  _complete = true;
}

void Request::_delete() {
  _head();
  if (remove(_client->getRessourcePath().c_str()))
    throw Exception("fail to delete file " + _client->getRessourcePath(),
                    _client->getSd(), "500");
  _headers->setDelete();
  _complete = true;
}

void Request::_post() {
  // struct stat   buffer;
  //  int fd = -1;
  //  int rtn = 0;
  //  int type;
  //  string path;
  //
  //  //  if (_location.upload_path.size() > 0)
  //  //  {
  //  //    string file = string(_header_block.getRequestLine()._request_target,
  //  //    _location.name.size()); path = _location.upload_path + "/" + file;
  //  //  }
  //  //  else
  //  path = ressource_path;
  //  DEBUG("POST path: " + path);
  //  type = pathType(path, NULL);
  //  try {
  //    if (type == 1) {
  //      if ((fd = open(path.c_str(), O_WRONLY | O_TRUNC, 0644)) == -1)
  //        throw(ErrnoException("TO CHANGE"));
  //      write(fd, _header_block.getContent().c_str(),
  //            _header_block.getContent().length());
  //      close(fd);
  //      rtn = 200;
  //      //      headers["Content-Location"] =
  //      //          _header_block.getRequestLine()._request_target;
  //    } else if (type == 0) {
  //      if ((fd = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644)) ==
  //      -1)
  //        return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
  //      write(fd, _header_block.getContent().c_str(),
  //            _header_block.getContent().length());
  //      close(fd);
  //      rtn = 201;
  //      //      headers["Location"] =
  //      //      _header_block.getRequestLine()._request_target;
  //    } else
  //      return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
  //  } catch (exception &ex) {
  //    throwError(ex);
  //  }
  //  return (_generateResponse(rtn, headers, ""));
  _headers->setPost();
  _complete = true;
}

void Request::_put() {
  //  int fd = -1;
  //  int rtn = 0;
  //  int type;
  //  string path;
  //
  //  //  if (_location.upload_path.size() > 0)
  //  //  {
  //  //    string file = string(_header_block.getRequestLine()._request_target,
  //  //    _location.name.size()); path = _location.upload_path + "/" + file;
  //  //  }
  //  //  else
  //  path = ressource_path;
  //  DEBUG("PUT path: " + path);
  //  type = pathType(path, NULL);
  //  try {
  //    if (type == 0) {
  //      if ((fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644)) ==
  //      -1)
  //        throw(ErrnoException("TO CHANGE"));
  //      write(fd, _header_block.getContent().c_str(),
  //            _header_block.getContent().length());
  //      close(fd);
  //      rtn = 201;
  //    } else if (type == 1) {
  //      if ((fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644)) ==
  //      -1)
  //        throw(ErrnoException("Create file on put"));
  //      write(fd, _header_block.getContent().c_str(),
  //            _header_block.getContent().length());
  //      close(fd);
  //      rtn = 204;
  //    } else
  //      return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
  //    //    headers["Content-Location"] =
  //    //        _header_block.getRequestLine()._request_target;
  //  } catch (exception &ex) {
  //    throwError(ex);
  //    return (_generateResponse(500, headers, _getErrorHTMLPage(500)));
  //  }
  //  return (_generateResponse(rtn, headers, ""));
  _headers->setPut();
  _complete = true;
}

void Request::_trace() {
  _headers->setTrace();
  _complete = true;
}

/**
 * Get the HTML page for a given status error
 * @param status the status of the response
 * @return a HTML page describing the error
 */
string Request::_getErrorHTMLPage(size_t code) {
  string base;
  (void)code;

  //  if (_conf.errorPages.count(code) > 0)
  //    return (readFile(_conf.errorPages[code]));
  //  base = readFile("./assets/error.html");
  //  base = replace(base, "$1", uIntegerToString(code));
  //  base = replace(base, "$2", _getStatusDescription(code));
  return (base);
}

// string Request::_getListingHTMLPage(string path, string ressource) {
//   string base;
//   string listing;
//   string link_base;
//   //  size_t i;
//   struct dirent *en;
//   DIR *dr;
//
//   base = readFile("./assets/listing.html");
//   base = replace(base, "$1", ressource);
//   dr = opendir(path.c_str());
//   //  i = 0;
//   //  while (_header_block.getRequestLine()._request_target[i] &&
//   //         _header_block.getRequestLine()._request_target[i] != '?')
//   //    link_base += _header_block.getRequestLine()._request_target[i++];
//   if (link_base[link_base.size() - 1] != '/')
//     link_base += '/';
//   while ((en = readdir(dr)) != 0)
//     listing += "<li><a href=\"" + link_base + string(en->d_name) + "\">" +
//                string(en->d_name) + "</a></li>";
//   closedir(dr);
//   base = replace(base, "$2", listing);
//   return (base);
// }

// string Request::_getMIMEType(string filename) {
//   map<string, string> m;
//   string ext;
//   size_t i;
//
//   i = filename.size() - 1;
//   while (i > 0 && filename[i] != '.')
//     --i;
//   if (i == 0)
//     return ("text/plain");
//   ext = string(filename, i + 1, filename.size() - i);
//   m["aac"] = "audio/aac";
//   m["abw"] = "application/x-abiword";
//   m["arc"] = "application/octet-stream";
//   m["avi"] = "video/x-msvideo";
//   m["azw"] = "application/vnd.amazon.ebook";
//   m["bin"] = "application/octet-stream";
//   m["bmp"] = "image/bmp";
//   m["bz"] = "application/x-bzip";
//   m["bz2"] = "application/x-bzip2";
//   m["csh"] = "application/x-csh";
//   m["css"] = "text/css";
//   m["csv"] = "text/csv";
//   m["doc"] = "application/msword";
//   m["docx"] = "application/"
//               "vnd.openxmlformats-officedocument.wordprocessingml.document";
//   m["eot"] = "application/vnd.ms-fontobject";
//   m["epub"] = "application/epub+zip";
//   m["gif"] = "image/gif";
//   m["htm"] = "text/html";
//   m["html"] = "text/html";
//   m["ico"] = "image/x-icon";
//   m["ics"] = "text/calendar";
//   m["jar"] = "application/java-archive";
//   m["jpeg"] = "image/jpeg";
//   m["jpg"] = "image/jpeg";
//   m["js"] = "application/javascript";
//   m["json"] = "application/json";
//   m["mid"] = "audio/midi";
//   m["midi"] = "audio/midi";
//   m["mpeg"] = "video/mpeg";
//   m["mpkg"] = "application/vnd.apple.installer+xml";
//   m["odp"] = "application/vnd.oasis.opendocument.presentation";
//   m["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
//   m["odt"] = "application/vnd.oasis.opendocument.text";
//   m["oga"] = "audio/ogg";
//   m["ogv"] = "video/ogg";
//   m["ogx"] = "application/ogg";
//   m["otf"] = "font/otf";
//   m["png"] = "image/png";
//   m["pdf"] = "application/pdf";
//   m["ppt"] = "application/vnd.ms-powerpoint";
//   m["pptx"] = "application/"
//               "vnd.openxmlformats-officedocument.presentationml.presentation";
//   m["rar"] = "application/x-rar-compressed";
//   m["rtf"] = "application/rtf";
//   m["sh"] = "application/x-sh";
//   m["svg"] = "image/svg+xml";
//   m["swf"] = "application/x-shockwave-flash";
//   m["tar"] = "application/x-tar";
//   m["tif"] = "image/tiff";
//   m["tiff"] = "image/tiff";
//   m["ts"] = "application/typescript";
//   m["ttf"] = "font/ttf";
//   m["vsd"] = "application/vnd.visio";
//   m["wav"] = "audio/x-wav";
//   m["weba"] = "audio/webm";
//   m["webm"] = "video/webm";
//   m["webp"] = "image/webp";
//   m["woff"] = "font/woff";
//   m["woff2"] = "font/woff2";
//   m["xhtml"] = "application/xhtml+xml";
//   m["xls"] = "application/vnd.ms-excel";
//   m["xlsx"] =
//       "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
//   m["xml"] = "application/xml";
//   m["xul"] = "application/vnd.mozilla.xul+xml";
//   m["zip"] = "application/zip";
//   m["3gp"] = "audio/3gpp";
//   m["3g2"] = "audio/3gpp2";
//   m["7z"] = "application/x-7z-compressed";
//   if (m.count(ext))
//     return (m[ext]);
//   return ("application/octet-stream");
// }

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
// bool Request::_isMethodAllowed(string method) {
//   (void)method;
//   for (size_t i = 0; i < _location.methods.size(); ++i) {
//     //    if (_location.methods[i] == method)
//     //      return (true);
//   }
//   return (false);
// }

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
  //  res.replace(0, _location.path.size(), "/");
  //  res = replace(res, "//", "/");
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

  //  if (_location.cgiPath.size() == 0)
  //    return (false);
  i = ressource_path.size() - 1;
  while (i > 0 && ressource_path[i] != '.')
    --i;
  if (i >= ressource_path.size())
    return (false);
  ext = string(ressource_path, i + 1, ressource_path.size() - i);
  //  for (size_t j = 0; j < _location.cgiExtension.size(); ++j) {
  //    if (_location.cgiExtension[j] == ext)
  //      return (true);
  //  }
  return (false);
}

/**
 * Add mendatory server headers to a CGI HTTP response, if status is
 * returned we get it to form HTTP status
 * @param response the HTTP response out of the CGI
 * @return the same HTTP response with additional headers
 */
// string Request::_addCGIHeaders(string response) {
//   string res;
//   //  size_t size;
//   //  int header_char_count = 0;
//
//   string headers = response;
//   if (response.find("\r\n\r\n") != string::npos)
//     headers = response.substr(0, response.find("\r\n\r\n"));
//   if (headers != "") {
////    for (size_t i = 0; i < headers.length(); i++)
////      if (headers[i] != '\n' && headers[i] != '\r')
//    //        header_char_count++;
//  }
//  //  size = response.size() - count(response.begin(), response.end(), '\n') -
//  //         count(response.begin(), response.end(), '\r') -
//  header_char_count; res = response;
//  //  res = "Content-Length: " + uIntegerToString(size) + "\r\n" + res;
//  res = "Date: " + _getDateHeader() + "\r\n" + res;
//  if (_getCGIStatus(response).size() > 0)
//    res = "HTTP/1.1 " + _getCGIStatus(response) + "\r\n" + res;
//  else
//    res = "HTTP/1.1 200 OK\r\n" + res;
//  return (res);
//}

/**
 * Get CGI response status if any
 * @param response the CGI response
 * @return a string containing the code and status if found, an empty string
 * if not
 */
// string Request::_getCGIStatus(string response) {
//   vector<string> splits;

//  for (size_t i = 0; i < countLines(response); ++i) {
//    splits = splitWhitespace(getLine(response, i));
//    if (splits.size() == 3 && splits[0] == "Status:")
//      return (splits[1] + " " + splits[2]);
//  }
//  return ("");
//}
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
