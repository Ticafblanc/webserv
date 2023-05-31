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

#include "../Include/header.hpp"
#include "../Include/config_webserv.class.hpp"
#include "../Include/http_request.class.hpp"
#include "../Include/client.class.hpp"


class server{

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/


    config_webserv                                  &_config;
    http_request                                    _request;
    int                                             _epollInstance;
    int                                             _numberTriggeredEvents;
    struct epoll_event                              _webservEvent, *_serverEvents;

    std::map<std::string, int (server::*)(int)>     _mapConnection;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

/**
 * Private methode of server class
 *
 * create an instance of epoll in _epollInstance and
 * return a file descriptor to new instance of epoll
 *
 * void createEpoll();
 *
 * @returns void
 * @param   void
 * @throws  server::serverException
 * */
    void createEpoll();

/**
 * Private methode of server class
 *
 * set epoll to follow one or multi ip and port
 *
 * void setEpoll();
 *
 * @returns void
 * @param   void
 * @throws  server::serverException
 **/
    void setEpoll();

/**
 * Private methode of server class
 *
 * set epollEvent instance with socket and type of event to follow
 * before to add a epollEvent to epoll
 *
 * void setEpoll_socket(int & server_socket, struct epollEvent & event, int events);
 *
 * @returns event fixed
 * @param   server_socket is an int & who refer to
 *          config_webserv->config_server.class->config_address.class->server_socket to add to the instance
 *
 *          event is a struct epollEvent & who refer to
 *          config_webserv->config_server.class->config_address.class->Event to set
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
    void setEpollEvent(int&, struct epollEvent &, int);

/**
 * Private methode of server class
 *
 * set Event instance with socket to add remove or modify
 *
 * void setEpoll_ctl(int option, int server_socket);
 *
 * @returns void
 * @param   event is a struct epollEvent * who point to
 *          config_webserv->config_server.class->config_address.class->Event to set
 *
 *          option is an int action to do:
 *          EPOLL_CTL_ADD to add a new descriptor to be monitored
 *          EPOLL_CTL_MOD to modify the monitoring of an already monitored descriptor
 *          EPOLL_CTL_DEL to delete a monitored descriptor.
 * @throws  server::serverException
 * */
    void setEpoll_ctl(int, int);

/**
 * Private methode of server class
 *
 * wait un event in request connect or new event in socket already open
 *
 * void setEpoll_wait();
 *
 * @returns void
 * @param   void
 * @throws  server::serverException
 * */
    void setEpoll_wait();



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
 * @throws  server::serverException
 * */
    int accessor_socket_flag(int&, int, int);

/**
 * Private methode of server class
 *
 * check if is a request try to connect with a server socket
 *
 * bool is_server_socket_already_conected();
 *
 * @returns bool false if is a sever socket than true
 * @param    event is an epoll event to manage
 * @throws  none
 * */
    bool is_server_socket_already_connected(epollEvent &);

/**
 * Private methode of server class
 *
 * accept new request connection, create client socket,
 * set it and add to epoll event to monitoring
 *
 * int connect_new_client(epoll_event & event);
 *
 * @returns void
 * @param   client socket to disconnect
 * @throws  server::serverException
 * */
    int connect_new_client(epoll_event & event);

/**
 * Private methode of server class
 *
 * accept new request connection, create client socket,
 * set it and add to epoll event to monitoring
 *
 * int disconnect_client(int);
 *
 * @returns void
 * @param   client socket to disconnect
 * @throws  server::serverException
 * */
    int disconnect_client(int);

/**
 * Private methode of server class
 *
 * accept new request connection, create client socket,
 * set it and add to epoll event to monitoring
 *
 * int keep_alive(int);
 *
 * @returns void
 * @param   client socket to disconnect
 * @throws  server::serverException
 * */
    int keep_alive(int);




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
 * class serverException;
 *
 * @inherit std::exception
 **/
    class serverException: public std::exception
    {
    public:

        /**
         * Constructor of serverException class
         *
         * serverException(const char * message, int statusCode);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        serverException(const char * message, int statusCode);

        /**
         * Copy constructor of serverException class
         *
         * serverException(serverException &);
         *
         * @param   serverException instance to build the serverException
         *          server_socket in an int to close
         * @throw   none
         **/
        serverException(const serverException &);

        /**
         * Operator overload= of serverException class
         *
         * operator=(const serverException&);
         *
         * @param   serverException instance const to copy the serverException
         * @throw   none
         **/
        serverException& operator=(const serverException &);

        /**
        * Destructor of serverException class
        *
        * virtual ~serverException() throw();
        *
        * @throw   none
        **/
        virtual ~serverException() throw();

        /**
         * Public methode of serverException
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
        int             _statusCode;
    };


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
 */
    void launcher();






/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/



};


#endif //WEBSERV_SERVER_CLASS_HPP