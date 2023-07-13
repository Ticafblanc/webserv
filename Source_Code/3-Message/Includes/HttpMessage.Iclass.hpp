//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_IHTTPMESSAGE_ICLASS_HPP
#define WEBSERVER_IHTTPMESSAGE_ICLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>

#define CLOSE false
#define KEEP_ALIVE true

class IHttpMessage {

public:

/*
*====================================================================================
*|                                  Public Methode                                  |
*====================================================================================
*/
    virtual ~IHttpMessage() {};
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool continueManageEvent() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    virtual bool continueManageEvent() = 0;

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
    virtual void updateClassMessage(IHttpMessage*&) = 0;

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
    virtual bool requestHeadersIsComplete() = 0;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool requestBodyIsComplete() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    virtual bool requestBodyIsComplete() = 0;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool bodyReponseIsComplete() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    virtual bool bodyReponseIsComplete() = 0;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool headersReponseIsComplete() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    virtual bool headersReponseIsComplete() = 0;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * virtual bool isComplete() = 0;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    virtual bool isComplete() = 0;

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
    virtual uint32_t eventsStatus() = 0;
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
    virtual bool connectionStatus() = 0;

};


#endif //WEBSERVER_IHttpMessage_CLASS_HPP
