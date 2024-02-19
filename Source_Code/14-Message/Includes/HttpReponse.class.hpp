//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HttpReponse_CLASS_HPP
#define WEBSERVER_HttpReponse_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Aclass.hpp>

class HttpReponse : public AHttpMessage {
    
/*>*******************************private section**********************************/
private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

   std::vector<std::vector<char> >          _buffers;
   std::size_t                              _totalBytesSend;

/*
*====================================================================================
*|                                  Private Methode                                 |
*====================================================================================
*/
    void chunkData();
    void setData(std::size_t headerSize);
    std::size_t setHeader();
    bool reponseIsNotComplete(std::size_t& bytesExchange);
    bool checkErrorBytesExchange(std::size_t& bytesExchange);
/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpReponse.class class
 *
 * HttpReponse.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpReponse(const AHttpMessage& base);

/**
* Destructor of HttpReponse.class class
*
* HttpReponse.class);
*
* @throw   none
**/
    ~HttpReponse();

/**
 * Copy constructor of HttpReponse.class class
 *
 * HttpReponse.class(const HttpReponse.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpReponse(const HttpReponse &);

/**
 * Operator overload= of HttpReponse.class class
 *
 * HttpReponse.class(const HttpReponse.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpReponse& operator=(const HttpReponse &);

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

    void sendData();
};


#endif //WEBSERVER_HttpReponse_CLASS_HPP
