//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_HTTPCLASS_HPP
#define WEBSERVER_HTTPCLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/1-Config/Includes/Server.class.hpp>

class Http {

/*>********************************public section**********************************/

public:


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
    explicit Http(Config&);

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
    Http(const Http&);

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
    std::string parseBlocHttp(std::string &);

/*>*******************************private section**********************************/

private:

/**
 * Public methode of Http.class class
 *
 * std::string addVectorBlocServer();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string addVectorBlocServer(std::string &);

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


/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    Config&                                                             _config;
    std::map<std::string, std::string (Http::*)(std::string &)>         _mapTokenListAction;
};
#endif //WEBSERVER_HTTPCLASS_HPP
