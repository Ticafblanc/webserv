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

  static void endServer(int signal);

  void checkServer(fd_set *fdSets, int *intVal);
  static void acceptConnection(const int &sd, int *intVal, fd_set *fdSets);


  void checkClient(fd_set *fdSets, int *intVal);
  int recvMessage(Client & clt);
  int sendMessage(Client &clt);

  /**
   *  @brief Close the connection with the socket
   *  descriptor (not listener). Remove the socket of
   *  the set to treat.
   *
   *  @param sd the socket descriptor.
   *  @param max_sd the number of socket.
   *  @param master_set the master set containing all the final
   *      the socket descriptor.
   *  @return the new number of socket descriptor.
   */
  int closeConnection(int sd, int max_sd, fd_set *read_set, fd_set *write_set);

  /**
   *  @brief Give the server name where the client want
   *  to access.
   *  @todo add throw if host not found.
   *
   *  @param hb the headers block containing the host parameter.
   *  @return the server name.
   */
  std::string getServerName(const Headers &hb);

  int getChunk(int sd, vecStr &request);
};

#endif // WEBSERV_SELECT_HPP
