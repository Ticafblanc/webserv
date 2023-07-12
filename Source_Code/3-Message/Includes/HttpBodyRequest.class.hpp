//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPBODYREQUEST_CLASS_HPP
#define WEBSERVER_HTTPBODYREQUEST_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>
#include <Source_Code/3-Message/Includes/HttpBodyReponse.class.hpp>

class HttpBodyRequest : public AHttpMessage {

/*>*******************************private section**********************************/

typedef void (HttpBodyRequest::*dataIsComplete)();

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    std::vector<char>   _buffer;
    std::size_t         _totalBytesRecv;
    dataIsComplete      _methodeToRecv;

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
 * bool checkErrorBytesRecv();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool checkErrorBytesExchange(std::size_t bytesExchange);

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
    void recvHeaderChunck();
    void recvBodyChunck();
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
    void recvBody();
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
    bool chunkIsComplete(std::string & str);

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
    bool bodyIsComplete(std::size_t& bytesRecv);
//    bool bodyIsWrite(std::size_t& bytesRecv);
//    bool chunckIsWrite(std::size_t& bytesRecv);
    bool findHeaderChunck();
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string bufferToDataString();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */



/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpBodyRequest.class class
 *
 * HttpBodyRequest.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    explicit HttpBodyRequest(const AHttpMessage& base, const std::string & data);

/**
* Destructor of HttpBodyRequest.class class
*
* HttpBodyRequest.class);
*
* @throw   none
**/
    ~HttpBodyRequest();

/**
 * Copy constructor of HttpBodyRequest.class class
 *
 * HttpBodyRequest.class(const HttpBodyRequest.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpBodyRequest(const HttpBodyRequest &);

/**
 * Operator overload= of HttpBodyRequest.class class
 *
 * HttpBodyRequest.class(const HttpBodyRequest.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpBodyRequest& operator=(const HttpBodyRequest &);

/*
*====================================================================================
*|                                  Public Methode                                  |
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
*|                                  Element access                                  |
*====================================================================================
*/









};


#endif //WEBSERVER_HttpBodyRequest_CLASS_HPP
