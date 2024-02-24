//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_SOCKETMANAGER_HPP
#define WEBSERV_SOCKETMANAGER_HPP

#include "client.hpp"
#include "socket.hpp"

template <class T = Socket> class SocketManager {

private:
  vector<T> _sockets;

public:
  typedef vector<T> vecSock;
  typedef typename vecSock::iterator vecSockIt;
  SocketManager() : _sockets() {}
  SocketManager(const SocketManager &copy) : _sockets(copy._sockets) {}
  ~SocketManager() {}

  SocketManager &operator=(const SocketManager &op) {
    if (&op == this)
      return (*this);
    this->_sockets = op._sockets;
    return (*this);
  }

  /**
   *  @brief Add a socket to the socket manager.
   *
   *  @param socket the socket.
   */
  void registerSocket(T socket) { this->_sockets.push_back(socket); }

  fd_set getSDSet() {
    fd_set sockets_fds_set;

    FD_ZERO(&sockets_fds_set);
    for (typename std::vector<T>::iterator it = this->_sockets.begin();
         it != this->_sockets.end(); it++)
      FD_SET(it->getSocketDescriptor(), &sockets_fds_set);
    return (sockets_fds_set);
  }

  int getLastSD() { return _sockets.back().getSocketDescriptor(); }

  T &getBySD(int sd) {
    for (typename std::vector<T>::iterator it = this->_sockets.begin();
         it != this->_sockets.end(); it++) {
      if (it->getSocketDescriptor() == sd)
        return (*it);
    }
    throw(throwMessage("SD not found."));
  }

  T &getBySDandHost(int sd, std::string host) {
    for (typename std::vector<T>::iterator it = this->_sockets.begin();
         it != this->_sockets.end(); it++)
      if (it->getSocketDescriptor() == sd)
        for (size_t j = 0; j < it->getServerConfiguration().names.size(); j++)
          if (it->getServerConfiguration().names[j] == host)
            return (*it);
    for (typename std::vector<T>::iterator it = this->_sockets.begin();
         it != this->_sockets.end(); it++)
      if (it->getSocketDescriptor() == sd)
        for (size_t j = 0; j < it->getServerConfiguration().names.size(); j++)
          if (it->getServerConfiguration().names[j] == "default_server")
            return (*it);
    return (this->getBySD(sd));
  }

  static pair<bool, int> checkSameListen(Server &server, vecSock &sock) {
    for (vecSockIt itT = sock.begin(); itT != sock.end(); ++itT) {
      if (itT->getServerConfiguration().port == server.port &&
          itT->getServerConfiguration().host == server.host)
        return make_pair(false, itT->getSocketDescriptor());
    }
    return make_pair(true, 0);
  }

  void setServerSocket(vecServ &server) {
    for (vecServIt itServ = server.begin(); itServ != server.end(); ++itServ) {
      pair<bool, int> ret = checkSameListen(*itServ, _sockets);
      if (ret.first)
        registerSocket(Socket(*itServ));
      else
        registerSocket(Socket(ret.second, *itServ));
    }
  }

  vector<T> &getSockets() { return (this->_sockets); }

  /**
   *  @brief Give a boolean that contain if the socket descriptor
   *  given in param is a socket descriptor of a socket of the
   *  socket manager.
   *
   *  @param socket_descriptor the socket descriptor to check.
   *  @return true if the socket descriptor is one of the socket
   *      manager, false otherwise.
   */
  bool hasSD(int socket_descriptor) {
    typename vector<T>::iterator it = this->_sockets.begin();

    for (; it != this->_sockets.end(); it++) {
      if (it->getSocketDescriptor() == socket_descriptor)
        return (true);
    }
    return (false);
  }
};

#endif // WEBSERV_SOCKETMANAGER_HPP
