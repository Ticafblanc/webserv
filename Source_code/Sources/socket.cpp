//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/socket.hpp"

void Socket::createSocketDescriptor() {
  if ((this->_sd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    throw(throwMessageErrno("Creation of the socket descriptor of a socket"));
}

void Socket::setSocketOptions() {
  if (setsockopt(this->_sd, SOL_SOCKET, SO_REUSEADDR /* | SO_REUSEPORT*/,
                 &this->_option_buffer, sizeof(this->_option_buffer)))
    throw(throwMessageErrno("Set option of a socket"));
}

void Socket::setSocketNonBlocking() {
  if (fcntl(this->_sd, F_SETFL, O_NONBLOCK) < 0)
    throw(throwMessageErrno("Socket to nonblocking"));
}

void Socket::initAddress(int port) {
  this->_address.sin_family = AF_INET;
  this->_address.sin_addr.s_addr = INADDR_ANY;
  this->_address.sin_port = htons(port);
}

void Socket::bindSocket() {
  if (bind(this->_sd, (struct sockaddr *)&this->_address,
           sizeof(this->_address)) < 0)
    throw(throwMessageErrno("Bind socket"));
}

void Socket::socketListener() {
  if (listen(this->_sd, MAX_CONNECTION) < 0)
    throw(throwMessageErrno("Set socket to listener"));
}

Socket::Socket(struct Server &server)
    : _sd(-1), _option_buffer(), _server_config(server) {
  try {
    this->createSocketDescriptor();
    this->setSocketOptions();
    this->setSocketNonBlocking();
    this->initAddress(server.port);
    this->bindSocket();
    this->socketListener();
  } catch (const std::exception &e) {
    throwError(e);
    throw(throwMessage("Stop program"));
  }
}

Socket::Socket(int sd, struct Server &server)
    : _sd(sd), _server_config(server) {}

//Socket::Socket(int sd) : _sd(sd) {}

Socket::Socket(const Socket &copy)
    : _sd(copy._sd), _option_buffer(copy._option_buffer),
      _address(copy._address), _server_config(copy._server_config) {}

Socket::~Socket() {}

Socket &Socket::operator=(const Socket &rhs) {
  if (this != &rhs) {
    this->_sd = rhs._sd;
    this->_option_buffer = rhs._option_buffer;
    this->_address = rhs._address;
    this->_server_config = rhs._server_config;
  }
  return (*this);
}

int Socket::getSocketDescriptor() { return (this->_sd); }

struct Server &Socket::getServerConfiguration() {
  return (this->_server_config);
}

void Socket::setToDefault() {
  this->_server_config.names.push_back("default_server");
}
