//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/5-headers.hpp"

static char *cast(const string &line) {
  char *c = new char[line.size()];
  return c;
}

Headers::Headers()
    : _firstLine(8), _headerFields(), _boundary("boundary="), _client(NULL),
      _header(), _complete(false), _statusCode(), _mimeType() {
  _setMapStatus();
}

Headers::Headers(Client &clt)
    : _firstLine(8), _headerFields(), _boundary("boundary="), _client(&clt),
      _complete(false), _statusCode(), _mimeType() {
  _setMapStatus();
}

Headers::Headers(const Headers &copy)
    : _firstLine(copy._firstLine), _headerFields(copy._headerFields),
      _boundary(copy._boundary), _client(copy._client), _header(),
      _complete(false), _statusCode(copy._statusCode),
      _mimeType(copy._mimeType) {}

Headers::~Headers() {}

Headers &Headers::operator=(const Headers &rhs) {
  if (this != &rhs) {
    _firstLine = rhs._firstLine;
    _headerFields = rhs._headerFields;
    _boundary = rhs._boundary;
    _client = rhs._client;
    _header.str(rhs._header.str());
    _statusCode = rhs._statusCode;
    _mimeType = rhs._mimeType;
  }
  return *this;
}

void Headers::_extractFirstLine() {
  string line;
  if (getline(_header >> ws, line, '\r')) {
    istringstream fl(line);
    fl >> ws >> _firstLine[METHOD] >> _firstLine[URI] >> _firstLine[HTTP_V];
  }
  if (!_client->allowMethod(_firstLine[METHOD]))
    throw Exception("Methode not implemented", _client->getSd(), "501");
  if (_firstLine[URI].length() > URI_SIZE)
    throw Exception("uri too long", _client->getSd(), "414");
  if (_firstLine[HTTP_V] != "HTTP/1.1")
    throw Exception("Http version not supported", _client->getSd(), "505");
  _extractUri();
  cout << _firstLine[METHOD] << _firstLine[URI] << _firstLine[HTTP_V] << endl;
}

void Headers::_extractData() {
  string line, token, value;
  size_t i = 0;
  while (getline(_header >> ws, line, '\r') && ++i) {
    istringstream bufferLine(line);
    if (getline(bufferLine >> ws, token, ':'))
      if (getline(bufferLine >> ws, value))
        _headerFields[token] = value;
    cout << _headerFields.find(token)->first << " : "
         << _headerFields.find(token)->second << endl;
  }
//  if (i != _headerFields.size())
//    throw Exception("Headers not complete", _client->getSd(), "400");
}

void Headers::parse() {
  _header = istringstream(_client->getHeader());
  _extractFirstLine();
  _extractData();
  _client->updateRessource(_headerFields["Host"], _firstLine[PATH]);
}

void Headers::_extractUri() {
  _extractQueryString();
  _extractPath();
  _extractExt();
}

void Headers::_extractQueryString() {
  string uri = _firstLine[URI];
  size_t pos = uri.find('?');
  if (pos != std::string::npos)
    _firstLine[QUERY_STRING] = uri.substr(pos + 1);
}

void Headers::_extractPath() {
  string uri = _firstLine[URI];
  size_t pos = uri.find('?');
  if (pos != std::string::npos)
    _firstLine[PATH] = uri.substr(0, pos);
  else
    _firstLine[PATH] = uri;
}

void Headers::_extractExt() {
  string path = _firstLine[PATH];
  size_t pos = path.find_last_of('.');
  if (pos != std::string::npos && path.substr(pos).length() == 3) {
    _firstLine[EXT] = path.substr(pos);
    if (!isValidMimeType())
      throw Exception("invalid mime type", _client->getSd(), "415");
  }
}

vector<char *> Headers::getCgiEnv() {
  vector<char *> env;
  execve(env[0], env.data(), env.data());
  env.push_back(cast("GATEWAY_INTERFACE=CGI/1.1"));
  env.push_back(cast("REMOTE_ADDR=" + _client->getIpAddress()));
  env.push_back(cast("AUTH_TYPE=Basic"));
  env.push_back(cast("REDIRECT_STATUS=200"));
  env.push_back(cast("DOCUMENT_ROOT=" + _client->getLocation()->root));
  env.push_back(cast("QUERY_STRING=" + _firstLine[QUERY_STRING]));
  env.push_back(cast("REQUEST_METHOD=" + _firstLine[METHOD]));
  env.push_back(cast("REQUEST_URI=" + _firstLine[URI]));
  env.push_back(cast("SCRIPT_NAME=" + _firstLine[PATH]));
  env.push_back(cast("SCRIPT_FILENAME=" + _firstLine[PATH]));
  env.push_back(cast("PATH_INFO=" + _firstLine[URI]));
  env.push_back(cast("PATH_TRANSLATED=" + _firstLine[URI]));
  env.push_back(cast("SERVER_NAME=" + getHeaderField("host")));
  env.push_back(cast("SERVER_PORT" + itoa(_client->getPort())));
  env.push_back(cast("SERVER_PROTOCOL=" + _firstLine[HTTP_V]));
  env.push_back(cast("SERVER_SOFTWARE=webserv/1.0"));
  for (mapStrStrIt it = _headerFields.begin(); it != _headerFields.end();
       ++it) {
    string envVar = "HTTP_" + it->first;
    replace(envVar.begin(), envVar.end(), '-', '_');
    transform(envVar.begin(), envVar.end(), envVar.begin(), ::toupper);
    envVar += "=" + it->second;
    env.push_back(cast(envVar));
  }
  env.push_back(cast(NULL));
  return env;
}

