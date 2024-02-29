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

bool Headers::extractFirstLine() {
  string line;
  if (getline(_header >> ws, line, '\r')) {
    istringstream fl(line);
    fl >> ws >> _firstLine[METHOD] >> _firstLine[PATH] >> _firstLine[HTTP_V];
    if (_firstLine[HTTP_V] != "HTTP/1.1") {
      setFirstLine(STATUS_CODE, "505");
      return false;
    }
    return true;
  }
  return false;
}
bool Headers::extractData() {
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
  return i == _headerFields.size();
}

void Headers::parse() {
  _header.str() = _client->getHeader();
  if (extractFirstLine()) {
    if (extractData()) {
      _client->updateRessource(_headerFields["Host"], _firstLine[PATH]);
      if (_client->allowMethod(_firstLine[METHOD]))
        setFirstLine(STATUS_CODE, "405");
    }
    setFirstLine(STATUS_CODE, "400");
  }
  if (!_firstLine[STATUS_CODE].empty())
    _client->setReceived(true);
}

static string extractQueryString(const string &uri) {
  size_t pos = uri.find('?');
  if (pos != std::string::npos)
    return uri.substr(pos + 1);
  return "";
}

static char *cast(string line) {
  char *c = new char[line.size()];
  return c;
}

vector<char *> Headers::getCgiEnv() {
  std::vector<char *> env;
  execve(env[0], env.data(), env.data());
  env.push_back(cast("REQUEST_METHOD=" + _firstLine[METHOD]));
  env.push_back(cast("QUERY_STRING=" + extractQueryString(_firstLine[PATH])));
  for (mapStrStrIt it = _headerFields.begin(); it != _headerFields.end();
       ++it) {
    string envVar = "HTTP_" + it->first;
    replace(envVar.begin(), envVar.end(), '-', '_');
    transform(envVar.begin(), envVar.end(), envVar.begin(), ::toupper);
    envVar += "=" + it->second;
    env.push_back(cast(envVar));
  }
  return env;
}

vecStr &Headers::getFirstLine() { return _firstLine; }
mapStrStr &Headers::getHeaderFields() { return _headerFields; }
Client *Headers::getClient() { return _client; }
void Headers::setFirstLine(const int &pos, const string &value) {
  _firstLine[pos] = value;
}
bool Headers::isCloseRequest() {
  mapStrStrIt it = _headerFields.find("Connection");
  if (it != _headerFields.end())
    return it->second == "close";
  return false;
}
