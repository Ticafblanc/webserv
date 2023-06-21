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
  _execute(_request, config, _client){
    try {
        _client.getclient()._request.recvHeader();
        findTokenServer();
        findBestConfig();
        _execute.executeRequest(_bestConfig->second);
    }
    catch (const Exception & e){
        _client.getclient()._statusCode = e.getCode();//400;//501 methode inconu
        _client.getclient()._connection = false;
        _execute.defaultPage(client.getclient()._statusCode);
        HttpReponse error(client, config);
    }
}

HttpMessage::~HttpMessage() {}

HttpMessage::HttpMessage(const HttpMessage & other)
: _client(other._client), _config(other._config),
_request(other._request), _execute(other._execute){}

HttpMessage &HttpMessage::operator=(const HttpMessage &rhs) {
    if (this != &rhs) {
        this->_client = rhs._client;
        this->_config = rhs._config;
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
    std::string serverName = _client.getclient()._request.getValueHeader("Host:");
    if (serverName.empty())
        throw Exception("No host in request", 400);
    else{
        Socket & server = _config._mapFdSocket.at(_client.getclient()._server);
        _serverToken = server.findServerName(serverName);
        if (_serverToken.empty())
            throw Exception("server name not found", 404);
    }
}


void HttpMessage::findBestConfig() {
    std::string& url = _request.getUrl();
    std::vector<std::pair<std::string, Config> > & vecUriConfig = _config._mapTokenVectorUriConfig.find(_serverToken)->second;
    _bestConfig = vecUriConfig.end();

    for (std::vector<std::pair<std::string, Config> >::iterator itvec = vecUriConfig.begin();
         itvec != vecUriConfig.end(); ++itvec) {
        if (url.find(itvec->first) == 0 && itvec->first.length() > _bestConfig->first.length())
            _bestConfig = itvec;
    }
    url = _bestConfig->second._root + url.substr(_bestConfig->first.length() - 1);
}




//client.getclient()._content ="<!DOCTYPE html>\n"
//                             "<html><head><title>"+ _config._code.getStatusCode(error) + "</title></head>"
//                                                                                         "<body><h1>" + _config._code.getStatusCode(error) + "</h1><p>Sorry</p></body></html>";
//client.getclient()._contentType = "text/html";

//_client.getclient()._content ="<!DOCTYPE html>\n"
//                              "<html><head><title>"+ _config._code.getStatusCode(error) + "</title></head>"
//                                                                                          "<body><h1>" + _config._code.getStatusCode(error) + "</h1><p>Sorry</p></body></html>";
//_client.getclient()._contentType = "text/html";

