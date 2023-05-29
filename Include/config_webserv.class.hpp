/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_webserv.class.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONFIG_WEBSERV_HPP
#define WEBSERV_CONFIG_WEBSERV_HPP

#include "../Include/header.hpp"
#include "../Include/peg_parser.class.hpp"

struct config_webserv;
/*
*==========================================================================================================
*|                                                  bloc location                                         |
*==========================================================================================================
*/

struct bloc_location {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_location.class class
 *
 * bloc_location(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    bloc_location(config_webserv&);

/**
* Destructor of bloc_location.class class
*
* bloc_location.class.class();
*
* @throw   none
**/
    ~bloc_location();

/**
 * Constructor of config_server.class class
 *
 * bloc_server(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    bloc_location(const bloc_location&);

/**
* Destructor of bloc_server.class class
*
* bloc_server.class.class();
*
* @throw   none
**/
    bloc_location& operator=(const bloc_location&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of bloc_server.class class
 *
 * std::vector<std::string> &get_vector_server_name() const;
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string parse_bloc_location();

/**
 * Public methode of bloc_location.class class
 *
 * std::vector<std::string> &get_vector_location_name() const;
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string set_root();


/**
 * Public methode of bloc_location.class class
 *
 * void set_vector_location_name(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       bloc_exception if name already exist
 */
    std::string add_index();

/**
 * Public methode of config_webserv struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of bloc_http class
 *
 * void set_default_value();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_default_value();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    config_webserv&                                             _config;
    std::map<std::string, std::string (bloc_location::*)()>     _map_token_list_action;
    std::string                                                 _root;//path of this location
    std::vector<std::string>                                    _index;// set name of specific index file
};

/*
*==========================================================================================================
*|                                                  listen data                                           |
*==========================================================================================================
*/


struct listen_data {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_server.class class
 *
 * listen_data(config_webserv& config, std::string& input);
 *
 * @param   input is a string reference extract befor;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listen_data(config_webserv&, std::string&);
/**
 * Constructor of config_server.class class
 *
 * listen_data(config_webserv& config, std::string& default_input);
 *
 * @param   input is a default string ;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listen_data(config_webserv&, std::string);

/**
* Destructor of listen_data.class class
*
* ~listen_data();
*
* @throw   none
**/
    ~listen_data();

/**
 * Constructor of config_server.class class
 *
 * listen_data(const listen_data & listen_data);
 *
 * @param   listen_data &
 * @throw   none
 **/
    listen_data(const listen_data&);

/**
* Destructor of listen_data.class class
*
*  listen_data& operator=(const listen_data& listen_data);
*
* @param   listen_data&
* @throw   none
**/
    listen_data& operator=(const listen_data&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of listen_data.class class
 *
 * std::string parse_listen_data();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string parse_listen_data();

/**
 * Public methode of config_webserv struct
 *
 * void set_sockaddr_in(std::string ip_address, int port);
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_sockaddr_in();

/**
 * Private methode of listen_data class
 *
 * create a new socket with fonction socket
 *
 * @see https://man7.org/linux/man-pages/man2/socket.2.html
 *
 * int socket(int domain, int protocol);
 *
 * tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = socket(AF_INET, SOCK_RAW, protocol);
 *
 * nginx work only on tcp protocol !!
 *
 * std::string set_socket();
 *
 * @returns std::string error or empty if its ok
 * @param   void
 * @throws  none
 **/
    std::string set_socket();

/**
 * Private methode of listen_data class
 *
 * set the option of server socket already created
 *
 * std::string set_socket_option();
 *
 * @returns std::string error or empty if its ok
 * @param   void
 * @throws  none
 *
 * @see https://linux.die.net/man/3/setsockopt
 * */
    std::string set_socket_option();

/**
 * Private methode of listen_data class
 *
 * associate an IP address and a port number with a socket already created
 *
 * std::string set_bind();
 *
 * @returns std::string error or empty if its ok
 * @param   void
 * @throws  none
 *
 * @see https://man7.org/linux/man-pages/man2/bind.2.html
 * */
    std::string set_bind();

/**
 * Private methode of listen data class
 *
 * set the listen option so the number of possible connexion
 *
 * std::string set_listen();
 *
 * @returns std::string error or empty if its ok
 * @param   void
 * @throws  none
 *
 * @see https://man7.org/linux/man-pages/man2/listen.2.html
 * */
    std::string set_listen();

/**
 * Private methode of listen class
 *
 * accessor of socket to get or set the flag option
 * set fnctl like subject fcntl(fd, F_SETFL, O_NONBLOCK)
 * don't show the actual flag in socket and force to change it to non blocking
 *
 * std::string accessor_server();
 *
 * @returns std::string error or empty if its ok
 * @param  void
 * @throws  none
 * */
    std::string set_socket_flag();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    config_webserv&         _config;
    std::stringstream       _input;
    std::string             _ip_address;
    int                     _port;
    int                     _server_socket;
    sockaddr_in             _sockaddress;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
};


/*
*==========================================================================================================
*|                                                  bloc server                                           |
*==========================================================================================================
*/


struct bloc_server {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_server.class class
 *
 * bloc_server(peg_parser& peg_parser);
 *
 * @param   config_webserv&
 * @throw   none
 **/
    bloc_server(config_webserv&);

/**
* Destructor of bloc_server.class class
*
* ~bloc_server();
*
* @throw   none
**/
    ~bloc_server();

/**
 * Constructor of config_server.class class
 *
 * bloc_server(const bloc_server & bloc_server);
 *
 * @param   bloc_server &
 * @throw   none
 **/
    bloc_server(const bloc_server&);

/**
* Destructor of bloc_server.class class
*
*  bloc_server& operator=(const bloc_server& bloc_server);
*
* @param   bloc_server&
* @throw   none
**/
    bloc_server& operator=(const bloc_server&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of bloc_server.class class
 *
 * std::string parse_bloc_server();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string parse_bloc_server();

/**
 * Public methode of bloc_server.class class
 *
 * std::string add_multimap_listen();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       bloc_exception if name already exist
 */
    std::string add_vector_listen();

/**
 * Public methode of bloc_server.class class
 *
 * std::string add_vector_server_name();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string add_vector_server_name();

/**
 * Public methode of bloc_server.class class
 *
 * std::string set_root();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string set_root();


/**
 * Public methode of bloc_server.class class
 *
 * std::string add_vector_bloc_location();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string add_map_bloc_location();

/**
 * Public methode of config_webserv struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of bloc_http class
 *
 * void set_default_value();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_default_value();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    config_webserv&                                         _config;
    std::map<std::string, std::string (bloc_server::*)()>   _map_token_list_action;
    std::vector<listen_data>                                _vector_listen;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
    std::vector<std::string>                                _vector_server_name;// store all server name
    std::string                                             _root;//path of repo defaut of server
    std::map<std::string, bloc_location>                    _map_bloc_location;
};



/*
*==========================================================================================================
*|                                                  bloc HTTP                                             |
*==========================================================================================================
*/



struct bloc_http {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of bloc_http.class class
 *
 * bloc_http(peg_parser& peg_parser);
 *
 * @param   peg_parser
 * @throw   none
 **/
    bloc_http(config_webserv&);

/**
* Destructor of bloc_http.class class
*
* bloc_http.class.class();
*
* @throw   none
**/
    ~bloc_http();

/**
 * Copy constructor of bloc_http class
 *
 * bloc_http(const bloc_http &);
 *
 * @param   bloc_http instance to build the server
 * @throw   none
 **/
    bloc_http(bloc_http&);

/**
 * Operator overload= of bloc_http class
 *
 * bloc_http(const bloc_http &);
 *
 * @param   bloc_http instance const to copy the server
 * @throw   none
 **/
    bloc_http& operator=(const bloc_http &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of bloc_http.class class
 *
 * std::string parse_bloc_http();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parse_bloc_http();

/**
 * Public methode of bloc_http.class class
 *
 * std::string add_vector_bloc_server();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string add_vector_bloc_server();

/**
 * Public methode of config_webserv struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of bloc_http class
 *
 * void set_default_value();
 *
 * std::string ip =  "127.0.0.1";
 * int port = 8081;
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_default_value();



/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    config_webserv&                                         _config;
    std::map<std::string, std::string (bloc_http::*)()>     _map_token_list_action;
    std::vector<bloc_server>                                _vector_bloc_server;//no default value
    int                                                     _select_bloc_server;
    std::map<int, int>                                      _map_client_socket;
    int                                                     _number_max_events;
};



/*
*==========================================================================================================
*|                                                  bloc events                                           |
*==========================================================================================================
*/




struct bloc_events {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of bloc_events.class class
 *
 * bloc_events(peg_parser& peg_parser);
 *
 * @param   peg_parser &
 * @throw   none
 **/
    bloc_events(config_webserv&);

/**
* Destructor of bloc_events.class class
*
*   ~bloc_events();
*
* @throw   none
**/
    ~bloc_events();

/**
 * Copy constructor of bloc_events class
 *
 * bloc_events(const bloc_events &);
 *
 * @param   bloc_events instance to build the server
 * @throw   none
 **/
    bloc_events(bloc_events &);

/**
 * Operator overload= of bloc_events class
 *
 * bloc_events(const bloc_events &);
 *
 * @param   bloc_events instance const to copy the server
 * @throw   none
 **/
    bloc_events& operator=(const bloc_events &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of bloc_events class
 *
 * std::string set_work_connection() ;
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parse_bloc_events() ;

/**
 * Public methode of bloc_events class
 *
 * std::string set_work_connection() ;
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string set_worker_connections() ;

/**
 * Public methode of bloc_events struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of bloc_events class
 *
 * void set_default_value();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_default_value();



/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    config_webserv&                                         _config;
    std::map<std::string, std::string (bloc_events::*)()>   _map_token_list_action;
    int                                                     _worker_connections;//if not define default 10 else accept >o and < 11
};



/*
*==========================================================================================================
*|                                                  Config Webserv                                        |
*==========================================================================================================
*/



struct config_webserv {

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_webserv class
 *
 * config_webserv();
 *
 * @param   void
 * @throw   none
 **/
    config_webserv();

/**
 * Constructor of config_webserv class
 *
 * config_webserv(std::string & path_config_file);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   none
 **/
    config_webserv(std::string &);

/**
* Destructor of config_webserv class
*
* ~config_webserv();
*
* @throw   none
**/
    ~config_webserv();

/**
 * Copy constructor of config_webserv class
 *
 * config_webserv(const config_webserv &);
 *
 * @param   config_webserv instance to build the server
 * @throw   none
 **/
    config_webserv(config_webserv &);

/**
 * Operator overload= of config_webserv class
 *
 * config_webserv(const config_webserv &);
 *
 * @param   config_webserv instance const to copy the server
 * @throw   none
 **/
    config_webserv& operator=(const config_webserv &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Protected methode of config_webserv struct
 *
 * int set_bloc_event();
 *
 * @returns     void
 * @param       void
 */
    std::string parse_bloc_event();

/**
 * Protected methode of config_webserv struct
 *
 * int set_bloc_http();
 *
 * @returns     void
 * @param       void
 */
    std::string parse_bloc_http();

/**
 * Protected methode of config_webserv struct
 *
 * std::string set_worker_processes();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string set_worker_processes();

/**
 * Public methode of config_webserv struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of config_webserv struct
 *
 * void set_default_value();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_default_value();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    peg_parser                                                  _peg_parser;
    std::map<std::string, std::string (config_webserv::*)()>    _map_token_list_action;
    int                                                         _worker_process;
    bloc_events                                                 _bloc_events;//required
    bloc_http                                                   _bloc_http;//if not set as default
};


//        data.setType(SOCK_STREAM);
//        data.setProtocol(0);
//        data.setBacklog(10);
//        data.setAddress(AF_INET, 8081);
//        data.setLevel(SOL_SOCKET);
//        data.setOptionName(SO_REUSEADDR);
//        data.setOptionVal(1);
//        server serv(data);


#endif //WEBSERV_CONFIG_WEBSERV_HPP
