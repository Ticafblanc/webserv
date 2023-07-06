//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPBODY_ACLASS_HPP
#define WEBSERVER_HTTPBODY_ACLASS_HPP

#include <Source_Code/3-Message/Includes/HttpHeadersRequest.class.hpp>

class AHttpBody : public HttpHeadersRequest{

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
 * Constructor of AHttpBody.class class
 *
 * AHttpBody.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    AHttpBody(Config& config, Socket& socket);

/**
* Destructor of AHttpBody.class class
*
* AHttpBody.class);
*
* @throw   none
**/
    virtual ~AHttpBody();

/**
 * Copy constructor of AHttpBody.class class
 *
 * AHttpBody.class(const AHttpBody.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    AHttpBody(const AHttpBody &);

/**
 * Operator overload= of AHttpBody.class class
 *
 * AHttpBody.class(const AHttpBody.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    AHttpBody& operator=(const AHttpBody &);


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


#endif //WEBSERVER_HttpBody_CLASS_HPP
