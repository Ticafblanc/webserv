//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_SERVER_CLASS_HPP
#define WEBSERVER_SERVER_CLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/1-Config/Includes/Location.class.hpp>
#include <Source_Code/1-Config/Includes/Listen.class.hpp>

class Server {

/*>*******************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of configServer.class class
 *
 * Server.class(pegParser& pegParser);
 *
 * @param   configWebserv&
 * @throw   none
 **/
    explicit Server(ConfigBase &);

/**
* Destructor of Server.class.class class
*
* Server.class*
* @throw   none
**/
    ~Server();

/**
 * Constructor of configServer.class class
 *
 * Server.class(const Server.class & Server.class);
 *
 * @param   blocServer &
 * @throw   none
 **/
    Server(const Server&);

/**
* Destructor of Server.class.class class
*
*  Server.class& operator=(const Server.class& Server.class);
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
 * Public methode of Server.class.class class
 *
 * std::string parseBlocServer();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseBlocServer(std::string &);

/**
 * Public methode of Server.class.class class
 *
 * std::string addMultimapListen();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       bloc_exception if name already exist
 */
    std::string addVectorListen(std::string &);

/**
 * Public methode of Server.class.class class
 *
 * std::string addVectorServerName();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addVectorServerName(std::string &);

/**
 * Public methode of Server.class.class class
 *
 * std::string addVectorServerName();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addIndex(std::string &);

/**
 * Public methode of Server.class.class class
 *
 * std::string setRoot();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string setRoot(std::string &);


/**
 * Public methode of Server.class.class class
 *
 * std::string addVectorBlocLocation();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string parseBlocLocation(std::string &);

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
 * void clearToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void clearToken();

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    Config                                                          _config;
    std::map<std::string, std::string (Server::*)(std::string &)>   _mapTokenListAction;
};


#endif //WEBSERVER_SERVER_CLASS_HPP
