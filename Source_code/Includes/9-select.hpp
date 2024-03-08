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
  timeval _timeOut;
  timeval *_timeOutP;
  socketServer &_serverManager;
  socketClient &_clientManager;
  map<int, Headers> _headers;
  map<int, Request> _request;
  map<int, Response> _response;
  map<int, CGIChild> _cgiChild;
  map<int, CGIParent> _cgiParent;
  setInt _sds;
  queInt _sdCltRecv;
  queInt _sdCltSend;
  queInt _sdServ;
  vector<fd_set> _fdSets;

  static void endServer(int signal);
  void udateData();
  void init();

  void check(int ret);

  pair<int, sockaddr_in> acceptConnection(const int &sd);
  void createSocketPair(Client &clt);
  void closeConnection(const int &sd);
  void checkClient(mapSockClient &clts, queInt sdCltRecv, queInt sdCltSend);
  bool sendMessage(int &r, Client &clt);
  bool acceptClient(int &r, Socket &srv);
  bool recvMessage(int &r, Client &clt);

  static ssize_t recvBuffer(int &r, Client &clt);
  static bool recvHeader(Client &clt);

  template <typename T>
  void forLoopSd(map<int, T> &mS, int flagSet, int flagClr, queInt &vecSd,
                 bool (Select::*p)(int &r, T &t)) {
    while (!vecSd.empty()) {
      int ret = vecSd.front();
      vecSd.pop();
      try {
        if ((this->*p)(ret, mS[ret])) {
          FD_SET(ret, &_fdSets[flagSet]);
          FD_CLR(ret, &_fdSets[flagClr]);
        }
      } catch (exception &e) {
        if (Exception *Ex = dynamic_cast<Exception *>(&e)) {
          FD_SET(ret, &_fdSets[WRITE_SDS]);
          _headers[ret].setStatus(Ex->getErrorPage());
          _headers[ret].getFirstLine()[EXT] = "html";
          _clientManager.getSockets()[ret].getBody() = defaultHtml(
              _headers[ret].getFirstLine()[STATUS_CODE],
              _headers[ret].getFirstLine()[RAISON_PHRASE], Ex->print());
          _clientManager.getSockets()[ret].getHeader().clear();
        } else if (ErrnoException *E = dynamic_cast<ErrnoException *>(&e)) {
          E->print();
        } else
          e.what();
      }
    }
  }

  template <class T>
  void forLoopSock(T &mS, int *ret, int flag, queInt &vecSd) {
    for (typename T::iterator it = mS.begin(); (*ret) && it != mS.end(); ++it) {
      if (FD_ISSET(it->first, &_fdSets[flag])) {
        vecSd.push(it->first);
        (*ret)--;
      }
    }
  }
};

#endif // WEBSERV_SELECT_HPP
