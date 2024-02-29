//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_SELECT_HPP
#define WEBSERV_SELECT_HPP

#include "8-reponse.hpp"

typedef SocketManager<Socket> socketServer;
typedef SocketManager<Client> socketClient;
typedef socketServer::mapSock mapSockServer;
typedef socketServer::mapSockIt mapSockServerIt;
typedef socketClient::mapSock mapSockClient;
typedef socketClient::mapSockIt mapSockClientIt;

class Select {

public:
  explicit Select(SocketManager<Socket> &sm, SocketManager<Client> &cm);
  Select(const Select &copy);
  ~Select();
  Select &operator=(const Select &op);

  void loop();
  void deinit();

private:
  static Select *_this;
  volatile sig_atomic_t _run;
  socketServer &_serverManager;
  socketClient &_clientManager;
  map<int, Headers> _headers;
  map<int, Request> _request;
  map<int, Response> _response;
  map<int, CGI> _cgi;
  setInt _sds;
  vecInt _sdClt;
  vecInt _sdServ;
  vector<fd_set> _fdSets;

  static void endServer(int signal);
  void udateData();
  void init();

  void check(int ret);

  pair<int, sockaddr_in> acceptConnection(const int &sd);
  void createSocketPair(Client &clt);
  void closeConnection(const int &sd);

  bool sendMessage(int &r, Client &clt);
  bool acceptClient(int &r, Socket &srv);
  bool recvMessage(int &r, Client &clt);

  static ssize_t recvBuffer(int &r, Client &clt);
  static bool recvHeader(Client &clt);
  ssize_t sendBuffer(int &r, Client &clt);

  template <typename T>
  void forLoopSd(map<int, T> &mS, fd_set &fd, vecInt &vecSd,
                 bool (Select::*p)(int &r, T &t)) {
    for (vecIntIt it = vecSd.begin(); it != vecSd.end(); ++it) {
      try {
        int ret = *it;
        if ((this->*p)(ret, mS[ret]))
          FD_SET(ret, &fd);
      } catch (const ErrnoException &e) {
        if (const Exception * Ex = dynamic_cast<const Exception *>(&e)) {
          FD_SET(*it, &_fdSets[WRITE_SDS]);
          _headers[*it].setStatus(Ex->getErrorPage());
          Ex->print();
        }else
          e.print();
      }
    }
  }

  template <class T> void forLoopSock(T &mS, int *ret, vecInt &vecSd) {
    for (typename T::iterator it = mS.begin(); (*ret) && it != mS.end(); ++it) {
      if (FD_ISSET(it->first, &_fdSets[TMP_READ_SDS])) {
        if (find(vecSd.begin(), vecSd.end(), it->first) == end(vecSd))
          vecSd.push_back(it->first);
        (*ret)--;
      }
    }
  }
};

#endif // WEBSERV_SELECT_HPP
