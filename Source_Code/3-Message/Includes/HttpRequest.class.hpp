//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPREQUEST_CLASS_HPP
#define WEBSERVER_HTTPREQUEST_CLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/4-Utils/Template/PegParser.class.tpp>

class HttpRequest {
/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Config&                                             _config;
    Socket&                                             _socketClient;
    std::string                                         _serverToken;
    Config*                                             _location;
    ssize_t                                             _bytesRecv;
    ssize_t                                             _totalBytesRecv;
    ssize_t                                             _contentLength;
    bool                                                _chunked;
    std::string                                         _crlf;
    std::vector<char>                                   _buffer;
    std::string                                         _data;
    PegParser<HttpRequest>                              _peg;
    std::string                                         _startLineMethode;
    std::string                                         _startLineURL;
    std::string                                         _startLineVersion;
    std::map<const std::string, const std::string>      _mapHttpHeaders;
    bool                                                _complete;
/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/



/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void recvData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void recvData();

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
    void checkBytesRecv();

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
    std::string convertBufferToString();
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
    bool messageIsNotComplete();

    std::string methodeGET(std::string &);
    std::string methodePOST(std::string &);
    std::string methodeDELETE(std::string &);
    void extractHeaderData();
    std::string addToMapHttpHeader(std::string &);
    void setMapTokenStartLine();
    void setMapTokenInformation();

    std::string Host(std::string &token);
    std::string ContentLength(std::string &token);
    std::string TransfereEncoding(std::string &token);
/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpRequest.class class
 *
 * HttpRequest.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpRequest(Config& config, Socket& socket);

/**
* Destructor of HttpRequest.class class
*
* HttpRequest.class);
*
* @throw   none
**/
    ~HttpRequest();

/**
 * Copy constructor of HttpRequest.class class
 *
 * HttpRequest.class(const HttpRequest.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpRequest(const HttpRequest &);

/**
 * Operator overload= of HttpRequest.class class
 *
 * HttpRequest.class(const HttpRequest.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpRequest& operator=(const HttpRequest &);

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
 * void sendData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string getMethode();

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
    std::string& getUrl();

/**
 * Private methode of HttpRequest.class class
 *
 * manage event like receive message
 *
 *     void recvMessage();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    void recvMessage();

    void recvRequest();

    void setContentLenght();

    void recvHeaderfirst();

    void recvHeaderChunck();

    bool isComplete() const;


    void findBestConfig();

    void findRessource();

    bool isDirectory();

    bool isFile(std::string &path);

    std::string checkIsCgi();

    void setIndex();

    void setAutoIndex();
};


#endif //WEBSERVER_HTTPREQUEST_CLASS_HPP
