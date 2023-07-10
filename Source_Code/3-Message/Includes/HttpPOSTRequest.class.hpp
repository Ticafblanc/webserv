//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPPOSTSREQUEST_CLASS_HPP
#define WEBSERVER_HTTPPOSTSREQUEST_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>

class HttpPOSTRequest : public AHttpMessage {

/*>*******************************private section**********************************/


private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    PegParser<HttpPOSTRequest>                          _peg;
    std::size_t                                         _contentLength;
    bool                                                _isChunked;
    bool                                                _isCGI;
    std::string                                         _contentType;

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
    void extractData();

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
    bool startCgi();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string addToMapHttpHeader(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string addToMapHttpHeader(std::string &);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string Host(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string Host(std::string &token);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string ContentLength(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string ContentLength(std::string &token);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string TransfereEncoding(std::string &token);


/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig);
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void findRessource();
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool checkIsPHP();
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool setIndex();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string endHeader(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string endHeader(std::string &token);

    friend void PegParser<HttpPOSTRequest>::setMapTokenHeadersInformation();

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
 * Constructor of HttpHeadersRequest.class class
 *
 * HttpHeadersRequest.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpPOSTRequest(const AHttpMessage& base, const std::string & data);

/**
* Destructor of HttpHeadersRequest.class class
*
* HttpHeadersRequest.class);
*
* @throw   none
**/
    ~HttpPOSTRequest();

/**
 * Copy constructor of HttpHeadersRequest.class class
 *
 * HttpHeadersRequest.class(const HttpHeadersRequest.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpPOSTRequest(const HttpPOSTRequest &);

/**
 * Operator overload= of HttpHeadersRequest.class class
 *
 * HttpHeadersRequest.class(const HttpHeadersRequest.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpPOSTRequest& operator=(const HttpPOSTRequest &);

};


#endif //WEBSERVER_HttpHeadersRequest_CLASS_HPP
