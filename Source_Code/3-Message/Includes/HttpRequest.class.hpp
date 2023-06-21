//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPREQUEST_CLASS_HPP
#define WEBSERVER_HTTPREQUEST_CLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/4-Utils/Template/PegParser.class.tpp>

class HeaderRequest {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    PegParser<HeaderRequest>                                            _peg;
    std::string                                                         _startLineMethode;
    std::string                                                         _startLineURL;
    std::string                                                         _startLineVersion;
    std::map<const std::string, const std::string>                      _mapHttpHeaders;
    bool                                                                _endHeader;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

    std::string addToStartLine(std::string &);
    std::string addToMapHttpHeader(std::string &);
    void setMapTokenStartLine();
    void setMapTokenInformation();

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HeaderRequest class
 *
 * HeaderRequest();
 *
 * @param   void
 * @throw   none
 **/
    HeaderRequest();

/**
 * Constructor of HeaderRequest class
 *
 * HeaderRequest(Config & config);
 *
 * @param   config &
 * @throw   none
 **/
    explicit HeaderRequest(std::string& message);

/**
* Destructor of HeaderRequest class
*
* HeaderRequest);
*
* @throw   none
**/
    ~HeaderRequest();

/**
 * Copy constructor of HeaderRequest class
 *
 * HeaderRequest(const HeaderRequest &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HeaderRequest(const HeaderRequest &);

/**
 * Operator overload= of HeaderRequest class
 *
 * HeaderRequest(const HeaderRequest &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HeaderRequest& operator=(const HeaderRequest &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/
    const std::string &getStartLineMethode() const;

    std::string &getStartLineUrl();

    const std::string &getStartLineVersion() const;

    const std::map<const std::string, const std::string> &getMapHttpHeaders() const;

    std::string endHeader(std::string &token);
};

class HttpRequest {
/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    ssize_t                         _bytesRecv;
    ssize_t                         _contentLength;
    std::vector<std::string>        _buffer;
    HeaderRequest                   _headRequest;


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
    void recvData(int sizeBuffer);

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
    void checkBytesRecv() const;

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
 * HttpRequest.class(Config & config);
 *
 * @param   config &
 * @throw   none
 **/
    HttpRequest();

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

    void recvHeader();

    void setContentLenght();
};


#endif //WEBSERVER_HTTPREQUEST_CLASS_HPP