vector<char *> Headers::getCgiArg() {
  vector<char *> arg;
  string execPath = _client->getLocation()->getCgiPath(_firstLine[EXT]);
  if (execPath.empty())
    throw Exception("Extension not found", _client->getSd(), "404");
  arg.push_back(cast(_client->getLocation()->getCgiPath(execPath)));
  arg.push_back(cast(_firstLine[PATH]));
  arg.push_back(cast(NULL));
  return arg;
}

vecStr &Headers::getFirstLine() { return _firstLine; }
mapStrStr &Headers::getHeaderFields() { return _headerFields; }
void Headers::setHeaderFields(const string &token, const string &value) {
  _headerFields[token] = value;
}

string Headers::getHeaderField(const string &token) {
  mapStrStrIt it = _headerFields.find(token);

  if (it != _headerFields.end())
    return it->second;
  return "";
}

size_t Headers::getContentLength() {
  mapStrStrIt it = _headerFields.find("Content-Length");

  if (it != _headerFields.end())
    return stol(it->second);
  return 0;
}

Client *Headers::getClient() { return _client; }
void Headers::setFirstLine(const int &pos, const string &value) {
  _firstLine[pos] = value;
}

void Headers::setStatus(const string &value) {
  setFirstLine(STATUS_CODE, value);
  _firstLine[RAISON_PHRASE] = _statusCode[_firstLine[STATUS_CODE]];
}

bool Headers::isCloseRequest() {
  mapStrStrIt it = _headerFields.find("Connection");
  if (it != _headerFields.end())
    return it->second == "close";
  return false;
}

void Headers::reset() {
  _headerFields["Host"] = "";
  if (_firstLine[METHOD] == "GET") {
    _headerFields["Content-Length"] = itoa(_client->getBody().length());
    _headerFields["Content-Type"] = _mimeType[_firstLine[EXT]];
  }
  _headerFields["Authorization"] = "";
  _headerFields["Cookie"] = "";
  if (_firstLine[STATUS_CODE] == "302")
    _headerFields["Location"] = _client->getLocation()->uriReturn;
}

string Headers::getHeaderReponse() {
  reset();
  ostringstream oss;
  oss << " " << _firstLine[HTTP_V] << " " << _firstLine[STATUS_CODE] << " "
      << _firstLine[RAISON_PHRASE] << "\r\n";
  for (mapStrStrIt it = _headerFields.begin(); it != _headerFields.end();
       ++it) {
    oss << it->first << ": " << it->second << "\r\n";
  }
  oss << "\r\n";
  return oss.str();
}

void Headers::setHead() {}
void Headers::setGet() {}
void Headers::setDelete() {}
void Headers::setPost() {}

void Headers::_setMapStatus() {
  _statusCode["100"] = "Continue";
  _statusCode["101"] = "Switching Protocols";
  _statusCode["200"] = "OK";
  _statusCode["201"] = "Created";
  _statusCode["202"] = "Accepted";
  _statusCode["203"] = "Non-Authoritative Information";
  _statusCode["204"] = "No Content";
  _statusCode["205"] = "Reset Content";
  _statusCode["206"] = "Partial Content";
  _statusCode["300"] = "Multiple Choices";
  _statusCode["301"] = "Moved Permanently";
  _statusCode["302"] = "Found";
  _statusCode["303"] = "See Other";
  _statusCode["304"] = "Not Modified";
  _statusCode["305"] = "Use Proxy";
  _statusCode["307"] = "Temporary Redirect";
  _statusCode["400"] = "Bad Request";
  _statusCode["401"] = "Unauthorized";
  _statusCode["402"] = "Payment Required";
  _statusCode["403"] = "Forbidden";
  _statusCode["404"] = "Not Found";
  _statusCode["405"] = "Method Not Allowed";
  _statusCode["406"] = "Not Acceptable";
  _statusCode["407"] = "Proxy Authentication Required";
  _statusCode["408"] = "Request Timeout";
  _statusCode["409"] = "Conflict";
  _statusCode["410"] = "Gone";
  _statusCode["411"] = "Length Required";
  _statusCode["412"] = "Precondition Failed";
  _statusCode["413"] = "Payload Too Large";
  _statusCode["414"] = "URI Too Long";
  _statusCode["415"] = "Unsupported Media Type";
  _statusCode["416"] = "Range Not Satisfiable";
  _statusCode["417"] = "Expectation Failed";
  _statusCode["426"] = "Upgrade Required";
  _statusCode["500"] = "Internal Select Error";
  _statusCode["501"] = "Not Implemented";
  _statusCode["502"] = "Bad Gateway";
  _statusCode["503"] = "Service Unavailable";
  _statusCode["504"] = "Gateway Timeout";
  _statusCode["505"] = "HTTP Version Not Supported";
}

bool Headers::isValidMimeType() {
  return _mimeType.find(_firstLine[EXT]) != _mimeType.end();
}

void Headers::_setMapMimeType() {
  _mimeType["arc"] = "application/octet-stream";
  _mimeType["bin"] = "application/octet-stream";
  _mimeType["form"] = "application/x-www-form-urlencoded";
  _mimeType["css"] = "text/css";
  _mimeType["htm"] = "text/html";
  _mimeType["html"] = "text/html";
  _mimeType["jpeg"] = "image/jpeg";
  _mimeType["jpg"] = "image/jpeg";
  _mimeType["oga"] = "audio/ogg";
  _mimeType["ogv"] = "video/ogg";
  _mimeType["ogx"] = "application/ogg";
  _mimeType["otf"] = "font/otf";
  _mimeType["png"] = "image/png";
  _mimeType["pdf"] = "application/pdf";
}
