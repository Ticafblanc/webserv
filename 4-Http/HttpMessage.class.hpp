/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HTTPMESSAGE_HPP
#define WEBSERV_HTTPMESSAGE_HPP

#include "0-Main/Includes/webserv.hpp"
#include "HttpRequest.class.hpp"
#include "Execute.class.hpp"
#include "HttpReponse.class.hpp"
//User-Agent : spécifie l'agent utilisateur (généralement le navigateur) qui envoie la requête
//Accept : indique les types de contenu que le client peut accepter de la part du serveur
//        Authorization : fournit des informations d'identification pour l'authentification du client
//Cookie : envoie des cookies stockés par le client au serveur
//        Content-Type : spécifie le type de contenu inclus dans une requête POST ou PUT
//Content-Length : indique la longueur du corps de la requête en octets
//Host : indique le nom d'hôte et éventuellement le numéro de port du serveur
//Referer : spécifie l'URL de la page précédente à partir de laquelle la requête a été déclenchée
//Origin : indique l'origine de la requête Cross-Origin Resource Sharing (CORS)
//If-Modified-Since : permet aux clients de vérifier si une ressource a été modifiée depuis une date spécifiée
//        Cache-Control : spécifie les directives de mise en cache pour les serveurs et les clients

//_map_client_socket.erase(client_socket);
//
//allow_methods
//        send_data_client(new_client_socket,
//                         set_html_content("/usr/local/var/www/webserv.com/accueille.html"));//@todo set server html root
//        cgi_pass

//https://datatracker.ietf.org/doc/html/rfc2616#section-14.10


/*
*==========================================================================================================
*|                                                  http message                                        |
*==========================================================================================================
*/

class HttpMessage {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Socket&                         _server;
    Socket&                         _client;
    Config&                         _config;
    HttpRequest                     _request;
    Execute                         _execute;
    HttpReponse                     _reponse;
    std::string                     _serverToken;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/



/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpMessage class
 *
 * HttpMessage(Config & config);
 *
 * @param   config &
 * @throw   none
 **/
    HttpMessage(Socket& server, Socket& client, Config& config);

/**
* Destructor of HttpMessage class
*
* HttpMessage);
*
* @throw   none
**/
    ~HttpMessage();

/**
 * Copy constructor of HttpMessage class
 *
 * HttpMessage(const HttpMessage &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpMessage(const HttpMessage &);

/**
 * Operator overload= of HttpMessage class
 *
 * HttpMessage(const HttpMessage &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpMessage& operator=(const HttpMessage &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void sendData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void findTokenServer();

/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of HttpMessage class
 *
 * class httpMessageException;
 *
 * @inherit std::exception
 **/
    class httpMessageException: public std::exception
    {
    public:

        /**
         * Constructor of httpMessageException class
         *
         * httpMessageException(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        httpMessageException(const char * message);

        /**
         * Copy constructor of httpMessageException class
         *
         * httpMessageException(httpMessageException &);
         *
         * @param   http_request_exception instance to build the httpMessageException
         *          http_request_socket in an int to close
         * @throw   none
         **/
        httpMessageException(const httpMessageException &);

        /**
         * Operator overload= of httpMessageException class
         *
         * operator=(const httpMessageException&);
         *
         * @param   http_request_exception instance const to copy the httpMessageException
         * @throw   none
         **/
        httpMessageException& operator=(const httpMessageException &);

        /**
        * Destructor of httpMessageException class
        *
        * virtual httpMessageException throw();
        *
        * @throw   none
        **/
        virtual ~httpMessageException() throw();

        /**
         * Public methode of httpMessageException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "socket error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string     _message;
    };



};


#endif //WEBSERV_HTTP_REQUEST_HPP
