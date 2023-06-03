/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbaseSocket.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_ABASESOCKET_CLASS_HPP
#define WEBSERV_ABASESOCKET_CLASS_HPP

#include "webserv.hpp"

class AbaseSocket : public epoll_event, public sockaddr_in{

/*>*******************************private section**********************************/

protected:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    std::string     _ipAddress;
    int             _port;
    blocServer&     _blocServer;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/



/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                      Fonction                                    |
*====================================================================================
*/

/**
 * Constructor of AbaseSocket class
 *
 * AbaseSocket();
 *
 * @param   void 
 * @throw   none
 **/
    AbaseSocket();

/**
 * Constructor of AbaseSocket class
 *
 * AbaseSocket(blocServer& blocServer, string &ipAddr, int &port);
 *
 * @param   void
 * @throw   none
 **/
    AbaseSocket(blocServer& blocServer, string &ipAddr, int &port);

/**
 * Constructor of AbaseSocket class
 *
 * AbaseSocket(blocServer& blocServer, epoll_event &event);
 *
 * @param   sockaddr instance to sockaddres_in
 * @param   event instance to epoll_event
 * @throw   socket::socketException
 **/
    AbaseSocket(blocServer& blocServer, epoll_event &event);

/**
 * Destructor of AbaseSocket class
 *
 * AbaseSocket();
 **/
    virtual ~AbaseSocket();

/**
 * Copy constructor of AbaseSocket class
 *
 * AbaseSocket(AbaseSocket &);
 *
 * @param   socket instance to build the AbaseSocket
 * @throw   none
 **/
    AbaseSocket(const AbaseSocket &other);

/**
 * Operator overload= of AbaseSocket class
 *
 * operator=(const AbaseSocket&);
 *
 * @param   socket instance const to copy the AbaseSocket
 * @throw   none
 **/
    AbaseSocket& operator=(const AbaseSocket &);


/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of AbaseSocket class
 *
 * class socketException;
 *
 * @inherit std::exception
 **/
    class socketException: public std::exception
    {
    public:

        /**
         * Constructor of socketException class
         *
         * socketException(const char * message, int statusCode);
         *
         * @param   socket is a AbaseSocket reference to set the private _socketFd
         *          to manage the close of AbaseSocket class
         *          message to store const char*
         * @throw   none
         **/
        socketException(const char * message);

        /**
         * Copy constructor of socketException class
         *
         * socketException(socketException &);
         *
         * @param   socketException instance to build the socketException
         *          socket_socket in an int to close
         * @throw   none
         **/
        socketException(const socketException &);

        /**
         * Operator overload= of socketException class
         *
         * operator=(const socketException&);
         *
         * @param   socketException instance const to copy the socketException
         * @throw   none
         **/
        socketException& operator=(const socketException &);

        /**
        * Destructor of socketException class
        *
        * virtual ~socketException() throw();
        *
        * @throw   none
        **/
        virtual ~socketException() throw();

