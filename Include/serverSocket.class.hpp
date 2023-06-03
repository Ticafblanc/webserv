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

#include "webserv.hpp"


class serverSocket : public AbaseSocket{

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    struct epoll_event                              _webservEvent, *_serverEvents;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/



/**
 * Private methode of serverSocket class
 *
 * check if is a request try to connect with a serverSocket AbaseSocket
 *
 * bool is_server_socket_already_conected();
 *
 * @returns bool false if is a sever AbaseSocket than true
 * @param    event is an baseEpoll event to manage
 * @throws  none
 * */
    bool isServerSocketAlreadyConnected(epoll_event & event, std::set<baseSocket>::iterator & itSetClient);

/**
 * Private methode of serverSocket class
 *
 * accept new request connection, create AbaseSocket AbaseSocket,
 * set it and add to baseEpoll event to monitoring
 *
 * int connectNewClient(epoll_event & event, std::set<AbaseSocket>::iterator &);
 *
 * @returns void
 * @param   client AbaseSocket to disconnect
 * @throws  server::serverException
 * */
    bool isNotNewClient(epoll_event & event, std::set<baseSocket>::iterator &);

/**
 * Private methode of serverSocket class
 *
 * accept new request connection, create AbaseSocket AbaseSocket,
 * set it and add to baseEpoll event to monitoring
 *
 * int disconnectClient(int);
 *
 * @returns void
 * @param   client AbaseSocket to disconnect
 * @throws  server::serverException
 * */
    void disconnectClient(std::set<baseSocket>::iterator & itSetClient);

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
 * @param   configWebserv instance to build the serverSocket
 * @throw   none
 **/
    serverSocket(configWebserv &);

/**
 * Destructor of sever class
 *
 * ~sever();
 *
 * @throw   none
 **/
    ~serverSocket();

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
         * @param   server is a serverSocket reference to set the private _server
         *          to manage the close of serverSocket class
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
         *          at the construction defaut constructor "AbaseSocket error"
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
 */
    virtual void manageEvent(epoll_event & event, baseSocket & sock);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/



};


#endif //WEBSERV_SERVER_CLASS_HPP