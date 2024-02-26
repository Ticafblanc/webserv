//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_SOCKET_HPP
#define WEBSERV_SOCKET_HPP

#include "3-configuration.hpp"

#define MSG_NOSIGNAL_ 0

typedef map<string, struct Server &> mapStrServ;
typedef mapStrServ::const_iterator mapStrServIt;

class Socket {

protected:
  int _sd;
  int _optionBuffer;
  struct sockaddr_in _address;
  mapStrServ _serversConfig;
  Server *_defaultServer;

  /**
   *  @brief Create the socket and give is socket descriptor.
   *  The socket is under IPV4 protocol (PF_INET / AF_INET)
   *  and is a support of dialog guaranteeing the data
   *  integrity.
   *
   * 	@throw if the socket can't be create.
   */
  void createSocketDescriptor();

  /**
   *  @brief Set the options socket.
   *  Set the socket to be at the Socket level and
   *  set that the address is an reusable local address,
   *  same for port.
   *
   * 	@throw if the options can't be set to the socket.
   */
  void setSocketOptions();

  /**
   * 	@brief Set the socket to be nonblocking socket.
   *
   * 	@throw if the attributes can't be set to the socket.
   */
  void setSocketNonBlocking();

  /**
   * 	@brief Initialisation of the address informations.
   * 	It's based on the same protocol than the socket,
   * 	the address is attached to any of the possibilities and
   * 	the port defined is the configuration file.
   *
   * 	@param port the port to bin the addres.
   */
  void initAddress(int port);

  /**
   * 	@brief Bind the socket to the address.
   *
   * 	@throw if the socket can't be bind.
   */
  void bindSocket();

  /**
   * 	@brief Set the socket to be a listener.
   * 	That permetted that it can use accept() the
   * 	incoming connections.
   *
   * @throw if the socket can't be set to listener.
   */
  void socketListener();

public:
  explicit Socket(struct Server &server);
  Socket(const Socket &copy);
  virtual ~Socket();
  Socket &operator=(const Socket &op);

  void add(struct Server &server);
  int getSocketDescriptor() const;
  mapStrServ &getServerConfiguration();
  bool isDefault();
};

class Client : public Socket {
private:
  string _client_ip;
  bool _information_received;
  string _request;

public:
  Client(Socket &server, const string &client_ip, int sd);
  Client(const Client &copy);
  virtual ~Client();
  Client &operator=(const Client &rhs);

  string &getRequest();
  string getClientIp();
  bool informationReceived();
  void setReceived(bool val);
};

template <class T = Socket> class SocketManager {
public:
  typedef map<int, T> mapSock;
  typedef typename mapSock::iterator mapSockIt;

private:
  mapSock _sockets;
  Socket *_defaultServer;

public:
  SocketManager() : _sockets(), _defaultServer(NULL) {}
  SocketManager(const SocketManager &copy)
      : _sockets(copy._sockets), _defaultServer(copy._defaultServer) {}
  ~SocketManager() {}

  SocketManager &operator=(const SocketManager &rhs) {
    if (this != &rhs) {
      _sockets = rhs._sockets;
      _defaultServer = rhs._defaultServer;
    }
    return *this;
  }

  /**
   *  @brief Add a socket to the socket manager.
   *
   *  @param socket the socket.
   */
  void registerSocket(const T &socket) {
    _sockets[socket.getSocketDescriptor()] = socket;
    if (!_defaultServer && socket.isDefault())
      _defaultServer = &socket;
  }

  int getLastSD() { return _sockets.back().getSocketDescriptor(); }

  T &getBySD(const int &sd) { return _sockets[sd]; }

  T &getBySDandHost(const int &sd, const string &host) {
    mapStrServ &tmp = _sockets[sd].getServerConfiguration();
    if (tmp.find(host) == tmp.end())
      return;
  }

  static pair<bool, int> checkSameListen(Server &server, mapSock &sock) {
    for (mapSockIt itT = sock.begin(); itT != sock.end(); ++itT) {
      if (itT->second.getServerConfiguration().port == server.port &&
          itT->second.getServerConfiguration().host == server.host)
        return make_pair(false, itT->first);
    }
    return make_pair(true, 0);
  }

  void setServerSocket(vecServ &server) {
    for (vecServIt itServ = server.begin(); itServ != server.end(); ++itServ) {
      pair<bool, int> ret = checkSameListen(*itServ, _sockets);
      if (ret.first)
        registerSocket(Socket(*itServ));
      else
        _sockets[ret.second].add(*itServ);
    }
  }

  mapSock &getSockets() { return (_sockets); }

  /**
   *  @brief Give a boolean that contain if the socket descriptor
   *  given in param is a socket descriptor of a socket of the
   *  socket manager.
   *
   *  @param socket_descriptor the socket descriptor to check.
   *  @return true if the socket descriptor is one of the socket
   *      manager, false otherwise.
   */
  bool hasSD(const int &sd) { return _sockets.find(sd) != _sockets.end(); }
};

#endif // WEBSERV_SOCKET_HPP
