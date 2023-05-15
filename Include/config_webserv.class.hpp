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

#include <Include/header.hpp>

/*
*==========================================================================================================
*|                                                  bloc location                                         |
*==========================================================================================================
*/

struct bloc_location {

/*>********************************public section**********************************/

public:

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
    bloc_location(std::stringstream & webserv_config_file);

/**
* Destructor of bloc_location.class class
*
* bloc_location.class.class();
*
* @throw   none
**/
    ~bloc_location();

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of bloc_location.class class
 *
 * std::vector<std::string> &get_vector_location_name() const;
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::vector<std::string> &get_vector_location_name() const;


/**
 * Public methode of bloc_location.class class
 *
 * void set_vector_location_name(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       bloc_exception if name already exist
 */
    void add_vector_location_name(std::string &);

/**
 * Public methode of bloc_location.class class
 *
 * std::string& get_ip_address();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       bloc_exception out of rang
 */
    std::vector<std::string>  &get_vector_sock_address() const;


/**
 * Public methode of bloc_location.class class
 *
 * void add_vector_sock_address(std::string ip_address, const int port);
 *
 * @returns     void
 * @param       ip_adress is a std::string with ip_address
 *              port is an int with port to add
 * @throw       bloc_exception if ip/port already exist in _webserv instance
 */
    void add_vector_sock_address(std::string, const int );

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::string                         _root;//path of this location
    std::vector<std::string>            _index;// set name of specific index file
};



/*
*==========================================================================================================
*|                                                  bloc server                                           |
*==========================================================================================================
*/


struct bloc_server {

/*>********************************public section**********************************/

public:

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
    bloc_server(std::stringstream & webserv_config_file);

/**
* Destructor of bloc_server.class class
*
* bloc_server.class.class();
*
* @throw   none
**/
    ~bloc_server();

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
    std::vector<std::string> &get_vector_server_name() const;


/**
 * Public methode of bloc_server.class class
 *
 * void set_vector_server_name(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       bloc_exception if name already exist
 */
    void add_vector_server_name(std::string &);

/**
 * Public methode of bloc_server.class class
 *
 * std::string& get_ip_address();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       bloc_exception out of rang
 */
    std::vector<std::string>  &get_vector_sock_address() const;


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
    void add_vector_sock_address(std::string, const int );

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::multimap<std::string, int>         _vector_listen;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
    std::vector<std::string>                _vector_server_name;// store all server name
    std::string                             _root;//path of repo defaut of server
    std::vector<bloc_location>              _vector_sock_address;
};



/*
*==========================================================================================================
*|                                                  bloc HTTP                                             |
*==========================================================================================================
*/



struct bloc_http {

/*>********************************public section**********************************/

public:

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
    bloc_http(std::stringstream & webserv_config_file);

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
    void set_vector_bloc_server();

/**
 * Public methode of bloc_http.class class
 *
 * std::vector<bloc_server> & get_vector_bloc_server()const;
 *
 * @returns     std::vector<bloc_server> contain tble of bloc_sevr class
 * @param       void
 * @throw       none
 */
    std::vector<bloc_server> & get_vector_bloc_server() const;

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::vector<bloc_server>        _vector_bloc_server;//no default value
};


/*
*==========================================================================================================
*|                                                  bloc events                                           |
*==========================================================================================================
*/

struct bloc_events {

/*>********************************public section**********************************/

public:

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
    bloc_events(std::stringstream & webserv_config_fgile);

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
 * std::string set_work_connection(int work_connection) ;
 *
 * @returns     string contain error message
 * @param       work_connection is number of pending connections avaible
 * @throw       none
 */
    std::string set_work_connection(int work_connection) ;

/**
 * Public methode of bloc_events.class class
 *
 * int &get_work_connection() const;
 *
 * @returns     int with the maximum number of pending connections
 * @param       void
 * @throw       none
 */
    int &get_work_connection() const;


/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    int _work_connection;//if not define default 10 else accept >o and < 11
};



/*
*==========================================================================================================
*|                                                  Config Webserv                                        |
*==========================================================================================================
*/



struct config_webserv{

/*>*******************************public section*********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_webserv class
 *
 * config_webserv(std::string path_config_file);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   config_webserv::config_exception
 **/
    config_webserv(std::string & path_config_file);

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
*|                                  Element access                                 |
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
    void set_bloc_event();

/**
 * Protected methode of config_webserv class
 *
 * int get_bloc_events();
 *
 * @returns     bloc_events contain the events config
 * @param       void
 */
    bloc_events & get_bloc_event() const;

/**
 * Protected methode of config_webserv class
 *
 * int set_bloc_http();
 *
 * @returns     void
 * @param       void
 */
    void set_bloc_http();

/**
 * Protected methode of config_webserv class
 *
 * int get_bloc_http();
 *
 * @returns     bloc_http contain the http config
 * @param       void
 */
    bloc_http & get_bloc_http() const;

/*>*******************************private section*********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    std::stringstream   _webserv_config_file;
    const bloc_events   _bloc_events;//required
    const bloc_http     _bloc_http;//if not set as default
};

#endif //WEBSERV_CONFIG_WEBSERV_HPP