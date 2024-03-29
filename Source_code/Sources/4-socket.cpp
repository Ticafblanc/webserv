//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#include "../Includes/4-socket.hpp"

void Socket::createSocketDescriptor() {
  if ((_sd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    throw ErrnoException("Creation of the socket descriptor of a socket");
}

void Socket::setSocketOptions() {
  if (setsockopt(_sd, SOL_SOCKET, SO_REUSEADDR /* | SO_REUSEPORT*/,
                 &_optionBuffer, sizeof(_optionBuffer)))
    throw ErrnoException("Set option of a socket");
}

void Socket::setSocketNonBlocking() {
  if (fcntl(_sd, F_SETFL, O_NONBLOCK) < 0)
    throw ErrnoException("Socket to nonblocking");
}

void Socket::initAddress() {
  _address.sin_family = AF_INET;
  _address.sin_addr.s_addr = inet_addr(_ipAddress.c_str());
  _address.sin_port = htons(_port);
}

void Socket::getSockaddrIn() {
  _ipAddress = inet_ntoa(_address.sin_addr);
  _port = ntohs(_address.sin_port);
}

void Socket::bindSocket() {
  if (bind(_sd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
    throw ErrnoException("Bind socket " + _ipAddress + ":" + itoa(_port));
}

void Socket::socketListener() {
  if (listen(_sd, MAX_CONNECTION) < 0)
    throw ErrnoException("Set socket to listener");
}

void Socket::closeSd() {
  close(_sd);
  _sd = 0;
}

static void setServersConfig(struct Server &server, mapStrServ &serversConfig) {
  for (vecStrIt i = server.names.begin(); i != server.names.end(); ++i)
    serversConfig[*i] = &server;
}

Socket::Socket(struct Server &server, Server *defaultServer)
    : _ipAddress(server.ipAddress), _port(server.port), _sd(-1),
      _optionBuffer(), _serversConfig(), _defaultServer(defaultServer) {
  createSocketDescriptor();
  setSocketOptions();
  setSocketNonBlocking();
  initAddress();
  bindSocket();
  socketListener();
  setServersConfig(server, _serversConfig);
}

static void setServersConfigIf(struct Server &server,
                               mapStrServ &serversConfig) {
  for (vecStrIt i = server.names.begin(); i != server.names.end(); ++i)
    if (serversConfig.find(*i) == serversConfig.end())
      serversConfig[*i] = &server;
}

void Socket::add(struct Server &server) {
  setServersConfigIf(server, _serversConfig);
}

Socket::Socket()
    : _ipAddress(), _port(), _sd(), _optionBuffer(), _address(),
      _serversConfig(), _defaultServer(NULL) {}

Socket::Socket(const Socket &copy)
    : _ipAddress(copy._ipAddress), _port(copy._port), _sd(copy._sd),
      _optionBuffer(copy._optionBuffer), _address(copy._address),
      _serversConfig(copy._serversConfig), _defaultServer(NULL) {}

Socket::~Socket() {}

Socket &Socket::operator=(const Socket &rhs) {
  if (this != &rhs) {
    _ipAddress = rhs._ipAddress;
    _port = rhs._port;
    _sd = rhs._sd;
    _optionBuffer = rhs._optionBuffer;
    _address = rhs._address;
    _serversConfig = rhs._serversConfig;
    _defaultServer = rhs._defaultServer;
  }
  return (*this);
}

int Socket::getSd() const { return _sd; }

mapStrServ &Socket::getServerConfiguration() { return _serversConfig; }

bool Socket::isDefault() {
  if (!_defaultServer) {
    for (mapStrServIt i = _serversConfig.begin(); i != _serversConfig.end();
         ++i) {
      if (i->second->isDefault()) {
        _defaultServer = i->second;
        return true;
      }
    }
  }
  return false;
}

Server *Socket::getServerByHost(const string &host) {
  mapStrServIt pos = _serversConfig.find(host);
  if (pos == _serversConfig.end())
    return _defaultServer;
  return &*pos->second;
}

const string &Socket::getIpAddress() const { return _ipAddress; }
const uint16_t &Socket::getPort() const { return _port; }
Server *Socket::getDefaultServer() const { return _defaultServer; }

Client::Client(Socket &server, const sockaddr_in &address, int sd)
    : Socket(server), _endRecv(false), _header(),_body(), _request(), _server(NULL),
      _location(NULL) {
  _address = address;
  _sd = sd;
  getSockaddrIn();
}

Client::Client()
    : Socket(), _endRecv(), _header(), _body(), _request(), _server(_defaultServer),
      _location(&_server->defaultLocation), _sds() {}

Client::Client(const Client &copy)
    : Socket(copy), _endRecv(copy._endRecv), _header(copy._header), _body(copy._body),
      _request(copy._request), _server(copy._server), _location(copy._location),
      _sds() {
  _sds[0] = copy._sds[0];
  _sds[1] = copy._sds[1];
}

Client::~Client() {}

void Client::closeSd() {
  close(_sds[0]);
  close(_sds[1]);
  _sd = 0;
}

Client &Client::operator=(const Client &rhs) {
  if (this != &rhs) {
    Socket::operator=(rhs);
    _endRecv = rhs._endRecv;
    _header = rhs._header;
    _body = rhs._body;
    _request = rhs._request;
    _server = rhs._server;
    _location = rhs._location;
    _sds[0] = rhs._sds[0];
    _sds[1] = rhs._sds[1];
  }
  return *this;
}

void Client::updateRessource(const string &host, const string &path) {
  _server = getServerByHost(host);
  _location = _server->getLocationByRessource(path);
}

void Client::setRessourcePath(const string &path) {
  _ressourcePath = _location->root.empty() ? _server->root : _location->root;
  _ressourcePath += path.substr(0, _ressourcePath.length());
}

bool Client::allowMethod(const string &method) {
  return _location->methods.find(method) != _location->methods.end();
}

string &Client::getHeader() { return _header; }
string &Client::getBody() { return _body; }
vecStr &Client::getRequest() { return _request; }
Server *Client::getServer() const { return _server; }
void Client::setServer(Server *server) { _server = server; }
Location *Client::getLocation() const { return _location; }
void Client::setLocation(Location *location) { _location = location; }
bool Client::isEndRecv() const { return _endRecv; }

void Client::setReceived(bool val) { _endRecv = val; }
int *Client::getSds() { return _sds; }
string &Client::getRessourcePath(){ return _ressourcePath; }
