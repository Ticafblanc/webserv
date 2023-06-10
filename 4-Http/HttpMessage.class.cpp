/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */


#include "HttpMessage.class.hpp"

/*
*==========================================================================================================
*|                                                  HttpMessage                                          |
*==========================================================================================================
*/

HttpMessage::HttpMessage(Socket& socket, Server& server)
: _socket(socket),
_server(server),
_request(socket, server),
_execute(_request),
_reponse(socket, _execute, server) {}

HttpMessage::~HttpMessage() {}

HttpMessage::HttpMessage(const HttpMessage & other)
: _socket(other._socket), _server(other._server), _request(other._request), _execute(other._execute), _reponse(other._reponse){}

HttpMessage &HttpMessage::operator=(const HttpMessage &rhs) {
    this->_socket = rhs._socket;
    this->_server = rhs._server;
    this->_request = rhs._request;
    this->_execute = rhs._execute;
    this->_reponse = rhs._reponse;
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/


/*
*====================================================================================
*|                                  Member Expetion                                 |
*====================================================================================
*/

HttpMessage::httpMessageException::httpMessageException(const char * message) : _message(message) {}

HttpMessage::httpMessageException::~httpMessageException() throw() {}

const char * HttpMessage::httpMessageException::what() const throw() { return _message.c_str(); }

HttpMessage::httpMessageException::httpMessageException(const HttpMessage::httpMessageException & other) : _message(other._message) {}

HttpMessage::httpMessageException &HttpMessage::httpMessageException::operator=(const HttpMessage::httpMessageException &rhs) {
    this->_message = rhs._message;
    return *this;
}





