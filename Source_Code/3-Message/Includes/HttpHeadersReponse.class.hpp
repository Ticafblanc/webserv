//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HttpHeadersReponse_CLASS_HPP
#define WEBSERVER_HttpHeadersReponse_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>

class HttpHeadersReponse : public AHttpMessage {
    
/*>*******************************private section**********************************/
private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/



/*
*====================================================================================
*|                                  Private Methode                                 |
*====================================================================================
*/
    void updateMapHeaders(std::string& cgiHeaders);

    void startLine();

    void addDate();

    void addServer();

    void setHeaders();
/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpHeadersReponse.class class
 *
 * HttpHeadersReponse.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpHeadersReponse(const AHttpMessage& base);
    HttpHeadersReponse(const AHttpMessage& base, std::string& CgiHeader);

/**
* Destructor of HttpHeadersReponse.class class
*
* HttpHeadersReponse.class);
*
* @throw   none
**/
    ~HttpHeadersReponse();

/**
 * Copy constructor of HttpHeadersReponse.class class
 *
 * HttpHeadersReponse.class(const HttpHeadersReponse.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpHeadersReponse(const HttpHeadersReponse &);

/**
 * Operator overload= of HttpHeadersReponse.class class
 *
 * HttpHeadersReponse.class(const HttpHeadersReponse.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpHeadersReponse& operator=(const HttpHeadersReponse &);

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


};


#endif //WEBSERVER_HttpHeadersReponse_CLASS_HPP
