//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_SOCKET_HPP
#define WEBSERV_SOCKET_HPP

#include "3-configuration.hpp"

#define MSG_NOSIGNAL_ 0

typedef map<string, struct Server *> mapStrServ;
typedef mapStrServ::const_iterator mapStrServIt;

class Socket {

protected:
  string _ipAddress;
  uint16_t _port;
  int _sd;
  int _optionBuffer;
  struct sockaddr_in _address;
  mapStrServ _serversConfig;
  Server *_defaultServer;
  void createSocketDescriptor();
  void setSocketOptions();
  void setSocketNonBlocking();
  void initAddress();
  void bindSocket();
  void socketListener();
  void getSockaddrIn();

public:
  Socket();
  explicit Socket(struct Server &server, Server *defaultServer);
  Socket(const Socket &copy);
  virtual ~Socket();
  Socket &operator=(const Socket &op);

  void add(struct Server &server);
  int getSd() const;
  const string &getIpAddress() const;
  const uint16_t &getPort() const;
  mapStrServ &getServerConfiguration();
  bool isDefault();
  Server *getDefaultServer() const;
  Server *getServerByHost(const string &host);
  virtual void closeSd();
};

class Client : public Socket {
protected:
  bool _endRecv;
  string _header;
  string _body;
  vecStr _request;
  string _response;
  string _ressourcePath;
  Server *_server;
  Location *_location;
  int _sds[2];

public:
  Client();
  Client(Socket &server, const sockaddr_in &address, int sd);
  Client(const Client &copy);
  virtual ~Client();
  Client &operator=(const Client &rhs);

  void reset();
  void updateRessource(const string & host, const string & path);
  void setRessourcePath(const string &path);
  bool allowMethod(const string & method);
  string &getHeader();
  string &getBody();
  vecStr &getRequest();
  string &getResponse();
  bool isEndRecv() const;
  void setReceived(bool val);
  Server *getServer() const;
  void setServer(Server *server);
  Location *getLocation() const;
  void setLocation(Location *location);
  int *getSds() ;
  string &getRessourcePath();
  void closeSd();

};

template <class T = Socket> class SocketManager {
public:
  typedef map<int, T> mapSock;
  typedef typename mapSock::iterator mapSockIt;

private:
  mapSock _sockets;
  Socket *_defaultSocket;

public:
  SocketManager() : _sockets(), _defaultSocket(NULL) {}
  SocketManager(const SocketManager &copy)
      : _sockets(copy._sockets), _defaultSocket(copy._defaultSocket) {}
  ~SocketManager() {}

  SocketManager &operator=(const SocketManager &rhs) {
    if (this != &rhs) {
      _sockets = rhs._sockets;
      _defaultSocket = rhs._defaultSocket;
    }
    return *this;
  }

  void registerSocket(const T &socket) { _sockets[socket.getSd()] = socket; }

  void registerSocketAndCheckDefaultServer(const Socket &socket) {
    registerSocket(socket);
    if (!_defaultSocket && _sockets[socket.getSd()].isDefault())
      _defaultSocket = &_sockets[socket.getSd()];
  }

  Socket &getSocketBySD(const int &sd) {
    if (hasSD(sd))
      return _sockets[sd];
    return *_defaultSocket;
  }

  Client &getClientBySD(const int &sd) { return _sockets[sd]; }

  static pair<bool, int> checkSameListen(Server &server, mapSock &sock) {
    for (mapSockIt itT = sock.begin(); itT != sock.end(); ++itT) {
      if (itT->second.getPort() == server.port &&
          itT->second.getIpAddress() == server.ipAddress)
        return make_pair(false, itT->first);
    }
    return make_pair(true, 0);
  }

  void setServerSocket(vecServ &server) {
    Server *defaultServer = NULL;
    if (server.begin()->isDefault())
      defaultServer = &*server.begin();
    for (vecServIt itServ = server.begin(); itServ != server.end(); ++itServ) {
      pair<bool, int> ret = checkSameListen(*itServ, _sockets);
      if (ret.first)
        registerSocketAndCheckDefaultServer(Socket(*itServ, defaultServer));
      else
        _sockets[ret.second].add(*itServ);
    }
  }

  bool closeSocket(const int &sd) {
    if (hasSD(sd)) {
      _sockets[sd].closeSd();
      _sockets.erase(sd);
      return true;
    }
    return false;
  }

  mapSock &getSockets() { return _sockets; }
  bool hasSD(const int &sd) { return _sockets.find(sd) != _sockets.end(); }
};

#endif // WEBSERV_SOCKET_HPP
