//
// Created by Matthis DoQuocBao on 2024-02-22.
//

#ifndef WEBSERV_SOCKET_HPP
#define WEBSERV_SOCKET_HPP

#include "configuration.hpp"
#include "utils.hpp"

#define MAX_CONNECTION 9999

#define MSG_NOSIGNAL_ 0

class Socket {
protected:
  int _sd;

private:
  int _option_buffer;
  struct sockaddr_in _address;
  struct Server _server_config;

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
  Socket(const struct Server &server);
  Socket(int sd, const struct Server &server);
  Socket(int sd);
  Socket(const Socket &copy);
  virtual ~Socket();
  Socket &operator=(const Socket &op);

  int getSocketDescriptor();
  struct Server getServerConfiguration();
  void setToDefault();
};

#endif // WEBSERV_SOCKET_HPP
