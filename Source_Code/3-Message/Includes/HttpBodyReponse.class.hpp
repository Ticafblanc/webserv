//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPBODYREPONSE_CLASS_HPP
#define WEBSERVER_HTTPBODYREPONSE_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>

class HttpBodyReponse : public AHttpMessage {
    typedef void (HttpBodyRequest::*dataIsComplete)();

/*>*******************************private section**********************************/
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
 * void sendData();
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
 * void sendData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void setDefaultPage();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void sendData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool checkErrorBytes(std::size_t& bytesExchange);


/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void sendData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool readDataIsNotComplete(std::size_t& bytesExchange);
/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpBodyReponse.class class
 *
 * HttpBodyReponse.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpBodyReponse(const AHttpMessage& base);

/**
* Destructor of HttpBodyReponse.class class
*
* HttpBodyReponse.class);
*
* @throw   none
**/
    ~HttpBodyReponse();

/**
 * Copy constructor of HttpBodyReponse.class class
 *
 * HttpBodyReponse.class(const HttpBodyReponse.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpBodyReponse(const HttpBodyReponse &);

/**
 * Operator overload= of HttpBodyReponse.class class
 *
 * HttpBodyReponse.class(const HttpBodyReponse.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpBodyReponse& operator=(const HttpBodyReponse &);

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
*|                                  Element access                                  |
*====================================================================================
*/


};


#endif //WEBSERVER_HttpBodyReponse_CLASS_HPP
