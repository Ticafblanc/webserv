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

#include "3-Config/Config.class.hpp"
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


class HttpMessage;

struct  HttpHeader{
    std::map<std::string, std::string>
    HttpHeader() {

    }
};


/*
*==========================================================================================================
*|                                                  http token                                        |
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
int&                                                        _socket;
    Server&                                                _server;
    std::map<int, std::string>                             _map_status_code;
    ssize_t                                                _bytes_exchange;
    std::vector<std::string>                               _buffer;



/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void recvData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void recvData();

/**
 * Private methode of HttpMessage class
 *
 * manage event like receive data
 *
 * std::string manage_event_already_conected(epoll_event & event);
 *
 * @returns std::string action to do for server
 * @param   event is an epoll event to manage
 * @throws  http_request::http_request_exception
 * */
    std::string manage_event_already_connected(epoll_event &);



/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void set_reply();
 *
 * @returns void
 * @param   void
 * @throws  none
 * */
    void set_reply();

/**
 * Private methode of HttpMessage class
 *
 * add headers befor send
 *
 * void set_content();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    void set_content();

/**
 * Private methode of HttpMessage class
 *
 * set headers befor send
 *
 * std::string set_headers();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    void set_header();

/**
 * Private methode of HttpMessage class
 *
 * add buffer to send
 *
 * std::string add_status_code();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    std::string add_status_code();

/**
 * Private methode of HttpMessage class
 *
 * add buffer to send
 *
 * std::string add_status_code();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    std::string add_content_info();

/**
 * Private methode of HttpMessage class
 *
 * add buffer to send
 *
 * std::string add_connection();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    std::string add_connection();
/**
 * Private methode of HttpMessage class
 *
 * add buffer to send
 *
 * void set_buffer();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    void set_buffer();

/**
 * Public methode of HttpMessage struct
 *
 * void set_map_status_code();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_status_code();
/**
 * Public methode of HttpMessage struct
 *
 * void set_map_content_type();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_content_type();

/**
 * Public methode of HttpMessage struct
 *
 * void set_map_token_methode();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token_methode();

/**
 * Public methode of HttpMessage struct
 *
 * void set_map_token_information();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token_information();

/**
 * Protected methode of HttpMessage class
 *
 * std::string get_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string get_methode();

/**
 * Protected methode of HttpMessage class
 *
 * std::string post_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string post_methode();

/**
 * Protected methode of HttpMessage class
 *
 * std::string delete_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string delete_methode();

/**
 * Protected methode of HttpMessage class
 *
 * std::string extract_http_version();
 *
 * @returns     version of http
 * @param       void
 * @throw       none
 */
    std::string extract_unused_information();
/**
 * Protected methode of HttpMessage class
 *
 * std::string extract_location();
 *
 * @returns     path of location resource
 * @param       void
 * @throw       none
 */
    std::string extract_location();

/**
 * Protected methode of HttpMessage class
 *
 * std::string extract_http_version();
 *
 * @returns     version of http
 * @param       void
 * @throw       none
 */
    std::string extract_http_version();

/**
 * Protected methode of HttpMessage class
 *
 * std::string connection_information();
 *
 * @returns     version of http
 * @param       void
 * @throw       none
 */
    std::string connection_information();

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
    HttpMessage( Socket& socket, Server& server);

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
 * set headers befor send
 *
 * void manageRequest();
 *
 * @returns std::string ready to send
 * @param   Content-Length to add to headers
 * @throws  http_request::http_requestexception
 * */
    void manageRequest();

/**
 * Private methode of server class
 *
 * send _body_buffer to client
 *
 * void send_data_client(int);
 *
 * @returns void
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void send_data_client(int);

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
