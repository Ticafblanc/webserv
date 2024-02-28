//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_SELECT_HPP
#define WEBSERV_SELECT_HPP

#include "8-reponse.hpp"

typedef SocketManager<Socket> socketServer;
typedef SocketManager<Client> socketClient;

class Select {

public:
  explicit Select(SocketManager<Socket> &sm, SocketManager<Client> &cm);
  Select(const Select &copy);
  ~Select();
  Select &operator=(const Select &op);

  void loop();

private:
  static Select *_this;
  volatile sig_atomic_t _run;
  socketServer &_serverManager;
  socketClient &_clientManager;
  map<int, Headers> _headers;
  map<int, Request> _request;
  map<int, Response> _response;
  map<int, CGI> _cgi;

  static void endServer(int signal);

  void checkServer(fd_set *fdSets, int *intVal, set<int> &sds);
  void acceptConnection(const int &sd, set<int> &sds, fd_set *fdSets);
  void closeConnection(set<int> &toClose, set<int> &sds, fd_set *fdSets);

  void checkClient(fd_set *fdSets, int *intVal, set<int> &sds);
  bool recvMessage(Client &clt, set<int> &toClose);
  static ssize_t recvBuffer(Client &clt);
  static bool recvHeader(Client &clt);

  bool isSend(int sd, fd_set &fd, Client &clt, setInt &);
  bool isRecv(int sd, fd_set &fd, Client &clt, setInt &);
  bool sendMessage(Client &clt, set<int> &toClose);
  ssize_t sendBuffer(Client &clt);

  void checkCgi(fd_set *fdSets, int *intVal, set<int> &sds);
};

#endif // WEBSERV_SELECT_HPP
