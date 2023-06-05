/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverSocket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket/Includes/serverSocket.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/
serverSocket::serverSocket() {}

serverSocket::serverSocket(blocServer &blocServer, string &ipAddr, int &port)
: Socket(blocServer, ipAddr, port) {}

serverSocket::~serverSocket() {}

serverSocket::serverSocket(const serverSocket& other) : Socket(other) {}
                                      
serverSocket& serverSocket::operator=(const serverSocket& rhs){
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

serverSocket::serverSocketException::serverSocketException(const char * message)
: _message(message) {}

serverSocket::serverSocketException::~serverSocketException() throw() {}

const char * serverSocket::serverSocketException::what() const throw() { return _message.c_str(); }

serverSocket::serverSocketException::serverSocketException(const serverSocket::serverSocketException & other) : _message(other._message) {}

serverSocket::serverSocketException &serverSocket::serverSocketException::operator=(const serverSocket::serverSocketException &rhs) {
    this->_message = rhs._message;
    return *this;
}


/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/


void serverSocket::manageEvent(epoll_event &event) {
    if ((event.events & EPOLLERR) || (event.events & EPOLLHUP) || (!(event.events & EPOLLIN)))
    {
        throw serverSocketException(strerror(errno));
    }
    if (isConnectionPossible()){
        connectNewClient(event);
    }
}

/*
*====================================================================================
*|                                 private utils function to launch                 |
*====================================================================================
*/

bool serverSocket::isConnectionPossible(){
    //number connection
    return true;
}

void serverSocket::connectNewClient(epoll_event & event) {
    clientSocket newClient(_blocServer, event);
   _blocServer._config._mapFdSocket[newClient.data.fd] = newClient;
}