        /**
         * Public methode of socketException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "AbaseSocket error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string     _message;
    };


/*
*====================================================================================
*|                                      Methode                                     |
*====================================================================================
*/

/**
 * Public methode of AbaseSocket struct
 *
 * void setSockaddrIn(std::string & ip_address, int & port);
 *
 * @returns     void
 * @throw       socketException
 */
    void setSockaddrIn();

/**
 * Public methode of AbaseSocket struct
 *
 *     void getSockaddrIn(const sockaddr_in& addr);
 *
 * @returns     void
 * @param       addr to extract data
 * @throw       socketException
 */
    void getSockaddrIn();

/**
 * Private methode of AbaseSocket class
 *
 * create a new AbaseSocket with fonction AbaseSocket
 *
 * @see https://man7.org/linux/man-pages/man2/AbaseSocket.2.html
 *
 * int AbaseSocket(int domain, int protocol);
 *
 * tcp_socket = AbaseSocket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = AbaseSocket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = AbaseSocket(AF_INET, SOCK_RAW, protocol);
 *
 * nginx work only on tcp protocol !!
 *
 * std::string set_socket();
 *
 * @returns void
 * @param   void
 * @throws  socketException
 **/
    void setSocket();

/**
 * Private methode of AbaseSocket class
 *
 * set the option of AbaseSocket AbaseSocket already created
 *
 * std::string setSocketOption();
 *
 * @returns void
 * @param   void
 * @throws  socketException
 *
 * @see https://linux.die.net/man/3/setsockopt
 * */
    void setSocketOption();

/**
 * Private methode of AbaseSocket class
 *
 * associate an IP address and a port number with a AbaseSocket already created
 *
 * std::string setBind();
 *
 * @returns void
 * @param   void
 * @throws  socketException
 *
 * @see https://man7.org/linux/man-pages/man2/bind.2.html
 * */
    void setBind();

/**
 * Private methode of listen data class
 *
 * set the listen option so the number of possible connexion
 *
 * std::string setListen();
 *
 * @returns void
 * @param   backlog is wait number of connection 5-10
 * @throws  socketException
 *
 * @see https://man7.org/linux/man-pages/man2/listen.2.html
 * */
    void setListen(int backlog) const;

/**
 * Private methode of AbaseSocket class
 *
 * accessor of AbaseSocket to get or set the flag option
 * set fnctl like subject fcntl(fd, F_SETFL, O_NONBLOCK)
 * don't show the actual flag in AbaseSocket and force to change it to non blocking
 *
 * void accessor_socket(int& socket_socket, int command, int flag);
 *
 * @returns return the flag set in socket_socket
 * @param   Command  (cmd) for accessor AbaseSocket :
 *          F_SETFD      Set the file descriptor flags to arg.
 *          F_GETFL      Get descriptor status flags, as described below (arg is ignored).
 *
 * @param   Flag for accessor AbaseSocket :
 *          O_NONBLOCK   Non-blocking I/O; if no data is available to a read(2)
 *          call, or if a write(2) operation would block, the read
 *          or write call returns -1 with the error EAGAIN
 *          O_APPEND     Force each write to append at the end of file;
 *          corresponds to the O_APPEND flag of open(2).
 *          O_ASYNC      Enable the SIGIO signal to be sent to the process
 *          group when I/O is possible, e.g., upon availability of
 *          data to be read.
 *
 * @throws  socket::socketException
 * */
    void accessorSocketFlag(int  command, int  flag) const;

/**
 * Private methode of socket class
 *
 * set epollEvent instance with AbaseSocket and type of event to follow
 * before to add a epollEvent to baseEpoll
 *
 * int setEpollEvent(int & socket_socket, struct epoll_event & event, int & events);
 *
 * @returns void
 * @param   flag is int to add to the event
 *          EPOLLIN the event occurs when data can be read from the file descriptor
 *          EPOLLOUT the event occurs when data can be written to the file descriptor
 *          EPOLLERR the event occurs when there is an error on the file descriptor
 *          EPOLLRDHUP the event occurs when the connection is closed by the remote peer
 *          EPOLLHUP the event occurs when the file descriptor is closed by the local peer
 *          EPOLLET edge triggering mode
 *          EPOLLONESHOT single trigger mode
 *
 * @throws  socket::socketException
 * */
    void setEpollEvent(int flag);

    void acceptConnection();

/**
 * Private methode of socket class
 *
 * int getSocket() const;
 *
 * @returns int socket fd
 * @param   void
 * */
    int getSocket() const;

/**
 * Private methode of socket class
 *
 * void buildServerSocket();
 *
 * @returns void
 * @param   void
 * */
    void buildServerSocket();

/**
 * Private methode of socket class
 *
 * void buildClientSocket();
 *
 * @returns void
 * @param   void
 * */
    void buildClientSocket();
/**
 * Private methode of socket class
 *
 * void closeSocket();
 *
 * @returns void
 * @param   void
 * */
    void closeSocket() const;

/**
 * Private methode of socket class
 *
 * virtual void manageEvent(epoll_event & event, AbaseSocket & sock) = 0;
 *
 *
 * @returns void
 * @param   void
 * */
    virtual void manageEvent(epoll_event & event) = 0;


};

#endif //WEBSERV_ABASESOCKET_CLASS_HPP