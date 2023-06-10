//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_LISTEN_HPP
#define WEBSERVER_LISTEN_HPP

#include "0-Main/Includes/webserv.hpp"

class Listen {

/*>********************************public section**********************************/

public:

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
    explicit Listen(Config& config);

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
/**
 * Public methode of Http class
 *
 * const std::vector<Listen>& getVectorListen() const ;
 *
 * @returns     void
 * @param       event to manage
 * @throw       none
 */
    std::pair<std::string, int> getDataListen() ;


/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    Config&         _config;
    std::string     _ipAddress;
    int             _port;
};


#endif //WEBSERVER_LISTEN_HPP
