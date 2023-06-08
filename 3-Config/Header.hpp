//
// Created by Matthis DoQuocBao on 2023-06-07.
//

#ifndef WEBSERVER_HEADER_HPP
#define WEBSERVER_HEADER_HPP

#include "0-Main/Includes/Headers.hpp"
#include "6-PegParser/PegParser.class.hpp"

class HeaderReponse {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/


    std::string                                                             _startLineVersion;
    std::string                                                             _startLineStatusCode;
    std::map<std::string, std::string>                                      _mapHttpHeaders;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/



/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HeaderReponse class
 *
 * HeaderReponse();
 *
 * @param   config &
 * @throw   none
 **/
    HeaderReponse();

/**
 * Copy constructor of HeaderReponse class
 *
 * HeaderReponse(const HeaderReponse &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HeaderReponse(const HeaderReponse &);

/**
 * Operator overload= of HeaderReponse class
 *
 * HeaderReponse(const HeaderReponse &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HeaderReponse& operator=(const HeaderReponse &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

    void setStartLineStatusCode(std::string&);

    void setMapHttpHeaders(std::string& token, std::string& value);

    const std::string & getHeaderReponse();

};

class HeaderRequest {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    PegParser                                                           _peg;
    std::string                                                         _startLineMethode;
    std::string                                                         _startLineURL;
    std::string                                                         _startLineVersion;
    std::map<std::string, std::string>                                  _mapHttpHeaders;
    std::map<std::string, std::string (HeaderRequest::*)(std::string &)>       _mapTokenListAction;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

    std::string addToStartLine(std::string &);
    std::string addToMapHttpHeader(std::string &);
    void setMapTokenStartLine();
    void setMapTokenInformation();

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HeaderRequest class
 *
 * HeaderRequest();
 *
 * @param   void
 * @throw   none
 **/
    HeaderRequest();

/**
 * Constructor of HeaderRequest class
 *
 * HeaderRequest(Config & config);
 *
 * @param   config &
 * @throw   none
 **/
    HeaderRequest(std::string& message);

/**
* Destructor of HeaderRequest class
*
* HeaderRequest);
*
* @throw   none
**/
    ~HeaderRequest();

/**
 * Copy constructor of HeaderRequest class
 *
 * HeaderRequest(const HeaderRequest &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HeaderRequest(const HeaderRequest &);

/**
 * Operator overload= of HeaderRequest class
 *
 * HeaderRequest(const HeaderRequest &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HeaderRequest& operator=(const HeaderRequest &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/
    const string &getStartLineMethode() const;

    const string &getStartLineUrl() const;

    const string &getStartLineVersion() const;

    const std::map<std::string, std::string> &getMapHttpHeaders() const;

};


#endif //WEBSERVER_HEADER_HPP
