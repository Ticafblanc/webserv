//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPBODYREPONSE_CLASS_HPP
#define WEBSERVER_HTTPBODYREPONSE_CLASS_HPP

#include <Source_Code/3-Message/Includes/HttpBody.Aclass.hpp>

class HttpBodyReponse : public AHttpBody {
    
/*>*******************************private section**********************************/
private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    std::string                                         _startLineVersion;
    std::string                                         _startLineStatusCode;
    std::map< std::string, std::string>                 _mapHttpBodyReponse;

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
 * Constructor of HttpBodyReponse.class class
 *
 * HttpBodyReponse.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpBodyReponse(Config& config, Socket& socket);

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
*|                                  Public Methode                                  |
*====================================================================================
*/

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void recvMessage();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool recvMessage();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void sendMessage();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool sendMessage();

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
 * void sendData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string getValueHeader(const std::string& token);

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




    bool checkIsAllowedMethode(int allow, int dual1, int dual2) const;

    void setContent();

    void errorPage();

    void addMapHttpHeader();

    void redirection();

    bool sendMessage(int code);

    bool executePhp();

    bool continueBody();

    void findPostRessource();

    bool bodyChunkIsComplete(std::size_t &bytesExchange);

    void controleHeader();

    bool readDataIsNotComplete(std::size_t& bytesExchange);

    bool writeDataIsNotComplete(size_t &bytesExchange);

    bool checkErrorBytes(size_t &bytesExchange);

    bool bodyIsNotComplete(std::size_t &bytesExchange);
};


#endif //WEBSERVER_HttpBodyReponse_CLASS_HPP
