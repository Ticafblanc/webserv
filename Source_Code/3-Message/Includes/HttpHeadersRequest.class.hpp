//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPHEADERSREQUEST_CLASS_HPP
#define WEBSERVER_HTTPHEADERSREQUEST_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>
#include <Source_Code/3-Message/Includes/HttpGETRequest.class.hpp>

class HttpHeadersRequest : public AHttpMessage {

/*>*******************************private section**********************************/

typedef bool (HttpHeadersRequest::*dataIsComplete)(std::size_t&);

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    std::vector<char>                                   _buffer;
    std::size_t                                         _totalBytesRecv;
    PegParser<HttpHeadersRequest>                       _peg;
    std::string                                         _queryString;
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
 * bool headerIsNotComplete();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool headerIsNotComplete(std::size_t& bytesExchange);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool checkErrorBytesRecv();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool checkErrorBytesExchange(std::size_t& bytesExchange);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string methodeGET(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string methodeGET(std::string &);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string methodePOST(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string methodePOST(std::string &);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string methodeDELETE(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string methodeDELETE(std::string &);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void extractHeaderData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void extractHeaderData();



    friend void PegParser<HttpHeadersRequest>::setMapTokenHeaderStartLine();


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
    HttpHeadersRequest(Config& config, Socket& socket);

/**
* Destructor of HttpHeadersRequest.class class
*
* HttpHeadersRequest.class);
*
* @throw   none
**/
    ~HttpHeadersRequest();

/**
 * Copy constructor of HttpHeadersRequest.class class
 *
 * HttpHeadersRequest.class(const HttpHeadersRequest.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpHeadersRequest(const HttpHeadersRequest &);

/**
 * Operator overload= of HttpHeadersRequest.class class
 *
 * HttpHeadersRequest.class(const HttpHeadersRequest.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpHeadersRequest& operator=(const HttpHeadersRequest &);


/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/



};


#endif //WEBSERVER_HttpHeadersRequest_CLASS_HPP
