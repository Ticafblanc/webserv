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

HttpMessage::HttpMessage(Socket& server, Socket& client, Config& config)
: _server(server),
  _client(client),
  _config(config),
  _request(_client, config),
  _execute(_request, config),
  _reponse(_client, _execute, config) {
    try {
        _request.recvMessage();
        findTokenServer();
        _execute.executeRequest(_serverToken);
        _reponse.sendMessage();
    }catch (std::exception & e){
        _config.errorLog.writeLogFile(e.what());
        std::cerr << e.what() << std::endl;
    }

}

HttpMessage::~HttpMessage() {}

HttpMessage::HttpMessage(const HttpMessage & other)
: _server(other._server), _client(other._client), _config(other._config),
_request(other._request), _execute(other._execute), _reponse(other._reponse){}

HttpMessage &HttpMessage::operator=(const HttpMessage &rhs) {
    if (this != &rhs) {
        this->_client = rhs._client;
        this->_server = rhs._server;
        this->_config = rhs._config;
        this->_request = rhs._request;
        this->_execute = rhs._execute;
        this->_reponse = rhs._reponse;
    }
    return *this;
}

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/
void HttpMessage::findTokenServer() {
    _serverToken = _request.getValueHeader("Host:");
    if (_serverToken.empty())
        throw HttpMessage::httpMessageException("no host");
    else{
        std::map<std::string, ConfigServer>::iterator it = _config.mapConfigServer.find(_serverToken);
        if (it == _config.mapConfigServer.end())
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





