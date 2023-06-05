/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_SERVERSOCKET_CLASS_HPP
# define WEBSERV_SERVERSOCKET_CLASS_HPP

#include "Socket.Aclass.hpp"


class serverSocket : public Socket{

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/



/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/



/**
 * Private methode of serverSocket class
 *
 * check if is a request try to connect with a serverSocket 7-Socket
 *
 * bool isConnectionPossible();
 *
 * @returns bool false if is a sever 7-Socket than true
 * @param    event is an 5-Epoll event to manage
 * @throws  none
 * */
    bool isConnectionPossible();

/**
 * Private methode of serverSocket class
 *
 * accept new request connection, create 7-Socket 7-Socket,
 * set it and add to 5-Epoll event to monitoring
 *
 * void connectNewClient(epoll_event & event);
 *
 * @returns void
 * @param   client 7-Socket to disconnect
 * @throws  server::serverException
 * */
    void connectNewClient(epoll_event & event);

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
 * sever();
 *
 * @param   configWebserv instance to build the serverSocket
 * @throw   none
 **/
    serverSocket();

/**
 * Constructor of sever class
 *
 * sever(data_server *);
 *
 * @param   configWebserv instance to build the serverSocket
 * @throw   none
 **/
    serverSocket(Server& Server, string &ipAddr, int &port);

/**
 * Destructor of sever class
 *
 * ~sever();
 *
 * @throw   none
 **/
    virtual ~serverSocket();

/**
 * Copy constructor of sever class
 *
 * sever(serverSocket &);
 *
 * @param   server instance to build the serverSocket
 * @throw   none
 **/
    serverSocket(const serverSocket &);

/**
 * Operator overload= of sever class
 *
 * operator=(const serverSocket&);
 *
 * @param   server instance const to copy the serverSocket
 * @throw   none
 **/
    serverSocket& operator=(const serverSocket &);


/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of sever class
 *
 * class serverSocketException;
 *
 * @inherit std::exception
 **/
    class serverSocketException: public std::exception
    {
    public:

        /**
         * Constructor of serverException class
         *
         * serverException(const char * message, int statusCode);
         *
         * @param   server is a serverSocket reference to set the private _server
         *          to manage the close of serverSocket class
         *          message to store const char*
         * @throw   none
         **/
        serverSocketException(const char * message);

        /**
         * Copy constructor of serverException class
         *
         * serverException(serverException &);
         *
         * @param   serverException instance to build the serverException
         *          server_socket in an int to close
         * @throw   none
         **/
        serverSocketException(const serverSocketException &);

        /**
         * Operator overload= of serverException class
         *
         * operator=(const serverException&);
         *
         * @param   serverException instance const to copy the serverException
         * @throw   none
         **/
        serverSocketException& operator=(const serverSocketException &);

        /**
        * Destructor of serverException class
        *
        * virtual ~serverException() throw();
        *
        * @throw   none
        **/
        virtual ~serverSocketException() throw();

        /**
         * Public methode of serverException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "7-Socket error"
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
 * Public methode of sever class
 *
 * void launcher();
 *
 * @returns void
 * @param void
 * @throw none
 *
 */
    virtual void manageEvent(epoll_event & event);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/



};


#endif //WEBSERV_SERVERSOCKET_CLASS_HPP