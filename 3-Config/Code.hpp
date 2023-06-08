//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#ifndef WEBSERVER_CODE_HPP
#define WEBSERVER_CODE_HPP

#include "0-Main/Includes/Headers.hpp"
#include "1-Utils/Includes/Utils.hpp"

class Code {

/*>********************************public section**********************************/

public:

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
 * void setStatusCode(int code);
 *
 * @returns     void
 * @param       code
 * @throw       none
 */
    void setDefaultPage(int code, const std::string& pathToHtmlPage);

/**
 * Public methode of Code.class class
 *
 * void setStatusCode(int code);
 *
 * @returns     void
 * @param       code
 * @throw       none
 */
    void setStatusCode(int code);

/**
 * Public methode of Code.class class
 *
 * std::string  getStatusCode();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string  getStatusCode() const;
    int  getCode() const;

/**
 * Public methode of Code.class class
 *
 * std::string & getStatusPage();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    const std::string & getStatusPage() const;


/*>*******************************private section**********************************/

private:
/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Public methode of Code.class class
 *
 * void buildStatusCode();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    void buildStatusCode();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::map<int, std::pair<const std::string, const std::string> >   _mapStatusCode;
    int                                                                 _statusCode;
};


#endif //WEBSERVER_CODE_HPP
