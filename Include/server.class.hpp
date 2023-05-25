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

#ifndef WEBSERV_SERVER_CLASS_HPP
# define WEBSERV_SERVER_CLASS_HPP

#include "../Include/config_webserv.class.hpp"
#include "../Include/header.hpp"


class server{

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/


    config_webserv              &_config;
    bool                        _stat_of_server;
    int                         _epoll_instance;
    int                         _number_max_events;
    int                         _number_triggered_events;
    struct epoll_event          _webserv_event, *_server_events;
    std::map<int, bloc_server>  _map_client_socket;

    struct epoll_event          *_client_event;
    sockaddr_in                 _client_address;
    socklen_t                   _client_address_len;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

/**
 * Private methode of server class
 *
 * create an instance of epoll in _epoll_instance and
 * return a file descriptor to new instance of epoll
 *
 * void create_epoll();
 *
 * @returns void
 * @param   void
 * @throws  server::server_exception
 * */
    void create_epoll();

/**
 * Private methode of server class
 *
 * set epoll to follow one or multi ip and port
 *
 * void set_epoll();
 *
 * @returns void
 * @param   void
 * @throws  server::server_exception
 **/
    void set_epoll();

/**
 * Private methode of server class
 *
 * set epoll_event instance with socket and type of event to follow
 * before to add a epoll_event to epoll
 *
 * void set_epoll_socket(int & server_socket, struct epoll_event & event, int events);
 *
 * @returns event fixed
 * @param   server_socket is an int & who refer to
 *          config_webserv->config_server.class->config_address.class->server_socket to add to the instance
 *
 *          event is a struct epoll_event & who refer to
 *          config_webserv->config_server.class->config_address.class->_event to set
 *
 *          events is int to add to the event
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
    void set_epoll_event(int&, struct epoll_event &, int);

/**
 * Private methode of server class
 *
 * set _event instance with socket to add remove or modify
 *
 * void set_epoll_ctl(int option, int server_socket);
 *
 * @returns void
 * @param   event is a struct epoll_event * who point to
 *          config_webserv->config_server.class->config_address.class->_event to set
 *
 *          option is an int action to do:
 *          EPOLL_CTL_ADD to add a new descriptor to be monitored
 *          EPOLL_CTL_MOD to modify the monitoring of an already monitored descriptor
 *          EPOLL_CTL_DEL to delete a monitored descriptor.
 * @throws  server::server_exception
 * */
    void set_epoll_ctl(int, int);

/**
 * Private methode of server class
 *
 * wait un event in request connect or new event in socket already open
 *
 * void set_epoll_wait();
 *
 * @returns void
 * @param   void
 * @throws  server::server_exception
 * */
    void set_epoll_wait();

/**
 * Private methode of server class
 *
 * check if is a request try to connect with a server socket
 *
 * bool is_server_socket_already_conected(int position);
 *
 * @returns bool true if is a sever socket than false
 * @param    position is index in server_event tab
 * @throws  server::server_exception
 * */
    bool is_server_socket_already_conected(int);

/**
 * Private methode of server class
 *
 * accept new request connection, create client socket,
 * set it and add to epoll event to monitoring
 *
 * void accept_connection(int new_client_socket);
 *
 * @returns void
 * @param   void
 * @throws  server::server_exception
 * */
    void accept_connection(int, bloc_server & server);

/**
 * Private methode of server class
 *
 * manage event like receive data
 *
 * void manage_event_already_conected(int position);
 *
 * @returns void
 * @param   void
 * @throws  server::server_exception
 * */
    void manage_event_already_conected(int);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string recv_data_client(int client_socket);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string recv_data_client(int);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void send_data_client(int client_socket, std::string& content);
 *
 * @returns void
 * @param   client_socket to send message
 * @param   content & to message to send
 * @throws  server::server_exception
 * */
    void send_data_client(int, std::string);

/**
 * Private methode of server class
 *
 * add headers befor send
 *
 * std::string set_html_content(std::string headers, std::string path_html_file);
 *
 * @returns std::string ready to send
 * @param   path_html_file to content to send
 * @throws  server::server_exception
 * */
     std::string set_content(std::string (*f)(size_t), std::string path_html_file);

/**
 * Private methode of server class
 *
 * set headers befor send
 *
 * std::string set_headers(size_t Content-Length);
 *
 * @returns std::string ready to send
 * @param   Content-Length to add to headers
 * @throws  server::server_exception
 * */
    std::string set_headers_html(size_t);

/**
 * Private methode of server class
 *
 * set headers befor send
 *
 * std::string set_headers(size_t Content-Length);
 *
 * @returns std::string ready to send
 * @param   Content-Length to add to headers
 * @throws  server::server_exception
 * */
    std::string set_headers_css(size_t);

























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
 * void set_socket(int & server_socket);
 *
 * @returns file descriptor (int) server socket created
 * @param   server_socket is an int & who refer set new socket
 * @throws  server::server_exception
 **/
    void set_socket(int &);

/**
 * Private methode of server class
 *
 * set the option of server socket already created
 *
 * void set_socket_option(int & server_socket);
 *
 * @returns void
 * @param   server_socket is an int & who refer to
 *          config_webserv->config_server.class->config_address.class->server_socket to set option
 * @throws  server::server_exception
 *
 * @see https://linux.die.net/man/3/setsockopt
 * */
    void set_socket_option(int & server_socket);

/**
 * Private methode of server class
 *
 * associate an IP address and a port number with a socket already created
 *
 * void set_bind(int & server_socket, struct sockaddr * sock_address);
 *
 * @returns void
 * @param   server_socket is an int & who refer to
 * @param   sock_address is an sockaddr_in contain data to set socket
 * @throws  server::server_exception
 *
 * @see https://man7.org/linux/man-pages/man2/bind.2.html
 * */
    void set_bind(int & server_socket, sockaddr_in sock_address);

/**
 * Private methode of server class
 *
 * set the listen option so the number of possible connexion
 *
 * void set_listen(int & server_socket, int backlog);
 *
 * @returns void
 * @param   server_socket is an int & who refer to
 *          config_webserv->config_server.class->config_address.class->server_socket to bind()
 *
 *          backlog is an int to define the maximum number of pending connections
 *          that can be queued before the server starts refusing new incoming connections.
 * @throws  server::server_exception
 *
 * @see https://man7.org/linux/man-pages/man2/listen.2.html
 * */
    void set_listen(int&, int);

/**
 * Private methode of server class
 *
 * accessor of socket to get or set the flag option
 * set fnctl like subject fcntl(fd, F_SETFL, O_NONBLOCK)
 * don't show the actual flag in socket and force to change it to non blocking
 *
 * void accessor_server(int& server_socket, int command, int flag);
 *
 * @returns return the flag set in server_socket
 * @param   server_socket is an int & who refer to
 *          config_webserv->config_server.class->config_address.class->server_socket to set or get flag option
 *
 *          Command  (cmd) for accessor server :
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
 * @throws  server::server_exception
 * */
    int accessor_socket_flag(int&, int, int);


/*check if file descriptor is open
 * if process fail throw server::socket_exception();
 */
//    int fd_isopen();

/*check if socket  is open
 * if process fail throw server::socket_exception();
 */
//    int socket_isopen();



/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                      Fonction                                    |
*====================================================================================
*/

/**
 * Constructor of sever class
 *
 * sever(data_server *);
 *
 * @param   config_webserv instance to build the server
 * @throw   none
 **/
    server(config_webserv &);

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
         * server_exception(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        server_exception(const char * message);

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
        std::string     _message;
    };

/*
*====================================================================================
*|                                        Accessor                                  |
*====================================================================================
*/

/**
 * Accessor of sever class
 *
 * data_server getDataServer() const;
 *
 * @returns data_server instance
 * @param void
 * @throw none
 **/
    config_webserv get_config_webserv() const;

/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/


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
 * @todo overload fonction to run launcher and launcher(flag);
 */
    void launcher();

};


#endif //WEBSERV_SERVER_CLASS_HPP