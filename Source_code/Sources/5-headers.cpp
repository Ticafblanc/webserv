//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/5-headers.hpp"

Headers::Headers() : _firstLine(5), _headerFields(), _client(NULL), _header() {}

Headers::Headers(Client &clt) : _firstLine(5), _headerFields(), _client(&clt) {}

Headers::Headers(const Headers &copy)
    : _firstLine(copy._firstLine), _headerFields(copy._headerFields),
      _client(copy._client), _header() {}

Headers::~Headers() {}

Headers &Headers::operator=(const Headers &rhs) {
  if (this != &rhs) {
    _firstLine = rhs._firstLine;
    _headerFields = rhs._headerFields;
    _client = rhs._client;
    _header.str() = rhs._header.str();
  }
  return *this;
}

void Headers::extractFirstLine() {
  string line;
  if (getline(_header >> ws, line, '\r')) {
    istringstream fl(line);
    fl >> ws >> _firstLine[METHOD] >> _firstLine[PATH] >> _firstLine[HTTP_V];
  }
  if (_firstLine[HTTP_V] != "HTTP/1.1")
    throw Exception("Http version not supported", _client->getSd(), "505");
}
void Headers::extractData() {
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
  if (i != _headerFields.size())
    throw Exception("Headers not complete", _client->getSd(), "400");
}

void Headers::parse() {
  _header = istringstream(_client->getHeader());
  extractFirstLine();
  extractData();
  _client->updateRessource(_headerFields["Host"], _firstLine[PATH]);
  if (!_client->allowMethod(_firstLine[METHOD]))
    throw Exception("Headers not complete", _client->getSd(), "405");
}

static string extractQueryString(const string &uri) {
  size_t pos = uri.find('?');
  if (pos != std::string::npos)
    return uri.substr(pos + 1);
  return "";
}

static string extractPath(const string &uri) {
  size_t pos = uri.find('?');
  if (pos != std::string::npos)
    return uri.substr(0, pos);
  return "";
}

static string extractExt(const string &uri) {
  string path = extractPath(uri);
  size_t pos = path.find_last_of('.');
  if (pos != std::string::npos)
    return path.substr(pos);
  return "";
}

static char *cast(string line) {
  char *c = new char[line.size()];
  return c;
}

vector<char *> Headers::getCgiEnv() {
  vector<char *> env;
  execve(env[0], env.data(), env.data());
  env.push_back(cast("REQUEST_METHOD=" + _firstLine[METHOD]));
  env.push_back(cast("QUERY_STRING=" + extractQueryString(_firstLine[PATH])));
  env.push_back(cast("AUTH_TYPE=Basic"));
  env.push_back(cast("GATEWAY_INTERFACE=CGI/1.1"));
  env.push_back(cast("SCRIPT_NAME=" + extractPath(_firstLine[PATH])));
  env.push_back(cast("SCRIPT_FILENAME=" + extractPath(_firstLine[PATH])));
  env.push_back(cast("PATH_INFO=" + _firstLine[PATH]));
  env.push_back(cast("PATH_TRANSLATED=" + _firstLine[PATH]));
  env.push_back(cast("REMOTE_ADDR=" + _client->getIpAddress()));
  env.push_back(cast("SERVER_NAME=" + getHeaderField("host")));
  env.push_back(cast("SERVER_PORT" + itoa(_client->getPort())));
  env.push_back(cast("HTTP_COOKIE=" + getHeaderField("cookie")));
  env.push_back(cast("DOCUMENT_ROOT=" + _client->getLocation()->root));
  env.push_back(cast("REQUEST_URI=" + _firstLine[PATH]));
  env.push_back(cast("SERVER_PROTOCOL=" + _firstLine[HTTP_V]));
  env.push_back(cast("REDIRECT_STATUS=200"));
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
  string execPath =
      _client->getLocation()->getCgiPath(extractExt(_firstLine[PATH]));
  if (execPath.empty())
    throw Exception("Extension not found", _client->getSd(), "404");
  arg.push_back(cast(execPath));
  arg.push_back(cast(extractPath(_firstLine[PATH])));
  arg.push_back(cast(NULL));
  return arg;
}

vecStr &Headers::getFirstLine() { return _firstLine; }
mapStrStr &Headers::getHeaderFields() { return _headerFields; }
string Headers::getHeaderField(const string &token) {
  mapStrStrIt it = _headerFields.find(token);

  if (it != _headerFields.end())
    return it->second;
  return "";
}
Client *Headers::getClient() { return _client; }
void Headers::setFirstLine(const int &pos, const string &value) {
  _firstLine[pos] = value;
}

void Headers::setStatus(const string &value) {
  _client->setReceived(true);
  setFirstLine(STATUS_CODE, value);
}

bool Headers::isCloseRequest() {
  mapStrStrIt it = _headerFields.find("Connection");
  if (it != _headerFields.end())
    return it->second == "close";
  return false;
}
