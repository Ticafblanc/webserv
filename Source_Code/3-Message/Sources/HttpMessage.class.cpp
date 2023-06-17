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


#include <Source_Code/3-Message/Includes/HttpMessage.class.hpp>

/*
*==========================================================================================================
*|                                                  HttpMessage                                          |
*==========================================================================================================
*/

HttpMessage::HttpMessage(Socket& client, Config& config)
: _client(client),
  _config(config),
  _request(_client, config),
  _execute(_request, config, _client){
    _request.recvMessage();
    findTokenServer();
    _execute.executeRequest(_serverToken);
}

HttpMessage::~HttpMessage() {}

HttpMessage::HttpMessage(const HttpMessage & other)
: _client(other._client), _config(other._config),
_request(other._request), _execute(other._execute){}

HttpMessage &HttpMessage::operator=(const HttpMessage &rhs) {
    if (this != &rhs) {
        this->_client = rhs._client;
        this->_config = rhs._config;
        this->_request = rhs._request;
        this->_execute = rhs._execute;
    }
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/


void HttpMessage::findTokenServer() {
    std::string serverName = _request.getValueHeader("Host:");
    if (serverName.empty())
        throw HttpMessage::httpMessageException("no host");
    else{
        Socket & server = _config._mapFdSocket.at(_client.getclient()._server);
        if ((_serverToken = server.findServerName(serverName)).empty())
            throw HttpMessage::httpMessageException("404 not found");
    }
}


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





