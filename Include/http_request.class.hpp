/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_request.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HTTP_REQUEST_HPP
#define WEBSERV_HTTP_REQUEST_HPP

#include "../Include/header.hpp"
#include "../Include/peg_parser.class.hpp"
#include "../Include/config_webserv.class.hpp"
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

class http_request {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    config_webserv                                          &_config;
    peg_parser                                              peg;
    std::map<int, std::string>                              _map_status_code;
    std::map<std::string , std::string>                     _map_content_type;
    int                                                     _status_code;
    std::string                                             _content_type;
    std::string                                             _connection;
    std::string                                             _buffer;
    std::string                                             _header_buffer;
    std::string                                             _body_buffer;
    std::vector<std::string>                                _vector_body_buffer_next;
    std::map<std::string, std::string (http_request::*)()>  _map_token_list_action_methode;
    std::map<std::string, std::string (http_request::*)()>  _map_token_list_action_information;



/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

/**
 * Private methode of http_request class
 *
 * check if is a request try to connect with a server socket
 *
 * bool is_server_socket_already_conected();
 *
 * @returns bool false if is a sever socket than true
 * @param    event is an epoll event to manage
 * @throws  none
 * */
    bool is_server_socket_already_connected(epoll_event &);

/**
 * Private methode of http_request class
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
 * std::string recv_data_client(int client_socket);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string recv_data_client(int);

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
 * Private methode of http_request class
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
 * Private methode of http_request class
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
 * Private methode of http_request class
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
 * Private methode of http_request class
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
 * Private methode of http_request class
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
 * Private methode of http_request class
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
 * Public methode of http_request struct
 *
 * void set_map_status_code();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_status_code();
/**
 * Public methode of http_request struct
 *
 * void set_map_content_type();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_content_type();

/**
 * Public methode of http_request struct
 *
 * void set_map_token_methode();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token_methode();

/**
 * Public methode of http_request struct
 *
 * void set_map_token_information();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token_information();

/**
 * Protected methode of http_request class
 *
 * std::string get_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string get_methode();

/**
 * Protected methode of http_request class
 *
 * std::string post_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string post_methode();

/**
 * Protected methode of http_request class
 *
 * std::string delete_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string delete_methode();

/**
 * Protected methode of http_request class
 *
 * std::string extract_http_version();
 *
 * @returns     version of http
 * @param       void
 * @throw       none
 */
    std::string extract_unused_information();
/**
 * Protected methode of http_request class
 *
 * std::string extract_location();
 *
 * @returns     path of location resource
 * @param       void
 * @throw       none
 */
    std::string extract_location();

/**
 * Protected methode of http_request class
 *
 * std::string extract_http_version();
 *
 * @returns     version of http
 * @param       void
 * @throw       none
 */
    std::string extract_http_version();

/**
 * Protected methode of http_request class
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
 * Constructor of http_request class
 *
 * http_request(config_webserv & config);
 *
 * @param   config_webserv &
 * @throw   none
 **/
    http_request(config_webserv &);

/**
* Destructor of http_request class
*
* ~http_request();
*
* @throw   none
**/
    ~http_request();

/**
 * Copy constructor of http_request class
 *
 * http_request(const http_request &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    http_request(const http_request &);

/**
 * Operator overload= of http_request class
 *
 * http_request(const http_request &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    http_request& operator=(const http_request &);

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
 * std::string set_headers(size_t Content-Length);
 *
 * @returns std::string ready to send
 * @param   Content-Length to add to headers
 * @throws  http_request::http_requestexception
 * */
    std::string manage_request(epoll_event&);

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
 * Class exception of http_request class
 *
 * class http_request_exception;
 *
 * @inherit std::exception
 **/
    class http_request_exception: public std::exception
    {
    public:

        /**
         * Constructor of http_request_exception class
         *
         * http_request_exception(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        http_request_exception(const char * message);

        /**
         * Copy constructor of http_request_exception class
         *
         * http_request_exception(http_request_exception &);
         *
         * @param   http_request_exception instance to build the http_request_exception
         *          http_request_socket in an int to close
         * @throw   none
         **/
        http_request_exception(const http_request_exception &);

        /**
         * Operator overload= of http_request_exception class
         *
         * operator=(const http_request_exception&);
         *
         * @param   http_request_exception instance const to copy the http_request_exception
         * @throw   none
         **/
        http_request_exception& operator=(const http_request_exception &);

        /**
        * Destructor of http_request_exception class
        *
        * virtual ~http_request_exception() throw();
        *
        * @throw   none
        **/
        virtual ~http_request_exception() throw();

        /**
         * Public methode of http_request_exception
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
