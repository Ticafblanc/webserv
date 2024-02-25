//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/client.hpp"

Client::Client(Socket &server, const string &client_ip, int sd)
    : Socket(server), _client_ip(client_ip), _information_received(false),
      _request() {
  _sd = sd;
}

Client::Client(Client &copy)
    : Socket(copy), _client_ip(copy._client_ip),
      _information_received(copy._information_received),
      _request(copy._request) {}

Client::~Client() {}

Client &Client::operator=(const Client &rhs) {
  if (this != &rhs) {
    Socket::operator=(rhs);
    _client_ip = rhs._client_ip;
    _information_received = rhs._information_received;
    _request = rhs._request;
  }
  return *this;
}

std::string &Client::getRequest() { return (this->_request); }

std::string Client::getClientIp() { return (this->_client_ip); }

bool Client::informationReceived() { return (this->_information_received); }

void Client::setReceived(bool val) { this->_information_received = val; }
