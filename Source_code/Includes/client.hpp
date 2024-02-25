//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CLIENT_HPP
#define WEBSERV_CLIENT_HPP

#include "socket.hpp"

class Client : public Socket{
private:
  string _client_ip;
  bool _information_received;
  string _request;

public:
  Client(Socket &server, const string& client_ip, int sd);
  Client(Client &copy);
  virtual ~Client();
  Client &operator=(const Client &rhs);

  Socket *getParent();
  string &getRequest();
  string getClientIp();
  bool informationReceived();
  void setReceived(bool val);
};

#endif // WEBSERV_CLIENT_HPP
