/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientSocket.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_CLIENTSOCKET_CLASS_HPP
# define WEBSERV_CLIENTSOCKET_CLASS_HPP

#include "webserv.hpp"


class clientSocket : public AbaseSocket{

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    httpRequest     _request;
    std::string     _connection;

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
 * Constructor of client class
 *
 * client();
 *
 * @param   configWebserv instance to build the clientSocket
 * @throw   none
 **/
    clientSocket();

/**
 * Constructor of client class
 *
 * client(data_client *);
 *
 * @param   configWebserv instance to build the clientSocket
 * @throw   none
 **/
    clientSocket(blocServer& blocServer, epoll_event & event);

/**
 * Destructor of client class
 *
 * ~client();
 *
 * @throw   none
 **/
    virtual ~clientSocket();

/**
 * Copy constructor of client class
 *
 * client(clientSocket &);
 *
 * @param   client instance to build the clientSocket
 * @throw   none
 **/
    clientSocket(const clientSocket &);

/**
 * Operator overload= of client class
 *
 * operator=(const clientSocket&);
 *
 * @param   client instance const to copy the clientSocket
 * @throw   none
 **/
    clientSocket& operator=(const clientSocket &);


/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of client class
 *
 * class clientSocketException;
 *
 * @inherit std::exception
 **/
    class clientSocketException: public std::exception
    {
    public:

        /**
         * Constructor of clientException class
         *
         * clientException(const char * message, int statusCode);
         *
         * @param   client is a clientSocket reference to set the private _client
         *          to manage the close of clientSocket class
         *          message to store const char*
         * @throw   none
         **/
        clientSocketException(const char * message);

        /**
         * Copy constructor of clientException class
         *
         * clientException(clientException &);
         *
         * @param   clientException instance to build the clientException
         *          client_socket in an int to close
         * @throw   none
         **/
        clientSocketException(const clientSocketException &);

        /**
         * Operator overload= of clientException class
         *
         * operator=(const clientException&);
         *
         * @param   clientException instance const to copy the clientException
         * @throw   none
         **/
        clientSocketException& operator=(const clientSocketException &);

        /**
        * Destructor of clientException class
        *
        * virtual ~clientException() throw();
        *
        * @throw   none
        **/
        virtual ~clientSocketException() throw();

        /**
         * Public methode of clientException
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
 * Public methode of client class
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


#endif //WEBSERV_CLIENTSOCKET_CLASS_HPP