//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/client.hpp"

Client::Client(Socket *parent, string client_ip, int sd)
    : Socket(sd), _parent_socket(parent), _client_ip(client_ip),
      _information_received(false), _request() {}

Client::Client(const Client &copy)
    : Socket(copy._sd), _parent_socket(copy._parent_socket),
      _client_ip(copy._client_ip),
      _information_received(copy._information_received),
      _request(copy._request) {}

Client::~Client() {}
Client &Client::operator=(const Socket &op) {
  (void)op;
  return (*this);
}

Socket *Client::getParent() { return (this->_parent_socket); }

std::string &Client::getRequest() { return (this->_request); }

std::string Client::getClientIp() { return (this->_client_ip); }

bool Client::informationReceived() { return (this->_information_received); }

void Client::setReceived(bool val) {
  this->_information_received = val;
  if (val)
    Log("Request received from : " + itoa(this->_sd));
}
