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

#pragma once

#ifndef WEBSERV_CONFIG_WEBSERV_HPP
#define WEBSERV_CONFIG_WEBSERV_HPP

#include "0-Main/Includes/webserv.hpp"



struct Config;
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
    blocLocation(Config&);

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
 * Server(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    blocLocation(const blocLocation&);

/**
* Destructor of blocLocation.class class
*
* Server.class.class();
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
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseBlocLocation();

/**
 * Public methode of blocLocation.class class
 *
 * std::string setRoot();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
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
 * @param       name is an std::string contain name of serverSocket to add
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
    Config&                                             _config;
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
 * listenData(3-Config.class& config, std::string& input);
 *
 * @param   input is a string reference extract befor;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listenData(Config&, std::string&);
/**
 * Constructor of configServer.class class
 *
 * listenData(3-Config.class& config, std::string& default_input);
 *
 * @param   input is a default string ;
 * @param   config is config webserv reference
 * @throw   none
 **/
    listenData(Config&, std::string);

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
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseListenData();


/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    Config&          _config;
    std::stringstream       _input;
    std::string             _ipAddress;
    int                     _port;
    Socket           _socket;
};


/*
*==========================================================================================================
*|                                                  bloc serverSocket                                           |
*==========================================================================================================
*/






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
 * blocHttp(6-PegParser& 6-PegParser);
 *
 * @param   peg_parser
 * @throw   none
 **/
    blocHttp(Config&);

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
 * @param   blocHttp instance to build the serverSocket
 * @throw   none
 **/
    blocHttp(blocHttp&);

/**
 * Operator overload= of blocHttp class
 *
 * blocHttp(const blocHttp &);
 *
 * @param   blocHttp instance const to copy the serverSocket
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
 * Public methode of 3-Config.class struct
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
    Config&                                          _config;
    std::map<std::string, std::string (blocHttp::*)()>     _mapTokenListAction;
    std::map<const int, blocServer>                         _mapBlocServer;//no default value
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
 * blocEvents(3-Config.class&);
 *
 * @param   peg_parser &
 * @throw   none
 **/
    blocEvents(Config&);

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
 * @param   blocEvents instance to build the serverSocket
 * @throw   none
 **/
    blocEvents(blocEvents &);

/**
 * Operator overload= of blocEvents class
 *
 * blocEvents(const blocEvents &);
 *
 * @param   blocEvents instance const to copy the serverSocket
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
    Config&                                          _config;
    std::map<std::string, std::string (blocEvents::*)()>    _mapTokenListAction;
    int                                                     _workerConnections;//if not define default 10 else accept >o and < 11
};



/*
*==========================================================================================================
*|                                                  3-Config.class Webserv                                        |
*==========================================================================================================
*/





//        data.setType(SOCK_STREAM);
//        data.setProtocol(0);
//        data.setBacklog(10);
//        data.setAddress(AF_INET, 8081);
//        data.setLevel(SOL_SOCKET);
//        data.setOptionName(SO_REUSEADDR);
//        data.setOptionVal(1);
//        serverSocket serv(data);


#endif //WEBSERV_CONFIG_WEBSERV_HPP
