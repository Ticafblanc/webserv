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
#include "../Include/client.class.hpp"

struct configWebserv;
/*
*==========================================================================================================
*|                                                  bloc location                                         |
*==========================================================================================================
*/

struct blocLocation {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of blocLocation.class class
 *
 * blocLocation(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    blocLocation(configWebserv&);

/**
* Destructor of blocLocation.class class
*
* blocLocation.class.class();
*
* @throw   none
**/
    ~blocLocation();

/**
 * Constructor of blocLocation.class class
 *
 * blocServer(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    blocLocation(const blocLocation&);

/**
* Destructor of blocLocation.class class
*
* blocServer.class.class();
*
* @throw   none
**/
    blocLocation& operator=(const blocLocation&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of blocLocation.class class
 *
 * std::string parseBlocLocation();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string parseBlocLocation();

/**
 * Public methode of blocLocation.class class
 *
 * std::string setRoot();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string setRoot();


/**
 * Public methode of blocLocation.class class
 *
 * std::string addIndex();
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       bloc_exception if name already exist
 */
    std::string addIndex();

/**
 * Public methode of blocLocation struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of blocLocation class
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
    configWebserv&                                             _config;
    std::map<std::string, std::string (blocLocation::*)()>     _mapTokenListAction;
    std::string                                                 _root;//path of this location
    std::vector<std::string>                                    _index;// set name of specific index file
};

/*
*==========================================================================================================
*|                                                  listen data                                           |
*==========================================================================================================
*/


struct listenData {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of configServer.class class
 *
 * listenData(configWebserv& config, std::string& input);
 *
 * @param   input is a string reference extract befor;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listenData(configWebserv&, std::string&);
/**
 * Constructor of configServer.class class
 *
 * listenData(configWebserv& config, std::string& default_input);
 *
 * @param   input is a default string ;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listenData(configWebserv&, std::string);

/**
* Destructor of listenData.class class
*
* ~listenData();
*
* @throw   none
**/
    ~listenData();

/**
 * Constructor of configServer.class class
 *
 * listenData(const listenData & listenData);
 *
 * @param   listenData &
 * @throw   none
 **/
    listenData(const listenData&);

/**
* Destructor of listenData.class class
*
*  listenData& operator=(const listenData& listenData);
*
* @param   listenData&
* @throw   none
**/
    listenData& operator=(const listenData&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of listenData.class class
 *
 * std::string parseListenData();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string parseListenData();

/**
 * Public methode of configWebserv struct
 *
 * void set_sockaddr_in(std::string ip_address, int port);
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setSockaddrIn();

/**
 * Private methode of listenData class
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
    std::string setSocket();

/**
 * Private methode of listenData class
 *
 * set the option of server socket already created
 *
 * std::string setSocketOption();
 *
 * @returns std::string error or empty if its ok
 * @param   void
 * @throws  none
 *
 * @see https://linux.die.net/man/3/setsockopt
 * */
    std::string setSocketOption();

/**
 * Private methode of listenData class
 *
 * associate an IP address and a port number with a socket already created
 *
 * std::string setBind();
 *
 * @returns std::string error or empty if its ok
 * @param   void
 * @throws  none
 *
 * @see https://man7.org/linux/man-pages/man2/bind.2.html
 * */
    std::string setBind();

/**
 * Private methode of listen data class
 *
 * set the listen option so the number of possible connexion
 *
 * std::string setListen();
 *
 * @returns std::string error or empty if its ok
 * @param   void
 * @throws  none
 *
 * @see https://man7.org/linux/man-pages/man2/listen.2.html
 * */
    std::string setListen();

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
    std::string setSocketFlag();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    configWebserv&          _config;
    std::stringstream       _input;
    std::string             _ipAddress;
    int                     _port;
    int                     _serverSocket;
    sockaddr_in             _sockaddress;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
};


/*
*==========================================================================================================
*|                                                  bloc server                                           |
*==========================================================================================================
*/


struct blocServer {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of configServer.class class
 *
 * blocServer(pegParser& pegParser);
 *
 * @param   configWebserv&
 * @throw   none
 **/
    blocServer(configWebserv&);

/**
* Destructor of blocServer.class class
*
* ~blocServer();
*
* @throw   none
**/
    ~blocServer();

/**
 * Constructor of configServer.class class
 *
 * blocServer(const blocServer & blocServer);
 *
 * @param   blocServer &
 * @throw   none
 **/
    blocServer(const blocServer&);

/**
* Destructor of blocServer.class class
*
*  blocServer& operator=(const blocServer& blocServer);
*
* @param   blocServer&
* @throw   none
**/
    blocServer& operator=(const blocServer&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of blocServer.class class
 *
 * std::string parseBlocServer();
 *
 * @returns     std::vector<std::string>& contain all names of server
 * @param       void
 * @throw       none
 */
    std::string parseBlocServer();

/**
 * Public methode of blocServer.class class
 *
 * std::string addMultimapListen();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       bloc_exception if name already exist
 */
    std::string addVectorListen();

/**
 * Public methode of blocServer.class class
 *
 * std::string addVectorServerName();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addVectorServerName();

/**
 * Public methode of blocServer.class class
 *
 * std::string setRoot();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string setRoot();


/**
 * Public methode of blocServer.class class
 *
 * std::string addVectorBlocLocation();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addMapBlocLocation();

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
 * Public methode of blocHttp class
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
    std::map<std::string, std::string (blocServer::*)()>   _mapTokenListAction;
    std::vector<listenData>                                _vectorListen;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
    std::vector<std::string>                                _vectorServerName;// store all server name
    std::string                                             _root;//path of repo defaut of server
    std::map<std::string, blocLocation>                    _mapBlocLocation;
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
 * blocHttp(pegParser& pegParser);
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
 * std::string parseBlocHttp();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parseBlocHttp();

/**
 * Public methode of blocHttp.class class
 *
 * std::string addVectorBlocServer();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addVectorBlocServer();

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
 * Public methode of blocHttp class
 *
 * void setDefaultValue();
 *
 * std::string ip =  "127.0.0.1";
 * int port = 8081;
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
 * blocEvents(configWebserv&);
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
    std::map<std::string, std::string (configWebserv::*)()>    _mapTokenListAction;
    int                                                        _workerProcess;
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
