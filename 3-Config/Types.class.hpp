//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_TYPES_HPP
#define WEBSERVER_TYPES_HPP

#include "0-Main/Includes/webserv.hpp"

class Types {

/*>********************************public section**********************************/

public:

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
        explicit Types(const std::string& pathFile);

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
        Types(const Types&);

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

/*>*******************************private section**********************************/

private:

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


#endif //WEBSERVER_TYPES_HPP
