//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#ifndef WEBSERVER_SERVER_HPP
#define WEBSERVER_SERVER_HPP

#include "0-Main/Includes/webserv.hpp"


class Server : public Epoll {

    /*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

    Server();

/**
 * Constructor of configServer.class class
 *
 * Server(6-PegParser& 6-PegParser);
 *
 * @param   configWebserv&
 * @throw   none
 **/
    Server(Config&);

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

    virtual bool EpollWait(int  timeOut);
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
    std::map<std::string, std::string (Server::*)()>   _mapTokenListAction;
    std::vector<listenData>                                _vectorListen;// link each ipaddress valid !! with port the port is required not th ip address if not ip addres or 0.0.0.0 define ip to INADDR_ANY
    std::vector<std::string>                                _vectorServerName;// store all serverSocket name
    std::string                                             _root;//path of repo defaut of serverSocket
    std::map<std::string, blocLocation>                    _mapBlocLocation;
    int                                                        _epollInstance;

};


#endif //WEBSERVER_SERVER_HPP
