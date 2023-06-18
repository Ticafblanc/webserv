//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#ifndef WEBSERVER_CODE_CLASS_HPP
#define WEBSERVER_CODE_CLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/4-Utils/Includes/Utils.hpp>

class Code {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Code.class.class class
 *
 * Code.class(pegParser& pegParser);
 *
 * @param   peg_parser
 * @throw   none
 **/
    Code();

/**
* Destructor of Code.class.class class
*
* Code.class.class.class();
*
* @throw   none
**/
    ~Code();

/**
 * Copy constructor of Code.class class
 *
 * Code.class(const Code.class &);
 *
 * @param   blocCode instance to build the serverSocket
 * @throw   none
 **/
    Code(const Code&);

/**
 * Operator overload= of Code.class class
 *
 * Code.class(const Code.class &);
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
 * Public methode of Code.class.class class
 *
 * void setStatusCode(int code);
 *
 * @returns     void
 * @param       code
 * @throw       none
 */
    void setNewCode(int code, const std::string& status, const std::string& pathToHtmlPage);

/**
 * Public methode of Code.class.class class
 *
 * void setStatusCode(int code);
 *
 * @returns     void
 * @param       code
 * @throw       none
 */
    bool FindCode(int code);

/**
 * Public methode of Code.class.class class
 *
 * void setStatusCode(int code);
 *
 * @returns     void
 * @param       code
 * @throw       none
 */
    void setDefaultPage(int code, const std::string& pathToHtmlPage);

/**
 * Public methode of Code.class.class class
 *
 * void setStatusCode(int code);
 *
 * @returns     void
 * @param       code
 * @throw       none
 */
    void setStatus(int code, const std::string& status);

/**
 * Public methode of Code.class.class class
 *
 * void setStatusCode(int code);
 *
 * @returns     void
 * @param       code
 * @throw       none
 */
    void setStatusCode(int code);

/**
 * Public methode of Code.class.class class
 *
 * std::string  getStatusCode();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string  getStatusCode(int statusCode) const;
    int  getCode() const;

/**
 * Public methode of Code.class.class class
 *
 * std::string & getStatusPage();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    const std::string & getStatusPage(int statusCode) const;


/*>*******************************private section**********************************/

private:
/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Public methode of Code.class.class class
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
    std::map<int, std::pair<std::string, std::string> >   _mapStatusCode;
    int                                                   _statusCode;
};


#endif //WEBSERVER_CODE_CLASS_HPP
