//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPGETREQUEST_CLASS_HPP
#define WEBSERVER_HTTPGETREQUEST_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>
#include <Source_Code/3-Message/Includes/HttpBodyReponse.class.hpp>

class HttpGETRequest : public AHttpMessage {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    PegParser<HttpGETRequest>                           _peg;


/*
*====================================================================================
*|                                  Private Methode                                 |
*====================================================================================
*/



/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool continueManageEvent() override;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool extractFileToBuffer();


/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction Override                        |
*====================================================================================
*/

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool continueManageEvent() override;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool continueManageEvent() override;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpGETRequest.class class
 *
 * HttpGETRequest.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpGETRequest(const AHttpMessage& base, const std::string & data);

/**
* Destructor of HttpGETRequest.class class
*
* HttpGETRequest.class);
*
* @throw   none
**/
    ~HttpGETRequest();

/**
 * Copy constructor of HttpGETRequest.class class
 *
 * HttpGETRequest.class(const HttpGETRequest.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpGETRequest(const HttpGETRequest &);

/**
 * Operator overload= of HttpGETRequest.class class
 *
 * HttpGETRequest.class(const HttpGETRequest.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpGETRequest& operator=(const HttpGETRequest &);


/*
*====================================================================================
*|                                  Public Metode                                   |
*====================================================================================
*/


};


#endif //WEBSERVER_HttpGETRequest_CLASS_HPP
