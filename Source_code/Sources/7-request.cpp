//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/7-request.hpp"

Request::Request()
    : _headers(), _client(NULL), _complete(false), _manage(NULL) {}

Request::Request(Headers &headers)
    : _headers(&headers), _client(headers.getClient()), _complete(false),
      _manage(NULL) {}

Request::Request(const Request &other)
    : _headers(other._headers), _client(other._client), _complete(false),
      _manage(other._manage) {}

Request::~Request() {}

Request &Request::operator=(const Request &other) {
  if (this != &other) {
    _headers = other._headers;
    _client = other._client;
    _complete = other._complete;
    _manage = other._manage;
  }
  return (*this);
}
bool Request::manageIsNull() const { return !_manage; }
void Request::resetManage(pManage m) { _manage = m; }
void Request::_reset() {
  _client->getHeader().clear();
  _client->getRequest().clear();
  _manage = NULL;
  _complete = true;
}

void Request::manager() {
  cout << "request manager " << _client->getSd() << endl;
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
  mapTmp["POST"] = &Request::_post;
  mapTmp["DELETE"] = &Request::_delete;
  _manage = mapTmp[_headers->getFirstLine()[METHOD]];
}

void Request::_get() {
  cout << "get " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  try {
    checkRessource(_client->getRessourcePath(), _client->getLocation()->index,
                   _client->getSd(), checkPermissionR);
    ifstream ifs(_client->getRessourcePath().c_str());
    if (!ifs.is_open())
      throw Exception("fail to open file " + _client->getRessourcePath(),
                      _client->getSd(), "500");
    _client->getBody() = string((std::istreambuf_iterator<char>(ifs)),
                                std::istreambuf_iterator<char>());
  } catch (const Exception &Ex) {
    if (!_client->getLocation()->uriReturn.first.empty())
      throw Exception("Redirect", _client->getSd(),
                      _client->getLocation()->uriReturn.first);
    if (!_client->getLocation()->autoindex ||
        !autoIndexToHtml(_client->getRessourcePath(), _client->getBody()))
      throw Ex;
    else
      _headers->setFirstLine(EXT, "html");
  }
  _headers->setStatus("200");
  _reset();
}

void Request::_delete() {
  cout << "delete " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  checkRessource(_client->getRessourcePath(), _client->getLocation()->index,
                 _client->getSd(), checkPermissionW);
  if (remove(_client->getRessourcePath().c_str()))
    throw Exception("fail to delete file " + _client->getRessourcePath(),
                    _client->getSd(), "500");
  _headers->setStatus("204");
  _reset();
}

string status;
void Request::_post() {
  cout << "post " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  if (!_headers->isValidMimeType())
    throw Exception("invalid mime type", _client->getSd(), "415");
  if (isFile(_client->getRessourcePath())) {
    if (!checkPermissionW(_client->getRessourcePath()))
      throw Exception("no permission for Ressource ", _client->getSd(), "403");
    status = "201";
  } else
    status = "204";
  _manage = &Request::_continuePost;
}

void Request::_continuePost() {
  cout << "contunue post " << _headers->getFirstLine()[URI] << " "
       << _client->getRessourcePath() << endl;
  if (_client->getBody().length() == _headers->getContentLength()) {
    ofstream ofs(_client->getRessourcePath(),
                 std::ios::out | std::ios::trunc | ios::binary);
    if (!ofs.is_open())
      throw Exception("Fail to create fail", _client->getSd(), "500");
    ofs << _client->getBody();
    _headers->setStatus(status);
    _reset();
  }
  _complete = true;
}
