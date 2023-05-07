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

private:

    data_server data;// see if to switch const

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
 * class socket_exception;
 *
 * @inherit std::exception
 **/
    class socket_exception: public std::exception
    {
    public:

        /**
         * Constructor of socket_exception class
         *
         * socket_exception();
         *
         * @param   void
         * @throw   none
         *
         * @todo merge if its possible at the end socket_exception,socketopt_exception and bind_exception
         * @todo wach if we build method to close file desciptor or close with destructor
         * @todo i think we can use the erno variable to throw a specific message we dont have "Checking the value of errno is strictly forbidden after a read or a write operation."
         **/
        socket_exception();

        /**
         * Constructor of socket_exception class
         *
         * socket_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        socket_exception(const char *);

        /**
         * Copy constructor of socket_exception class
         *
         * socket_exception(socket_exception &);
         *
         * @param   socket_exception instance to build the socket_exception
         * @throw   none
         **/
        socket_exception(const socket_exception &);

        /**
         * Operator overload= of socket_exception class
         *
         * operator=(const socket_exception&);
         *
         * @param   socket_exception instance const to copy the socket_exception
         * @throw   none
         **/
        socket_exception& operator=(const socket_exception &);

        /**
        * Destructor of socket_exception class
        *
        * virtual ~socket_exception() throw();
        *
        * @throw   none
        **/
        virtual ~socket_exception() throw();

        /**
         * Public methode of socket_exception
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
        std::string _message;
    };

/**
* Class exception of sever class
*
* class socketopt_exception;
*
* @inherit std::exception
**/
    class socketopt_exception: public std::exception
    {
    public:

        /**
         * Constructor of socketopt_exception class
         *
         * socketopt_exception();
         *
         * @param   void
         * @throw   none
         *
         **/
        socketopt_exception(const int);

        /**
         * Constructor of socketopt_exception class
         *
         * socketopt_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        socketopt_exception(const int, const char *);

        /**
        * Copy constructor of socketopt_exception class
        *
        * socketopt_exception(const socketopt_exception &);
        *
        * @param   socketopt_exception instance to build the socketopt_exception
        * @throw   none
        **/
        socketopt_exception(const socketopt_exception &);

        /**
         * Operator overload= of socketopt_exception class
         *
         * operator=(const socketopt_exception&);
         *
         * @param   socketopt_exception instance const to copy the socketopt_exception
         * @throw   none
         **/
        socketopt_exception& operator=(const socketopt_exception &);

        /**
         * Destructor of socketopt_exception class
         *
         * virtual ~socketopt_exception() throw();
         *
         * @throw   none
         *
         * @todo wach if we build method to close file desciptor or close with destructor
         **/
        virtual ~socketopt_exception() throw();

        /**
         * Public methode of socketopt_exception
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "socketopt error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string _message;
        int _server_socket;
    };

/**
* Class exception of sever class
*
* class bind_exception;
*
* @inherit std::exception
**/
    class bind_exception: public std::exception
    {
    public:

        /**
         * Constructor of bind_exception class
         *
         * bind_exception();
         *
         * @param   void
         * @throw   none
         **/
        bind_exception(const int);

        /**
         * Constructor of bind_exception class
         *
         * bind_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        bind_exception(const int, const char *);

        /**
        * Copy constructor of bind_exception class
        *
        * bind_exception(const bind_exception &);
        *
        * @param   bind_exception instance to build the bind_exception
        * @throw   none
        **/
        bind_exception(const bind_exception &);

        /**
         * Operator overload= of bind_exception class
         *
         * operator=(const bind_exception&);
         *
         * @param   bind_exception instance const to copy the bind_exception
         * @throw   none
         **/
        bind_exception& operator=(const bind_exception &);

        /**
         * Destructor of bind_exception class
         *
         * virtual ~bind_exception() throw();
         *
         * @throw   none
         * @todo wach if we build method to close file desciptor or close with destructor
         *
         **/
        virtual ~bind_exception() throw();

        /**
         * Public methode of bind_exception
         *
         * virtual const char * what() const throw();
         *
         * @return  const char * store in private std::string _message
         *          at the construction defaut constructor "bind error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string _message;
        int         _server_socket;
    };

/**
* Class exception of sever class
*
* class listen_exception;
*
* @inherit std::exception
**/
    class listen_exception: public std::exception
    {
    public:

        /**
         * Constructor of listen_exception class
         *
         * listen_exception();
         *
         * @param   void
         * @throw   none
         **/
        listen_exception(const int);

        /**
         * Constructor of listen_exception class
         *
         * listen_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        listen_exception(const int, const char *);

        /**
         * Copy constructor of listen_exception class
         *
         * listen_exception(listen_exception &);
         *
         * @param   listen_exception instance to build the listen_exception
         * @throw   none
         **/
        listen_exception(const listen_exception &);

        /**
         * Operator overload= of listen_exception class
         *
         * operator=(const listen_exception&);
         *
         * @param   listen_exception instance const to copy the listen_exception
         * @throw   none
         **/
        listen_exception& operator=(const listen_exception &);

        /**
         * Destructor of listen_exception class
         *
         * virtual ~listen_exception() throw();
         *
         * @throw   none
         *
         * @todo wach if we build method to close file desciptor or close with destructor
         *
         **/
        virtual ~listen_exception() throw();

        /**
         * Public methode of launch_exception
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "listen error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string _message;
        int _server_socket;
    };

/**
* Class exception of sever class
*
* class accept_exception;
*
* @inherit std::exception
**/
    class accept_exception: public std::exception
    {
    public:

        /**
         * Constructor of accept_exception class
         *
         * accept_exception();
         *
         * @param   void
         * @throw   none
         **/
        accept_exception();

        /**
         * Constructor of accept_exception class
         *
         * accept_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        accept_exception(const char *);

        /**
         * Copy constructor of accept_exception class
         *
         * accept_exception(accept_exception &);
         *
         * @param   accept_exception instance to build the accept_exception
         * @throw   none
         **/
        accept_exception(const accept_exception &);

        /**
         * Operator overload= of accept_exception class
         *
         * operator=(const accept_exception&);
         *
         * @param   accept_exception instance const to copy the accept_exception
         * @throw   none
         **/
        accept_exception& operator=(const accept_exception &);

        /**
         * Destructor of accept_exception class
         *
         * virtual ~accept_exception() throw();
         *
         * @throw   none
         **/
        virtual ~accept_exception() throw();

        /**
         * Public methode of launch_exception
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "accept error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string _message;
    };

/**
* Class exception of sever class
*
* class epoll_exception;
*
* @inherit std::exception
**/
    class epoll_exception: public std::exception
    {
    public:

        /**
         * Constructor of epoll_exception class
         *
         * epoll_exception();
         *
         * @param   void
         * @throw   none
         **/
        epoll_exception();

        /**
         * Constructor of epoll_exception class
         *
         * epoll_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        epoll_exception(const char *);

        /**
         * Copy constructor of epoll_exception class
         *
         * epoll_exception(epoll_exception &);
         *
         * @param   epoll_exception instance to build the epoll_exception
         * @throw   none
         **/
        epoll_exception(const epoll_exception &);

        /**
         * Operator overload= of epoll_exception class
         *
         * operator=(const epoll_exception&);
         *
         * @param   epoll_exception instance const to copy the epoll_exception
         * @throw   none
         **/
        epoll_exception& operator=(const epoll_exception &);

        /**
         * Destructor of epoll_exception class
         *
         * virtual ~epoll_exception() throw();
         *
         * @throw   none
         **/
        virtual ~epoll_exception() throw();

        /**
         * Public methode of launch_exception
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "epoll error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string _message;
    };

/**
* Class exception of sever class
*
* class launch_exception;
*
* @inherit std::exception
**/
    class launch_exception: public std::exception
    {
    public:

        /**
         * Constructor of launch_exception class
         *
         * launch_exception();
         *
         * @param   void
         * @throw   none
         **/
        launch_exception();

        /**
         * Constructor of launch_exception class
         *
         * launch_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        launch_exception(const char *);

        /**
         * Copy constructor of launch_exception class
         *
         * launch_exception(launch_exception &);
         *
         * @param   launch_exception instance to build the launch_exception
         * @throw   none
         **/
        launch_exception(const launch_exception &);

        /**
         * Operator overload= of launch_exception class
         *
         * operator=(const launch_exception&);
         *
         * @param   launch_exception instance const to copy the launch_exception
         * @throw   none
         **/
        launch_exception& operator=(const launch_exception &);

        /**
         * Destructor of launch_exception class
         *
         * virtual ~launch_exception() throw();
         *
         * @throw   none
         **/
        virtual ~launch_exception() throw();

        /**
         * Public methode of launch_exception
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "launch error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string _message;
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
    void handle(int);

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
 * int socket(int domain, int type, int protocol);
 *
 * tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = socket(AF_INET, SOCK_RAW, protocol);
 *
 * int set_socket(int domain, int type, int protocol);
 *
 * @returns file descriptor (int) server socket created
 * @param   domaine is an int define the family of address AF_INET for IPv4 and AF_INET6 for IPv6
 *
 *          type is an int define the transmission mode SOCK_STREAM for tcp
 *          SOCK_DGRAM for udp SOCK_RAW for row
 *
 *          protocol in an int define the protocol to use fonction the domaine and type of domaine
 *          for AF_INET (IPv4) :
 *          IPPROTO_TCP for TCP
 *          IPPROTO_UDP for UDP
 *          IPPROTO_ICMP for ICMP
 *          0 for let de systeme define the option by it self
 *          for AF_INET6 (IPv6) :
 *          IPPROTO_TCP for TCP
 *          IPPROTO_UDP for UDP
 *          IPPROTO_ICMPV6 for ICMPv6
 *          0 for let de systeme define the option by it self
 *          for AF_UNIX (locale host) :
 *          0 for default.
 * @throws  server::socket_exception
 *
 * @Todo    watch if necessery to define the option in data server
 * @todo    add specific message
 **/
    static int set_socket(int, int, int);

/**
 * Private methode of server class
 *
 * set the option of server socket already created
 *
 * void set_sockoption(int server_socket, int level, int option_name, int option_val);
 *
 * @returns void
 * @param   server_socket is an int file descriptor already created
 *
 *          level is an int to define the level option :
 *          SOL_SOCKET : pour les options générales du socket.
 *          IPPROTO_IP : pour les options du protocole IP (Internet Protocol).
 *          IPPROTO_TCP : pour les options du protocole TCP (Transmission Control Protocol).
 *          IPPROTO_UDP : pour les options du protocole UDP (User Datagram Protocol).
 *
 *          option_name is an int to define de option name by macro for SOL_SOCKET
 *          you can define SO_REUSEADDR to use the ip addresse juste after you close de socket
 *
 *          option_val to define de value of option_name for exemple for SO_REUSEADDR you can define
 *          0 to desable option or 1 to enble option
 *
 * @throws  server::socketopt_exception
 *
 * @see https://linux.die.net/man/3/setsockopt
 *
 * @Todo    watch if necessery to define the option in data server
 * @todo    add specific message
 * */
    static void set_sockoption(int, int , int , int);

/**
 * Private methode of server class
 *
 * associate an IP address and a port number with a socket already created
 *
 * void set_bind(int server_socket);
 *
 * @returns void
 * @param   server_socket is an int file descriptor already created
 * @throws  server::bind_exception
 *
 * @see https://man7.org/linux/man-pages/man2/bind.2.html
 *
 * @todo    add specific message
 * */
    void set_bind(int);

/**
 * Private methode of server class
 *
 * set the listen option so the number of possible connexion
 *
 * void set_listen(int server_socket, int backlog);
 *
 * @returns void
 * @param   server_socket is an int file descriptor already created
 *
 *          backlog is an int to define the maximum number of pending connections
 *          that can be queued before the server starts refusing new incoming connections.
 * @throws  server::listen_exception
 *
 * @see https://man7.org/linux/man-pages/man2/listen.2.html
 *
 * @Todo    watch if necessery to define the option in data server
 * @todo    add specific message
 * */
    void set_listen(int, int);

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
    static int create_epoll();

/**
 * Private methode of server class
 *
 * set fd for news client for server socket
 *
 * int create_epoll();
 *
 * @returns an file descriptor (int) for the new instance
 * @param   void
 * @throws  server::epoll_exception
 * */
    struct epoll_event set_epoll_socket();

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