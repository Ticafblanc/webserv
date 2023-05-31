/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configWebserv.class.hpp                           :+:      :+:    :+:   */
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
#include "../Include/client.class.hpp"

struct configWebserv;
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
    bloc_location(configWebserv&);

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
 * Public methode of configWebserv struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of blocHttp class
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
    configWebserv&                                             _config;
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
 * listen_data(configWebserv& config, std::string& input);
 *
 * @param   input is a string reference extract befor;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listen_data(configWebserv&, std::string&);
/**
 * Constructor of config_server.class class
 *
 * listen_data(configWebserv& config, std::string& default_input);
 *
 * @param   input is a default string ;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listen_data(configWebserv&, std::string);

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
 * Public methode of configWebserv struct
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

    configWebserv&         _config;
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
 * @param   configWebserv&
 * @throw   none
 **/
    bloc_server(configWebserv&);

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
 * Public methode of configWebserv struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of blocHttp class
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
    configWebserv&                                         _config;
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



struct blocHttp {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of blocHttp.class class
 *
 * blocHttp(peg_parser& peg_parser);
 *
 * @param   peg_parser
 * @throw   none
 **/
    blocHttp(configWebserv&);

/**
* Destructor of blocHttp.class class
*
* blocHttp.class.class();
*
* @throw   none
**/
    ~blocHttp();

/**
 * Copy constructor of blocHttp class
 *
 * blocHttp(const blocHttp &);
 *
 * @param   blocHttp instance to build the server
 * @throw   none
 **/
    blocHttp(blocHttp&);

/**
 * Operator overload= of blocHttp class
 *
 * blocHttp(const blocHttp &);
 *
 * @param   blocHttp instance const to copy the server
 * @throw   none
 **/
    blocHttp& operator=(const blocHttp &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of blocHttp.class class
 *
 * std::string parse_blocHttp();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parse_blocHttp();

/**
 * Public methode of blocHttp.class class
 *
 * std::string add_vector_bloc_server();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string add_vector_bloc_server();

/**
 * Public methode of configWebserv struct
 *
 * void set_map_token();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void set_map_token();

/**
 * Public methode of blocHttp class
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
    configWebserv&                                          _config;
    std::map<std::string, std::string (blocHttp::*)()>     _mapTokenListAction;
    std::vector<blocServer>                                 _vectorBlocServer;//no default value
    int                                                     _selectBlocServer;
    std::map<int, int>                                      _mapClientSocket;
    int                                                     _numberMaxEvents;
};



/*
*==========================================================================================================
*|                                                  bloc events                                           |
*==========================================================================================================
*/




struct blocEvents {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of blocEvents.class class
 *
 * blocEvents(peg_parser& peg_parser);
 *
 * @param   peg_parser &
 * @throw   none
 **/
    blocEvents(configWebserv&);

/**
* Destructor of blocEvents.class class
*
*   ~blocEvents();
*
* @throw   none
**/
    ~blocEvents();

/**
 * Copy constructor of blocEvents class
 *
 * blocEvents(const blocEvents &);
 *
 * @param   blocEvents instance to build the server
 * @throw   none
 **/
    blocEvents(blocEvents &);

/**
 * Operator overload= of blocEvents class
 *
 * blocEvents(const blocEvents &);
 *
 * @param   blocEvents instance const to copy the server
 * @throw   none
 **/
    blocEvents& operator=(const blocEvents &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of blocEvents class
 *
 * std::string parseBlocEvents() ;
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parseBlocEvents() ;

/**
 * Public methode of blocEvents class
 *
 * std::string setWorkerConnections() ;
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string setWorkerConnections() ;

/**
 * Public methode of blocEvents struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of blocEvents class
 *
 * void setDefaultValue();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setDefaultValue();



/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    configWebserv&                                          _config;
    std::map<std::string, std::string (blocEvents::*)()>    _mapTokenListAction;
    int                                                     _workerConnections;//if not define default 10 else accept >o and < 11
};



/*
*==========================================================================================================
*|                                                  Config Webserv                                        |
*==========================================================================================================
*/



struct configWebserv {

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of configWebserv class
 *
 * configWebserv();
 *
 * @param   void
 * @throw   none
 **/
    configWebserv();

/**
 * Constructor of configWebserv class
 *
 * configWebserv(std::string &);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   none
 **/
    configWebserv(std::string &);

/**
* Destructor of configWebserv class
*
* ~configWebserv();
*
* @throw   none
**/
    ~configWebserv();

/**
 * Copy constructor of configWebserv class
 *
 * configWebserv(configWebserv &);
 *
 * @param   configWebserv instance to build the server
 * @throw   none
 **/
    configWebserv(configWebserv &);

/**
 * Operator overload= of configWebserv class
 *
 * configWebserv& operator=(const configWebserv &);
 *
 * @param   configWebserv instance const to copy the server
 * @throw   none
 **/
    configWebserv& operator=(const configWebserv &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Protected methode of configWebserv struct
 *
 * std::string parseBlocEvent();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocEvent();

/**
 * Protected methode of configWebserv struct
 *
 * std::string parseBlocHttp();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocHttp();

/**
 * Protected methode of configWebserv struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setWorkerProcesses();

/**
 * Public methode of configWebserv struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of configWebserv struct
 *
 * void setDefaultValue();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setDefaultValue();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    pegParser                                                  _pegParser;
    std::map<std::string, std::string (configWebserv::*)()>     _mapTokenListAction;
    int                                                         _workerProcess;
    blocEvents                                                 _blocEvents;//required
    blocHttp                                                   _blocHttp;//if not set as default
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
