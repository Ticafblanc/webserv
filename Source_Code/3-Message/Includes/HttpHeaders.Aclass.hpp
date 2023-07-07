//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPHEADERS_ACLASS_HPP
#define WEBSERVER_HTTPHEADERS_ACLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Iclass.hpp>

class AHttpHeaders : public IHttpMessage {

/*>*******************************private section**********************************/

protected:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Config&                                             _config;
    Socket&                                             _socketClient;
    bool                                                _connection;
    uint32_t                                            _events;
    int                                                 _statusCode;
    bool                                                _requestHeadersIsComplete;
    bool                                                _requestBodyIsComplete;
    bool                                                _bodyReponseIsComplete;
    bool                                                _headersReponseIsComplete;
    bool                                                _isComplete;
    std::map< std::string, std::string>                 _mapHttpHeaders;

public:

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

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 *     virtual bool eventsStatus() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void setConfig(Config &config);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 *     virtual bool eventsStatus() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    uint32_t eventsStatus() override;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 *  virtual bool connectionStatus() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool connectionStatus() override;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 *  virtual bool connectionStatus() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void setConnection(bool connection);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 *  virtual bool connectionStatus() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void setEvents(uint32_t events);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 *  virtual bool connectionStatus() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void setStatusCode(int statusCode);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool requestHeadersIsComplete() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool requestHeadersIsComplete() override;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool requestBodyIsComplete() override;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool requestBodyIsComplete() override;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool bodyReponseIsComplete() override;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool bodyReponseIsComplete() override;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool headersReponseIsComplete() override;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool headersReponseIsComplete() override;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool isComplete() override;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool isComplete() override;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 *  virtual bool connectionStatus() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void addMapHttpHeaders(const std::pair<std::string, std::string> &pairHeader);


};


#endif //WEBSERVER_HttpHeaders_CLASS_HPP
