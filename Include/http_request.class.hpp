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


allow_methods
        send_data_client(new_client_socket,
                         set_html_content("/usr/local/var/www/webserv.com/accueille.html"));//@todo set server html root
        cgi_pass
if (request.disconection())
accept_disconnection(_server_events[position].data.fd);
send_data_client(_server_events[position].data.fd, request.reply());
int                         _stat_of_server;
std::map<int, std::string>  _status_code;
std::string data;
data = recv_data_client(_server_events[position].data.fd);
/*
*==========================================================================================================
*|                                                  http token                                        |
*==========================================================================================================
*/



class http_request {

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of http_request class
 *
 * http_request();
 *
 * @param   void
 * @throw   none
 **/
    http_request();

/**
 * Constructor of http_request class
 *
 * http_request(std::string & path_config_file);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   none
 **/
    http_request(std::string &);

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
    http_request(http_request &);

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
 * Protected methode of http_request struct
 *
 * int set_bloc_event();
 *
 * @returns     void
 * @param       void
 */
    std::string parse_bloc_event();

/**
 * Protected methode of http_request struct
 *
 * int set_bloc_http();
 *
 * @returns     void
 * @param       void
 */
    std::string parse_bloc_http();

/**
 * Protected methode of http_request struct
 *
 * std::string set_worker_processes();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string set_worker_processes();

/**
 * Public methode of http_request struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of http_request struct
 *
 * void set_default_value();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_default_value();

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
 * void send_data_client(int client_socket, std::string& content);
 *
 * @returns void
 * @param   client_socket to send message
 * @param   content & to message to send
 * @throws  server::server_exception
 * */
    void send_data_client(int, std::string);
    /**
 * Private methode of server class
 *
 * add headers befor send
 *
 * std::string set_html_content(std::string path_html_file);
 *
 * @returns std::string ready to send
 * @param   path_html_file to content to send
 * @throws  server::server_exception
 * */
    std::string set_html_content(std::string path_html_file);

/**
 * Private methode of server class
 *
 * set headers befor send
 *
 * std::string set_headers(size_t Content-Length);
 *
 * @returns std::string ready to send
 * @param   Content-Length to add to headers
 * @throws  server::server_exception
 * */
    std::string set_headers(size_t);

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    peg_parser                                                  _peg_parser;
    std::map<std::string, std::string (http_request::*)()>        _map_token_list_action;
    int                                                         _worker_process;
};


#endif //WEBSERV_HTTP_REQUEST_HPP
