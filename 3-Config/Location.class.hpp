//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_LOCATION_CLASS_HPP
#define WEBSERVER_LOCATION_CLASS_HPP

#include "0-Main/Includes/webserv.hpp"

class Location {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Location.class.class class
 *
 * Location.class(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    explicit Location(Config&);

/**
* Destructor of Location.class.class class
*
* Location.class.class.class();
*
* @throw   none
**/
    ~Location();

/**
 * Constructor of Location.class.class class
 *
 * Server.class(std::stringstream & webserv_config_file);
 *
 * @param   void
 * @throw   none
 **/
    Location(const Location&);

/**
* Destructor of Location.class.class class
*
* Server.class.class.class();
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
 * Public methode of Location.class.class class
 *
 * std::string parseBlocLocation();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseBlocLocation(std::string &);

/**
 * Public methode of Location.class.class class
 *
 * std::string setRoot();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string setRoot(std::string &);


/**
 * Public methode of Location.class.class class
 *
 * std::string addIndex();
 *
 * @returns     void
 * @param       name is an std::string contain name of serverSocket to add
 * @throw       bloc_exception if name already exist
 */
    std::string addIndex(std::string &);

/**
 * Public methode of Location.class struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();


/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    Config&                                                             _config;
    std::map<std::string, std::string (Location::*)(std::string &)>     _mapTokenListAction;
    std::string                                                         _root;//path of this location
    std::vector<std::string>                                            _index;// set name of specific index file
};


#endif //WEBSERVER_LOCATION_CLASS_HPP
