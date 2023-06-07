//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#ifndef WEBSERVER_CODE_HPP
#define WEBSERVER_CODE_HPP


struct Code {


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
 * std::string parseBlocCode();
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    void setStatusCode();

/**
 * Public methode of Code.class class
 *
 * std::string & operator[](int code);
 *
 * @returns     string contain error message
 * @param       void
 * @throw       none
 */
    std::string & getStatusCode();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::map<int, std::string>                         _mapStatusCode;
    int                                                _statusCode;
};


#endif //WEBSERVER_CODE_HPP
