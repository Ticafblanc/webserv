//
// Created by Matthis DoQuocBao on 2024-02-25.
//

#include "../Includes/8-reponse.hpp"

Response::Response() : _headers(), _client(NULL) {}

Response::Response(Headers &headers)
    : _headers(&headers), _client(headers.getClient()) {}

Response::Response(const Response &other)
    : _headers(other._headers), _client(other._client) {}

Response::~Response() {}

Response &Response::operator=(const Response &other) {
  if (this != &other) {
    _headers = other._headers;
    _client = other._client;
  }
  return (*this);
}

void Response::manager() {
  cout << "Response manager " << _client->getSd() << endl;
  if (_headers->getFirstLine()[STATUS_CODE].empty() ||
      !_client->getResponse().empty())
    return;
  _client->getResponse() = _headers->getHeaderReponse();
  _client->getResponse() += _client->getBody();
}
