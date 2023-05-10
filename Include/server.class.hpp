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

#include <Include/data_server.class.hpp>
#include <Include/header.hpp>


class server{

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/

private:

    data_server _data;
    int*        _server_socket;
    int         _number_of_socket;
    int         _client_socket;
    int         _epoll_instance;
    int         _number_triggered_events;
    static bool _stat_of_server;
    struct epoll_event _event, *_events;
    struct sockaddr_storage _client_address;


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
 * @param   void
 * @throw   none
 **/
    server();

/**
 * Constructor of sever class
 *
 * sever(data_server &);
 *
 * @param   data_server instance to build the server
 * @throw   none
 **/
    server(const data_server &);

/**
 * Destructor of sever class
 *
 * ~sever();
 *
 * @throw   none
 **/
    ~server();

/**
 * Copy constructor of sever class
 *
 * sever(server &);
 *
 * @param   server instance to build the server
 * @throw   none
 **/
    server(const server &);

/**
 * Operator overload= of sever class
 *
 * operator=(const server&);
 *
 * @param   server instance const to copy the server
 * @throw   none
 **/
    server& operator=(const server &);


/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/

private:

/**
 * Class exception of sever class
 *
 * class server_exception;
 *
 * @inherit std::exception
 **/
    class server_exception: public std::exception
    {
    public:

        /**
         * Constructor of server_exception class
         *
         * server_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        server_exception(const char *);

        /**
         * Constructor of server_exception class
         *
         * server_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        server_exception(const int server_socket, const char *);

        /**
         * Copy constructor of server_exception class
         *
         * server_exception(server_exception &);
         *
         * @param   server_exception instance to build the server_exception
         *          server_socket in an int to close
         * @throw   none
         **/
        server_exception(const server_exception &);

        /**
         * Operator overload= of server_exception class
         *
         * operator=(const server_exception&);
         *
         * @param   server_exception instance const to copy the server_exception
         * @throw   none
         **/
        server_exception& operator=(const server_exception &);

        /**
        * Destructor of server_exception class
        *
        * virtual ~server_exception() throw();
        *
        * @throw   none
        **/
        virtual ~server_exception() throw();

