/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-Client.Aclass.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_CLIENT_HPP
#define WEBSERV_CLIENT_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/3-Message/Includes/HttpHeadersRequest.class.hpp>
#include <Source_Code/3-Message/Includes/HttpBodyRequest.class.hpp>
#include <Source_Code/3-Message/Includes/HttpBodyReponse.class.hpp>
#include <Source_Code/3-Message/Includes/HttpHeadersReponse.class.hpp>
#include <Source_Code/3-Message/Includes/HttpReponse.class.hpp>

class Client : public Socket {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Config&                                             _config;
    std::time_t                                         _lastConnection;
    IHttpMessage*                                       _message;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

/**
 * Constructor of 7-Client class
 *
 * void selectRequestMessageMethode() ;
 *
 * @param   sockaddr instance to sockaddres_in
 * @param   event instance to epoll_event
 * @throw   socket::socketException
 **/
    void selectRequestMessageMethode() ;

/**
 * Constructor of 7-Client class
 *
 * void updateClient() ;
 *
 * @param   sockaddr instance to sockaddres_in
 * @param   event instance to epoll_event
 * @throw   socket::socketException
 **/
    void updateClient() ;

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                      Fonction                                    |
*====================================================================================
*/


/**
 * Constructor of 7-Client class
 *
 * 7-Client(Server.class& Server.class, epoll_event &event);
 *
 * @param   sockaddr instance to sockaddres_in
 * @param   event instance to epoll_event
 * @throw   socket::socketException
 **/
    explicit Client(epoll_event &event, Config& config, Socket * server);

/**
 * Destructor of 7-Client class
 *
 * 7-Client();
 **/
    virtual ~Client();

/**
 * Copy constructor of 7-Client class
 *
 * 7-Client(7-Client &);
 *
 * @param   socket instance to build the 7-Client
 * @throw   none
 **/
    Client(const Client &other);

/**
 * Operator overload= of 7-Client class
 *
 * operator=(const 7-Client&);
 *
 * @param   socket instance const to copy the 7-Client
 * @throw   none
 **/
    Client& operator=(const Client &);

/**
 * Operator overload= of 7-Client class
 *
 * operator=(const 7-Client&);
 *
 * @param   socket instance const to copy the 7-Client
 * @throw   none
 **/
    bool operator==(const Client &);


/*
*====================================================================================
*|                                 public method                                    |
*====================================================================================
*/
    void recvEvent();
    void sendEvent();
/*
*====================================================================================
*|                                      Accessor                                    |
*====================================================================================
*/

    bool isConnection() const;
    uint32_t getEvents() const;
    time_t getLastConnection() const;
    void setLastConnection(time_t lastConnection);


};

#endif //WEBSERV_ABASECLIENT_CLASS_HPP