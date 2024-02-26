//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/4-socket.hpp"

void Socket::createSocketDescriptor() {
  if ((_sd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    throw(throwMessageErrno("Creation of the socket descriptor of a socket"));
}

void Socket::setSocketOptions() {
  if (setsockopt(_sd, SOL_SOCKET, SO_REUSEADDR /* | SO_REUSEPORT*/,
                 &_optionBuffer, sizeof(_optionBuffer)))
    throw(throwMessageErrno("Set option of a socket"));
}

void Socket::setSocketNonBlocking() {
  if (fcntl(_sd, F_SETFL, O_NONBLOCK) < 0)
    throw(throwMessageErrno("Socket to nonblocking"));
}

void Socket::initAddress(int port) {
  _address.sin_family = AF_INET;
  _address.sin_addr.s_addr = INADDR_ANY;
  _address.sin_port = htons(port);
}

void Socket::bindSocket() {
  if (bind(_sd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
    throw(throwMessageErrno("Bind socket"));
}

void Socket::socketListener() {
  if (listen(_sd, MAX_CONNECTION) < 0)
    throw(throwMessageErrno("Set socket to listener"));
}

static void setServersConfig(struct Server &server, mapStrServ &serversConfig) {
  for (vecStrIt i = server.names.begin(); i != server.names.end(); ++i)
    serversConfig[*i] = server;
}

Socket::Socket(struct Server &server)
    : _sd(-1), _optionBuffer(), _serversConfig(), _defaultServer(NULL) {
  try {
    createSocketDescriptor();
    setSocketOptions();
    setSocketNonBlocking();
    initAddress(server.port);
    bindSocket();
    socketListener();
  } catch (const std::exception &e) {
    throwError(e);
    throw(throwMessage("Stop program"));
  }
  setServersConfig(server, _serversConfig);
}

static void setServersConfigIf(struct Server &server,
                               mapStrServ &serversConfig) {
  for (vecStrIt i = server.names.begin(); i != server.names.end(); ++i)
    if (serversConfig.find(*i) == serversConfig.end())
      serversConfig[*i] = server;
}

void Socket::add(struct Server &server) {
  setServersConfigIf(server, _serversConfig);
}

Socket::Socket(const Socket &copy)
    : _sd(copy._sd), _optionBuffer(copy._optionBuffer), _address(copy._address),
      _serversConfig(copy._serversConfig), _defaultServer(NULL) {}

Socket::~Socket() {}

Socket &Socket::operator=(const Socket &rhs) {
  if (this != &rhs) {
    _sd = rhs._sd;
    _optionBuffer = rhs._optionBuffer;
    _address = rhs._address;
    _serversConfig = rhs._serversConfig;
    _defaultServer = rhs._defaultServer;
  }
  return (*this);
}

int Socket::getSocketDescriptor() const { return _sd; }

mapStrServ &Socket::getServerConfiguration() { return _serversConfig; }

bool Socket::isDefault() {
  if (!_defaultServer) {
    for (mapStrServIt i = _serversConfig.begin(); i != _serversConfig.end();
         ++i) {
      if (i->second.isDefault()) {
        _defaultServer = &i->second;
        return true;
      }
    }
  }
  return false;
}

Client::Client(Socket &server, const string &client_ip, int sd)
    : Socket(server), _client_ip(client_ip), _information_received(false),
      _request() {
  _sd = sd;
}

Client::Client(const Client &copy)
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