        /**
         * Public methode of server_exception
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "socket error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string   _message;
        int           _server_socket;
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
 * @returns data_server instance
 * @param void
 * @throw none
 **/
    data_server getDataServer() const;

/**
 * Accessor of sever class
 *
 * void setDataServer(data_server& d);
 *
 * @returns void
 * @param data_server instance to set the data server
 * @throw none
 **/
    void setDataServer(data_server&);

/*
*====================================================================================
*|                                  public methode                                  |
*====================================================================================
*/

public:

/**
 * Public methode of sever class
 *
 * void launcher();
 *
 * @returns void
 * @param void
 * @throw none
 *
 * @see https://man7.org/linux/man-pages/man2/accept.2.html
 *
 */
    void launcher();

/*
*====================================================================================
*|                                      signal                                      |
*====================================================================================
*/

private:
/**
 * Private methode of sever class
 *
 * void handle(int sig);
 *
 * @returns void
 * @param int signal catch by foction call
 * @throw none
 */
    static void handle(int);

/*
*====================================================================================
*|                                  private methode utils                           |
*====================================================================================
*/

private:

/**
 * Private methode of server class
 *
 * create a new socket with fonction socket
 *
 * @see https://man7.org/linux/man-pages/man2/socket.2.html
 *
 * int socket(int domain, int protocol);
 *
 * tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = socket(AF_INET, SOCK_RAW, protocol);
 *
 * nginx work only on tcp protocol !!
 *
 * void set_socket(int domain);
 *
 * @returns file descriptor (int) server socket created
 * @param   domaine is an int define the family of address AF_INET for IPv4 and AF_INET6 for IPv6
 * @throws  server::server_exception
 **/
    void set_socket(int);

/**
 * Private methode of server class
 *
 * set the option of server socket already created
 *
 * void set_sockoption();
 *
 * @returns void
 * @param   void
 * @throws  server::server_exception
 *
 * @see https://linux.die.net/man/3/setsockopt
 *
 * @todo    add specific message
 * */
    void set_socket_option();

/**
 * Private methode of server class
 *
 * associate an IP address and a port number with a socket already created
 *
 * void set_bind(int server_socket);
 *
 * @returns void
 * @param   server_socket is an int file descriptor already created
 * @throws  server::server_exception
 *
 * @see https://man7.org/linux/man-pages/man2/bind.2.html
 *
 * @todo    add specific message
 * */
    void set_bind();

/**
 * Private methode of server class
 *
 * set the listen option so the number of possible connexion
 *
 * void set_listen(int server_socket, int backlog);
 *
 * @returns void
 * @param   backlog is an int to define the maximum number of pending connections
 *          that can be queued before the server starts refusing new incoming connections.
 * @throws  server::listen_exception
 *
 * @see https://man7.org/linux/man-pages/man2/listen.2.html
 *
 * @Todo    watch if necessery to define the option in data server
 * @todo    add specific message
 * */
    void set_listen(int);

/**
 * Private methode of server class
 *
 * accessor of socket to get or set the flag option
 * set fnctl like subject fcntl(fd, F_SETFL, O_NONBLOCK)
 * don't show the actual flag in socket and force to change it to non blocking
 *
 * void accessor_server(int cmd, int flag);
 *
 * @returns void
 * @param   Command  (cmd) for accessor server :
 *          F_SETFD      Set the file descriptor flags to arg.
 *          F_GETFL      Get descriptor status flags, as described below (arg is ignored).
 *
 *          Flag for accessor server :
 *          O_NONBLOCK   Non-blocking I/O; if no data is available to a read(2)
 *          call, or if a write(2) operation would block, the read
 *          or write call returns -1 with the error EAGAIN
 *          O_APPEND     Force each write to append at the end of file;
 *          corresponds to the O_APPEND flag of open(2).
 *          O_ASYNC      Enable the SIGIO signal to be sent to the process
 *          group when I/O is possible, e.g., upon availability of
 *          data to be read.
 *
 * @throws  none but to do
 *
 * @todo add an exception to mange crash of fcntl fonction dont build for now wait at the and to buil juste one exception for lanch methode
 * */
    int accessor_socket_flag(int server_socket, int, int);

/**
 * Private methode of server class
 *
 * create an instance of epoll
 *
 * int create_epoll();
 *
 * @returns an file descriptor (int) for the new instance
 * @param   void
 * @throws  server::epoll_exception
 * */
    int create_epoll();

/**
 * Private methode of server class
 *
 * set file descriptor (socket) in epoll event instance and define events
 *
 * void set_epoll_socket(int socket, int event);
 *
 * @returns event fixed
 * @param   socket to set in _event epoll instance
 *
 *          events is int to set events of socket
 *          EPOLLIN the event occurs when data can be read from the file descriptor
 *          EPOLLOUT the event occurs when data can be written to the file descriptor
 *          EPOLLERR the event occurs when there is an error on the file descriptor
 *          EPOLLRDHUP the event occurs when the connection is closed by the remote peer
 *          EPOLLHUP the event occurs when the file descriptor is closed by the local peer
 *          EPOLLET edge triggering mode
 *          EPOLLONESHOT single trigger mode
 *
 * @throws  none
 * */
    void set_epoll_socket(int, int);

/**
 * Private methode of server class
 *
 * set _event instance with socket to add remove or modify
 *
 * void set_epoll_ctl(int option, int socket);
 *
 * @returns void
 * @param   option is an int action to do:
 *          EPOLL_CTL_ADD to add a new descriptor to be monitored
 *          EPOLL_CTL_MOD to modify the monitoring of an already monitored descriptor
 *          EPOLL_CTL_DEL to delete a monitored descriptor.
 *
 *          socket to set in _event epoll instance
 * @throws  server::epoll_exception
 * */
    void set_epoll_ctl(int, int, struct epoll_event *);

/**
 * Private methode of server class
 *
 * wait un event in request connect or new event in socket already open
 *
 * void set_epoll_wait();
 *
 * @returns void
 * @param   void
 * @throws  server::epoll_exception
 * */
    void set_epoll_wait();

/**
 * Private methode of server class
 *
 * accept new request connection, create client socket,
 * set it and add to epoll event to monitoring
 *
 * void accept_connection();
 *
 * @returns void
 * @param   void
 * @throws  server::epoll_exception
 * */
    void accept_connection();

/**
 * Private methode of server class
 *
 * manage event like receive data
 *
 * void manage_event(int socket);
 *
 * @returns void
 * @param   socket is an int to manage the recev and send answer
 * @throws  server::epoll_exception
 * */
    void manage_event(int);
};


#endif //WEBSERV_SERVER_HPP