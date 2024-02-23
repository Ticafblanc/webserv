//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_SERVER_HPP
#define WEBSERV_SERVER_HPP

#include "socketManager.hpp"
#include "headers.hpp"
#include "utils.hpp"

class Server {
private:
  SocketManager<Socket *> _sm;
  SocketManager<Client *> _sub_sm;

  int waitConnection(fd_set *read_set, fd_set *write_set, int max_sd);

  /**
 *  @brief Accept all connections in the queue of the
 *  socket descriptor, add them to the total of connected
 *  sockets descriptors (not to listener).
 *
 *  @param sd the socket descriptor where accept.
 *  @param max_sd the total of socket descriptor.
 *  @param master_set the set of all sockets descriptors
 *      (listener + opened socket with clients).
 *  @return new number of maximum sockets descriptor.
   */
  int acceptConnection(int sd, int max_sd, fd_set *read_set, fd_set *write_set,
                       SocketManager<Client *> &sub_sm);

  /**
 *  @brief Set the message get from the socket into
 *  the buffer.
 *
 *  @return -1 if and error appear, 0 otherwise.
   */
  int receiveConnection(int sd, std::string &request);

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

  /**
 *  @brief Check to be sure that a default
 *  server was selected.
   */
  void verifyDefaultServer();
  int getChunk(int sd, vecStr &request);

public:
  Server();
  Server(SocketManager<Socket *> sm);
  Server(const Server &copy);
  ~Server();
  Server &operator=(const Server &op);

  void loop();
  void closeServer();
};

#endif // WEBSERV_SERVER_HPP
