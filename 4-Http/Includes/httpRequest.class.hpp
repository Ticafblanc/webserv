/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpRequest.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HTTP_REQUEST_HPP
#define WEBSERV_HTTP_REQUEST_HPP

#include "0-Main/Includes/webserv.hpp"
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
//if (request.disconection())
//accept_disconnection(_server_events[position].data.fd);
//send_data_client(_server_events[position].data.fd, request.reply());
//int                         _stat_of_server;
//std::map<int, std::string>  _status_code;
//std::string data;
//data = recv_data_client(_server_events[position].data.fd);
/*
*==========================================================================================================
*|                                                  http token                                        |
*==========================================================================================================
*/

class httpRequest {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    clientSocket&                                          _client;
    ssize_t                                                _bytes_exchange;
    std::string                                            _buffer;









//    6-PegParser                                              peg;
    std::map<int, std::string>                              _map_status_code;
    std::map<std::string , std::string>                     _map_content_type;
    int                                                     _status_code;
    std::string                                             _content_type;
    std::string                                             _connection;
    std::string                                             _content;
    std::string                                             _header_buffer;
//    std::string                                             _body_buffer;
    std::vector<std::string>                                _vector_body_buffer_next;
    std::map<std::string, std::string (httpRequest::*)()>  _mapTokenListActionMethode;
    std::map<std::string, std::string (httpRequest::*)()>  _map_token_list_action_information;


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
 * Private methode of httpRequest class
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
 * Private methode of httpRequest class
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
 * Private methode of httpRequest class
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
 * Private methode of httpRequest class
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
 * Private methode of httpRequest class
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
 * Private methode of httpRequest class
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
 * Private methode of httpRequest class
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
 * Public methode of httpRequest struct
 *
 * void set_map_status_code();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_status_code();
/**
 * Public methode of httpRequest struct
 *
 * void set_map_content_type();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_content_type();

/**
 * Public methode of httpRequest struct
 *
 * void set_map_token_methode();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token_methode();

/**
 * Public methode of httpRequest struct
 *
 * void set_map_token_information();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token_information();

/**
 * Protected methode of httpRequest class
 *
 * std::string get_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string get_methode();

/**
 * Protected methode of httpRequest class
 *
 * std::string post_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string post_methode();

/**
 * Protected methode of httpRequest class
 *
 * std::string delete_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string delete_methode();

/**
 * Protected methode of httpRequest class
 *
 * std::string extract_http_version();
 *
 * @returns     version of http
 * @param       void
 * @throw       none
 */
    std::string extract_unused_information();
/**
 * Protected methode of httpRequest class
 *
 * std::string extract_location();
 *
 * @returns     path of location resource
 * @param       void
 * @throw       none
 */
    std::string extract_location();

/**
 * Protected methode of httpRequest class
 *
 * std::string extract_http_version();
 *
 * @returns     version of http
 * @param       void
 * @throw       none
 */
    std::string extract_http_version();

/**
 * Protected methode of httpRequest class
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
 * Constructor of httpRequest class
 *
 * httpRequest(Server &  server);
 *
 * @param   blocServer &
 * @throw   none
 **/
    httpRequest(clientSocket & client);

/**
* Destructor of httpRequest class
*
* httpRequest);
*
* @throw   none
**/
    ~httpRequest();

/**
 * Copy constructor of httpRequest class
 *
 * httpRequest(const httpRequest &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    httpRequest(const httpRequest &);

/**
 * Operator overload= of httpRequest class
 *
 * httpRequest(const httpRequest &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    httpRequest& operator=(const httpRequest &);

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
 * Class exception of httpRequest class
 *
 * class httpRequestException;
 *
 * @inherit std::exception
 **/
    class httpRequestException: public std::exception
    {
    public:

        /**
         * Constructor of httpRequestException class
         *
         * httpRequestException(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        httpRequestException(const char * message);

        /**
         * Copy constructor of httpRequestException class
         *
         * httpRequestException(httpRequestException &);
         *
         * @param   http_request_exception instance to build the httpRequestException
         *          http_request_socket in an int to close
         * @throw   none
         **/
        httpRequestException(const httpRequestException &);

        /**
         * Operator overload= of httpRequestException class
         *
         * operator=(const httpRequestException&);
         *
         * @param   http_request_exception instance const to copy the httpRequestException
         * @throw   none
         **/
        httpRequestException& operator=(const httpRequestException &);

        /**
        * Destructor of httpRequestException class
        *
        * virtual httpRequestException throw();
        *
        * @throw   none
        **/
        virtual ~httpRequestException() throw();

        /**
         * Public methode of httpRequestException
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
