/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientSocket.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:27:31 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/31 21:54:51 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/clientSocket.class.hpp"

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/
clientSocket::clientSocket() : _request(*this), _connection("keep-alive") {}

clientSocket::clientSocket(blocServer &blocServer, epoll_event & event)
: AbaseSocket(blocServer, event), _request(*this), _connection("keep-alive") {}

clientSocket::~clientSocket() {}

clientSocket::clientSocket(const clientSocket& other) : AbaseSocket(other), _request(other._request), _connection("keep-alive") {}
                                      
clientSocket& clientSocket::operator=(const clientSocket& rhs){
    this->_request = rhs._request;
    return *this;
}

/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

clientSocket::clientSocketException::clientSocketException(const char * message)
: _message(message) {}

clientSocket::clientSocketException::~clientSocketException() throw() {}

const char * clientSocket::clientSocketException::what() const throw() { return _message.c_str(); }

clientSocket::clientSocketException::clientSocketException(const clientSocket::clientSocketException & other) : _message(other._message) {}

clientSocket::clientSocketException &clientSocket::clientSocketException::operator=(const clientSocket::clientSocketException &rhs) {
    this->_message = rhs._message;
    return *this;
}


/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/


void clientSocket::manageEvent(epoll_event &event) {
    if ((event.events & EPOLLERR) || (event.events & EPOLLHUP) || (!(event.events & EPOLLIN)))
    {
        throw clientSocketException(strerror(errno));//deconnexion
    }
    _request.manageRequest();
}

/*
*====================================================================================
*|                                 private utils function to launch                 |
*====================================================================================
*/









