//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPHEADERS_ACLASS_HPP
#define WEBSERVER_HTTPHEADERS_ACLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Iclass.hpp>

class AHttpHeaders : public IHttpMessage {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Config&                                             _config;
    Socket&                                             _socketClient;
    std::string                                         _startLineVersion;
    std::map< std::string, std::string>                 _mapHttpHeaders;

/*
*====================================================================================
*|                                  Private Methode                                 |
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
 * Constructor of AHttpHeaders.class class
 *
 * AHttpHeaders.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    AHttpHeaders(Config& config, Socket& socket);

/**
* Destructor of AHttpHeaders.class class
*
* AHttpHeaders.class);
*
* @throw   none
**/
    virtual ~AHttpHeaders();

/**
 * Copy constructor of AHttpHeaders.class class
 *
 * AHttpHeaders.class(const AHttpHeaders.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    AHttpHeaders(const AHttpHeaders &);

/**
 * Operator overload= of AHttpHeaders.class class
 *
 * AHttpHeaders.class(const AHttpHeaders.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    AHttpHeaders& operator=(const AHttpHeaders &);


/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/
    virtual Config &getConfig() const = 0;

    virtual void setConfig(Config &config) = 0;

    virtual const std::string &getStartLineVersion() const = 0;

    virtual void setStartLineVersion(const std::string &startLineVersion) = 0;

    virtual const std::map<std::string, std::string> &getMapHttpHeaders() const = 0;

    virtual void setMapHttpHeaders(const std::map<std::string, std::string> &mapHttpHeaders) = 0;
};


#endif //WEBSERVER_HttpHeaders_CLASS_HPP
