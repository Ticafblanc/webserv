//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/5-headers.hpp"

Headers::Headers() : _firstLine(5), _headerFields(), _client(NULL) {}

Headers::Headers(Client &clt) : _firstLine(5), _headerFields(), _client(&clt) {}

Headers::Headers(const Headers &copy)
    : _firstLine(copy._firstLine), _headerFields(copy._headerFields),
      _client(copy._client) {}

Headers::~Headers() {}

Headers &Headers::operator=(const Headers &rhs) {
  if (this != &rhs) {
    _firstLine = rhs._firstLine;
    _headerFields = rhs._headerFields;
    _client = rhs._client;
  }
  return *this;
}

bool Headers::extractData() {
  istringstream b(_client->getHeader());
  string line, token, value;
  size_t i = 0;
  if (getline(b >> ws, line, '\r')) {
    istringstream fl(line);
    fl >> ws >> _firstLine[METHOD] >> _firstLine[PATH] >> _firstLine[HTTP_V];
  } else
    return false;
  while (getline(b >> ws, line, '\r') && ++i) {
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
  if (extractData()) {
    _firstLine[STATUS_CODE] = "400";
  }
}

vecStr &Headers::getFirstLine() { return _firstLine; }
mapStrStr &Headers::getHeaderFields() { return _headerFields; }
Client *Headers::getClient() { return _client; }
