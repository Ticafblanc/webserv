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
    bloc_location(peg_parser&);

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
    bloc_location(const bloc_location &);

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

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    peg_parser&                         _peg_parser;
    std::string                         _root;//path of this location
    std::vector<std::string>            _index;// set name of specific index file
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
 * bloc_server(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    bloc_server(peg_parser&);

/**
* Destructor of bloc_server.class class
*
* bloc_server.class.class();
*
* @throw   none
**/
    ~bloc_server();

/**
 * Constructor of config_server.class class
 *
 * bloc_server(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    bloc_server(const bloc_server &);

/**
* Destructor of bloc_server.class class
*
* bloc_server.class.class();
*
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
 * std::vector<std::string> &get_vector_server_name() const;
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string parse_bloc_server();

/**
 * Public methode of bloc_server.class class
 *
 * void set_vector_server_name(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       bloc_exception if name already exist
 */
    std::string add_multimap_listen();

/**
 * Public methode of bloc_server.class class
 *
 * void set_vector_server_name(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       bloc_exception if name already exist
 */
    std::string add_vector_server_name();

/**
 * Public methode of bloc_server.class class
 *
 * std::string& get_ip_address();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       bloc_exception out of rang
 */
    std::string set_root();


/**
 * Public methode of bloc_server.class class
 *
 * void add_vector_sock_address(std::string ip_address, const int port);
 *
 * @returns     void
 * @param       ip_adress is a std::string with ip_address
 *              port is an int with port to add
 * @throw       bloc_exception if ip/port already exist in _webserv instance
 */
    std::string add_vector_bloc_location();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    peg_parser&                             _peg_parser;
    std::multimap<std::string, int>         _multimap_listen;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
    std::vector<std::string>                _vector_server_name;// store all server name
    std::string                             _root;//path of repo defaut of server
    std::vector<bloc_location>              _vector_bloc_location;
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
 * bloc_http.class(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    bloc_http(peg_parser&);

/**
* Destructor of bloc_http.class class
*
* bloc_http.class.class();
*
* @throw   none
**/
    ~bloc_http();

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of bloc_http.class class
 *
 * void set_vector_bloc_server();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    std::string parse_bloc_http();

/**
 * Public methode of bloc_http.class class
 *
 * void set_vector_bloc_server();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    std::string add_vector_bloc_server();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    peg_parser&                     _peg_parser;
    std::vector<bloc_server>        _vector_bloc_server;//no default value
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
 * bloc_events.class();
 *
 * @param   void
 * @throw   none
 **/
    bloc_events(peg_parser&);

/**
* Destructor of bloc_events.class class
*
* bloc_events.class.class();
*
* @throw   none
**/
    ~bloc_events();

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of bloc_events.class class
 *
 * std::string set_work_connection(std::stringstream & string_stream) ;
 *
 * @returns     string contain error message
 * @param       work_connection is number of pending connections avaible
 * @throw       none
 */
    std::string parse_bloc_events() ;

/**
 * Public methode of bloc_events.class class
 *
 * std::string set_work_connection(std::stringstream & string_stream) ;
 *
 * @returns     string contain error message
 * @param       work_connection is number of pending connections avaible
 * @throw       none
 */
    std::string set_work_connection() ;

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    peg_parser&     _peg_parser;
    int             _work_connection;//if not define default 10 else accept >o and < 11
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
 * config_webserv(std::string & path_config_file);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
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

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Protected methode of config_webserv class
 *
 * int set_bloc_event();
 *
 * @returns     void
 * @param       void
 */
    std::string parse_bloc_event();

/**
 * Protected methode of config_webserv class
 *
 * int set_bloc_http();
 *
 * @returns     void
 * @param       void
 */
    std::string parse_bloc_http();
    std::string set_worker_processes();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    peg_parser          _peg_parser;
    int                 _work_process;
    bloc_events         _bloc_events;//required
    bloc_http           _bloc_http;//if not set as default
};

#endif //WEBSERV_CONFIG_WEBSERV_HPP
