//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_EVENTCLASS_HPP
#define WEBSERVER_EVENTCLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>

class Events {

/*>********************************public section**********************************/

public:


/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Events.class class
 *
 * Events(PegParser&);
 *
 * @param   peg_parser &
 * @throw   none
 **/
    explicit Events(Config & config);

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
    Events(const Events &);

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
    std::string parseBlocEvents(std::string &) ;

/*>*******************************private section**********************************/

private:

/**
 * Public methode of Events class
 *
 * std::string setWorkerConnections() ;
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string setWorkerConnections(std::string &) ;

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
    Config&                                                         _config;
    std::map<std::string, std::string (Events::*)(std::string &)>   _mapTokenListAction;
};


#endif //WEBSERVER_EVENTCLASS_HPP
