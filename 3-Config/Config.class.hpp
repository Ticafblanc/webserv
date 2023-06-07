/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

#include "0-Main/Includes/Headers.hpp"
#include "1-Utils/Includes/Utils.hpp"
#include "2-Log/Log.class.hpp"
#include "4-Http/HttpMessage.class.hpp"
#include "5-Epoll/Epoll.class.hpp"
#include "7-Socket/Socket.class.hpp"
#include "6-PegParser/PegParser.class.hpp"

struct Config;
struct Server;

/*
*==========================================================================================================
*|                                                  bloc location                                         |
*==========================================================================================================
*/

struct Location {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Location.class class
 *
 * Location(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    Location(Config&);

/**
* Destructor of Location.class class
*
* Location.class.class();
*
* @throw   none
**/
    ~Location();

/**
 * Constructor of Location.class class
 *
 * Server(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    Location(const Location&);

/**
* Destructor of Location.class class
*
* Server.class.class();
*
* @throw   none
**/
    Location& operator=(const Location&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of Location.class class
 *
 * std::string parseBlocLocation();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseBlocLocation();

/**
 * Public methode of Location.class class
 *
 * std::string setRoot();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string setRoot();


/**
 * Public methode of Location.class class
 *
 * std::string addIndex();
 *
 * @returns     void
 * @param       name is an std::string contain name of serverSocket to add
 * @throw       bloc_exception if name already exist
 */
    std::string addIndex();

/**
 * Public methode of Location struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of Location class
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
    Config&                                                 _config;
    std::map<std::string, std::string (Location::*)()>     _mapTokenListAction;
    std::string                                                 _root;//path of this location
    std::vector<std::string>                                    _index;// set name of specific index file
};

/*
*==========================================================================================================
*|                                                  listen data                                           |
*==========================================================================================================
*/


struct Listen {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of configServer.class class
 *
 * Listen(Config& config);
 *
 * @param   input is a string reference extract befor;
 * @param   config is config webserv reference
 * @throw   none
 **/
    Listen(Config& config);

/**
* Destructor of Listen.class class
*
* Listen*
* @throw   none
**/
    ~Listen();

/**
 * Constructor of configServer.class class
 *
 * Listen(const Listen & Listen);
 *
 * @param   listenData &
 * @throw   none
 **/
    Listen(const Listen&);

/**
* Destructor of Listen.class class
*
*  Listen& operator=(const Listen& Listen);
*
* @param   listenData&
* @throw   none
**/
    Listen& operator=(const Listen&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of Listen.class class
 *
 * std::string parseListenData();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseListenData();
    std::string parseListenData(std::string in);


/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    Config&         _config;
    std::string     _ipAddress;
    int             _port;
};


/*
*==========================================================================================================
*|                                                  bloc serverSocket                                           |
*==========================================================================================================
*/


struct Server{


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of configServer.class class
 *
 * Server();
 *
 * @param   none
 * @throw   none
 **/
//    Server();

/**
 * Constructor of configServer.class class
 *
 * Server(pegParser& pegParser);
 *
 * @param   configWebserv&
 * @throw   none
 **/
    Server(Config &);

/**
* Destructor of Server.class class
*
* Server*
* @throw   none
**/
    ~Server();

/**
 * Constructor of configServer.class class
 *
 * Server(const Server & Server);
 *
 * @param   blocServer &
 * @throw   none
 **/
    Server(const Server&);

/**
* Destructor of Server.class class
*
*  Server& operator=(const Server& Server);
*
* @param   blocServer&
* @throw   none
**/
    Server& operator=(const Server&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/


/**
 * Public methode of Server.class class
 *
 * std::string parseBlocServer();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseBlocServer();

/**
 * Public methode of Server.class class
 *
 * std::string addMultimapListen();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       bloc_exception if name already exist
 */
    std::string addVectorListen();

/**
 * Public methode of Server.class class
 *
 * std::string addVectorServerName();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addVectorServerName();

/**
 * Public methode of Server.class class
 *
 * std::string setRoot();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string setRoot();


/**
 * Public methode of Server.class class
 *
 * std::string addVectorBlocLocation();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addMapBlocLocation();

/**
 * Public methode of Config struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of Http class
 *
 * void setDefaultValue();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setDefaultValue(std::string addess);

/**
 * Public methode of Http class
 *
 * bool checkEvent(epoll_event &event);
 *
 * @returns     true is a new socket
 * @param       event  check
 * @throw       none
 */
    bool checkEvent(epoll_event &event);

    bool isClient(epoll_event &event);


/**
 * Public methode of Http class
 *
 * void manageEvent(epoll_event &event);
 *
 * @returns     void
 * @param       event to manage
 * @throw       none
 */
    void manageEvent(epoll_event &event);

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    Config&                                             _config;
    Epoll&                                              _epoll;
    std::map<std::string, std::string (Server::*)()>    _mapTokenListAction;
    std::vector<Socket>                                 _vectorServerSocket;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
    std::vector<std::string>                            _vectorServerName;// store all serverSocket name
    std::string                                         _root;//path of repo defaut of serverSocket
    std::map<std::string, Location>                     _mapBlocLocation;



};


/*
*==========================================================================================================
*|                                                  bloc HTTP                                             |
*==========================================================================================================
*/



struct Types {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Types.class class
 *
 * Types(pegParser& pegParser);
 *
 * @param   peg_parser
 * @throw   none
 **/
    Types(std::string pathFile);

/**
* Destructor of Types.class class
*
* Types.class.class();
*
* @throw   none
**/
    ~Types();

/**
 * Copy constructor of Types class
 *
 * Types(const Types &);
 *
 * @param   blocTypes instance to build the serverSocket
 * @throw   none
 **/
    Types(Types&);

/**
 * Operator overload= of Types class
 *
 * Types(const Types &);
 *
 * @param   blocTypes instance const to copy the serverSocket
 * @throw   none
 **/
    Types& operator=(const Types &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of Types.class class
 *
 * std::string parseBlocTypes();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parseBlocTypes();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    PegParser                                                  _peg;
    std::map<std::string, std::string>                         _mapMimeType;
};

struct Code {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Code.class class
 *
 * Code(pegParser& pegParser);
 *
 * @param   peg_parser
 * @throw   none
 **/
    Code();

/**
* Destructor of Code.class class
*
* Code.class.class();
*
* @throw   none
**/
    ~Code();

/**
 * Copy constructor of Code class
 *
 * Code(const Code &);
 *
 * @param   blocCode instance to build the serverSocket
 * @throw   none
 **/
    Code(Code&);

/**
 * Operator overload= of Code class
 *
 * Code(const Code &);
 *
 * @param   blocCode instance const to copy the serverSocket
 * @throw   none
 **/
    Code& operator=(const Code &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of Code.class class
 *
 * std::string parseBlocCode();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    void setStatusCode();

/**
 * Public methode of Code.class class
 *
 * std::string & operator[](int code);
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string & getStatusCode();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::map<int, std::string>                         _mapStatusCode;
    int                                                _statusCode;
};

/*
*==========================================================================================================
*|                                                  bloc HTTP                                             |
*==========================================================================================================
*/



struct Http {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Http.class class
 *
 * Http(pegParser& pegParser);
 *
 * @param   peg_parser
 * @throw   none
 **/
    Http(Config&);

/**
* Destructor of Http.class class
*
* Http.class.class();
*
* @throw   none
**/
    ~Http();

/**
 * Copy constructor of Http class
 *
 * Http(const Http &);
 *
 * @param   blocHttp instance to build the serverSocket
 * @throw   none
 **/
    Http(Http&);

/**
 * Operator overload= of Http class
 *
 * Http(const Http &);
 *
 * @param   blocHttp instance const to copy the serverSocket
 * @throw   none
 **/
    Http& operator=(const Http &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of Http.class class
 *
 * std::string parseBlocHttp();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parseBlocHttp();

/**
 * Public methode of Http.class class
 *
 * std::string addVectorBlocServer();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addVectorBlocServer();

/**
 * Public methode of Config struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of Http class
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
    Config&                                             _config;
    std::map<std::string, std::string (Http::*)()>      _mapTokenListAction;
    std::vector<std::pair<Server, Epoll> >              _vecPairServerEpoll;
    HttpMessage                                         _http;
    int                                                 _status_code;
    Types                                               _types;
    Code                                                _code;
    int                                                 _clientBodyBufferSize;
    int                                                 _clientHeaderBufferSize;
    int                                                 _clientMaxBodySize;
};



/*
*==========================================================================================================
*|                                                  bloc events                                           |
*==========================================================================================================
*/




struct Events {


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Events.class class
 *
 * Events(Config&);
 *
 * @param   peg_parser &
 * @throw   none
 **/
    Events(Config&);

/**
* Destructor of Events.class class
*
*   Events*
* @throw   none
**/
    ~Events();

/**
 * Copy constructor of Events class
 *
 * Events(const Events &);
 *
 * @param   blocEvents instance to build the serverSocket
 * @throw   none
 **/
    Events(Events &);

/**
 * Operator overload= of Events class
 *
 * Events(const Events &);
 *
 * @param   blocEvents instance const to copy the serverSocket
 * @throw   none
 **/
    Events& operator=(const Events &);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of Events class
 *
 * std::string parseBlocEvents() ;
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parseBlocEvents() ;

/**
 * Public methode of Events class
 *
 * std::string setWorkerConnections() ;
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string setWorkerConnections() ;

/**
 * Public methode of Events struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();


/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    Config&                                             _config;
    std::map<std::string, std::string (Events::*)()>    _mapTokenListAction;
    int                                                 _workerConnections;//if not define default 10 else accept >o and < 11
};



/*
*==========================================================================================================
*|                                                  Config Webserv                                        |
*==========================================================================================================
*/



struct Config {

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

//    Config();
/**
 * Constructor of Config class
 *
 * Config(std::string &);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   none
 **/
    Config(std::string &, char ** envp);

/**
* Destructor of Config class
*
* Config @throw   none
**/
    ~Config();

/**
 * Copy constructor of Config class
 *
 * Config(Config &);
 *
 * @param   configWebserv instance to build the serverSocket
 * @throw   none
 **/
    Config(Config &);

/**
 * Operator overload= of Config class
 *
 * Config& operator=(const Config &);
 *
 * @param   configWebserv instance const to copy the serverSocket
 * @throw   none
 **/
    Config& operator=(const Config &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Protected methode of Config struct
 *
 * std::string parseBlocEvent();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocEvent();

/**
 * Protected methode of Config struct
 *
 * std::string parseBlocHttp();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocHttp();


/**
 * Protected methode of Config struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setWorkerProcesses();

/**
 * Public methode of Config struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of Config struct
 *
 * void setDefaultValue();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setDefaultValue();


/**
 * Public methode of Config struct
 *
 * setEnvp(char **envp)
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    char** setEnvp(char **envp);

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    PegParser                                           _pegParser;
    std::map<std::string, std::string (Config::*)()>    _mapTokenListAction;
    int                                                 _workerProcess;
    std::string                                         _pathLog;
    std::string                                         _patherrorLog;
    std::string                                         _pathpidLog;
    Events                                              _Events;
    Http                                                _Http;
    char **                                             _enp;
    Log                                                 _Log;
    Log                                                 _errorLog;
    Log                                                 _pidLog;

    void parseConfig();
};


//        data.setType(SOCK_STREAM);
//        data.setProtocol(0);
//        data.setBacklog(10);
//        data.setAddress(AF_INET, 8081);
//        data.setLevel(SOL_SOCKET);
//        data.setOptionName(SO_REUSEADDR);
//        data.setOptionVal(1);
//        serverSocket serv(data);


#endif //WEBSERV_CONFIG_HPP