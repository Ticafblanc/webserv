//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_CLIENT_HPP
#define WEBSERV_CLIENT_HPP

#include "socket.hpp"

class Client : public Socket{
private:
  Socket *_parent_socket;
  string _client_ip;
  bool _information_received;
  string _request;

public:
  Client(Socket *parent, string client_ip, int sd);
  Client(const Client &copy);
  virtual ~Client();
  Client &operator=(const Socket &op);

  Socket *getParent();
  string &getRequest();
  string getClientIp();
  bool informationReceived();
  void setReceived(bool val);
};

#endif // WEBSERV_CLIENT_HPP
