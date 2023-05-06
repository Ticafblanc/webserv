/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_SERVER_HPP
# define WEBSERV_SERVER_HPP

#include "data_server.class.hpp"
#include "header.hpp"
#include <poll.h>

#define MAX_EVENTS 100

class server{

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/

private:// see if to switch const

    enum { nbr_clients, server_socket, epoll_fd};

    data_server data;
    std::vector<int> i_arg;
    std::vector<std::string> s_arg;
    struct epoll_event event, events[MAX_EVENTS];



/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:

/**
 * Constructor of sever class
 *
 * sever();
 *
 * @param void
 * @throw none
 **/
    server();

/**
 * Constructor of sever class
 *
 * sever(data_server &);
 *
 * @param data_server instance to build the server
 * @throw none
 **/
    server(data_server &);

/**
 * Destructor of sever class
 *
 * ~sever();
 *
 * @throw none
 **/
    ~server();

/**
 * Copy constructor of sever class
 *
 * sever(server &);
 *
 * @param server instance to build the server
 * @throw none
 **/
    server(const server&);

/**
 * Operator overload= of sever class
 *
 * operator=(const server&);
 *
 * @param server instance const to copy the server
 * @throw none
 **/
    server& operator=(const server& rhs);


/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

public:

    class socket_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class socketopt_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class bind_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class listen_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class accept_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class launch_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class epoll_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

public:

/**
 * Accessor of sever class
 *
 * data_server getDataServer() const;
 *
 * @return data_server instance
 * @param void
 * @throw none
 **/
    data_server getDataServer() const;

/**
 * Accessor of sever class
 *
 * void setDataServer(data_server& d);
 *
 * @return void
 * @param data_server instance to set the data server
 * @throw none
 **/
    void setDataServer(data_server&);

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

public:

/**
 * https://man7.org/linux/man-pages/man2/accept.2.html
 *
 */
    void launcher();

/*
*====================================================================================
*|                                      signal                                      |
*====================================================================================
*/

private:

    void handle(int sig);

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

private:

/**
 * Methode of server class
 *
 * int set_socket();
 *
 * @return file descriptor (int) server socket created
 * @param void
 * @throw server::socket_exception
 *
 * create a new socket with fonction socket
 * int socket(int domain, int type, int protocol);
 * if process fail throw server::socket_exception();
 * https://man7.org/linux/man-pages/man2/socket.2.html
 * tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = socket(AF_INET, SOCK_RAW, protocol);
 **/
    int set_socket();

/**
 * https://linux.die.net/man/3/setsockopt
 * */
    void set_sockoption();

/**
 * https://man7.org/linux/man-pages/man2/bind.2.html
 * */
    void set_bind();

/**
 * https://man7.org/linux/man-pages/man2/listen.2.html
 * */
    void set_listen();

/**
 * Command  (cmd) for accessor server :
 * F_SETFD      Set the file descriptor flags to arg.
 * F_GETFL      Get descriptor status flags, as described below (arg is ignored).
 *
 * Flag for accessor server :
 * O_NONBLOCK   Non-blocking I/O; if no data is available to a read(2)
 *              call, or if a write(2) operation would block, the read
 *              or write call returns -1 with the error EAGAIN
 * O_APPEND     Force each write to append at the end of file;
 *              corresponds to the O_APPEND flag of open(2).
 * O_ASYNC      Enable the SIGIO signal to be sent to the process
 *              group when I/O is possible, e.g., upon availability of
 *              data to be read.
 * set fnctl like subject fcntl(fd, F_SETFL, O_NONBLOCK)
 * */
    void accessor_server(int cmd, int flag);

/**
 * create an instance of epoll
 * */
    void create_epoll();

/**
 * set fds for news client for server socket
 * */
    void set_epoll_socket();

/**
 * registe socket to follow
 * EPOLL_CTL_ADD, EPOLL_CTL_MOD or EPOLL_CTL_DEL
 * */
    void set_epoll_ctl(int);

/**
 * wait un event in request connect or sockert already open or throw exeptiom
 * */
    void set_epoll_wait();
};


#endif //WEBSERV_SERVER_HPP