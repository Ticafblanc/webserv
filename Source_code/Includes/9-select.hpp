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

  class Exception : public ErrnoException {
  private:
    int _sd;
    string _errorPage;

  public:
    Exception(const string &msg) throw();
    Exception(const string &msg, const int &sd,
              const string &errorPage) throw();
    Exception(const Exception &) throw();
    Exception &operator=(const Exception &) throw();
    virtual ~Exception() throw();
  };

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
  vecInt _sdCltRecv;
  vecInt _sdCltSend;
  vecInt _sdServ;
  vector<fd_set> _fdSets;

  static void endServer(int signal);
  void udateData();
  void init();

  bool check(int ret);
  void checkClient();
  void checkServer();

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
      } catch (const std::exception &e) {
        _headers[*it].setFirstLine(STATUS_CODE, "500");
        FD_SET(*it, &fd);
        throwError(e);
      }
    }
  }
};

#endif // WEBSERV_SELECT_HPP
