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
  if (!_client->allowMethod(_headers->getFirstLine()[METHOD]))
    throw Exception("Headers not complete", _client->getSd(), "405");
  map<string, pManage> mapTmp;
  mapTmp["GET"] = &Request::_get;
  mapTmp["HEAD"] = &Request::_head;
  mapTmp["POST"] = &Request::_post;
  mapTmp["DELETE"] = &Request::_delete;
  _manage = mapTmp[_headers->getFirstLine()[METHOD]];
}

void Request::_checkRessource(bool (*p)(const string &)) {
  if (!p(_client->getRessourcePath())) {
    if (isDirectory(_client->getRessourcePath())) {
      if (isFile(_client->getRessourcePath() + _client->getLocation()->index)) {
        _client->getRessourcePath() += _client->getLocation()->index;
        return;
      }
      throw Exception("uri not found", _client->getSd(), "404");
    }
    throw Exception("Permission fail", _client->getSd(), "403");
  }
}

void Request::_head() {
  cout << "head " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  _checkRessource(checkPermissionR);
  _headers->setStatus("204");
  _complete = true;
}

void Request::_get() {
  cout << "get " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  _checkRessource(checkPermissionR);
  ifstream ifs(_client->getRessourcePath().c_str());
  if (!ifs.is_open())
    throw Exception("fail to open file " + _client->getRessourcePath(),
                    _client->getSd(), "500");
  _client->getBody() = string((std::istreambuf_iterator<char>(ifs)),
                              std::istreambuf_iterator<char>());
  _headers->setStatus("200");
  _complete = true;
}

void Request::_delete() {
  cout << "delete " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  _checkRessource(checkPermissionRW);
  if (remove(_client->getRessourcePath().c_str()))
    throw Exception("fail to delete file " + _client->getRessourcePath(),
                    _client->getSd(), "500");
  _headers->setStatus("204");
  _complete = true;
}

void Request::_post() {
  cout << "put " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  if (isFile(_client->getRessourcePath())) {
    if (!checkPermissionW(_client->getRessourcePath()))
      throw Exception("no permission for Ressource ", _client->getSd(), "403");
    _headers->setStatus("201");
  } else
    _headers->setStatus("204");
  _manage = &Request::_continuePost;
}

void Request::_continuePost() {
  cout << "contunue post " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  if (_client->getBody().length() == _headers->getContentLength()){
    ofstream ofs(_client->getRessourcePath(),
                 std::ios::out | std::ios::trunc | ios::binary);
    if (!ofs.is_open())
      throw Exception("Fail to create fail", _client->getSd(), "500");
    ofs << _client->getBody();
  }else{
    _client->getBody() += *_client->getRequest().rbegin();
  }
  _complete = true;
}
