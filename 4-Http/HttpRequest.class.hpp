//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPREQUEST_CLASS_HPP
#define WEBSERVER_HTTPREQUEST_CLASS_HPP

#include "3-Config/Config.class.hpp"

class HeaderRequest {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    PegParser                                                           _peg;
    std::string                                                         _startLineMethode;
    std::string                                                         _startLineURL;
    std::string                                                         _startLineVersion;
    std::map<const std::string, const std::string>                                  _mapHttpHeaders;
    std::map<std::string, std::string (HeaderRequest::*)(std::string &)>       _mapTokenListAction;

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
    HeaderRequest(std::string& message);

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
    const string &getStartLineMethode() const;

    const string &getStartLineUrl() const;

    const string &getStartLineVersion() const;

    const std::map<const std::string, const std::string> &getMapHttpHeaders() const;
/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of HttpRequest.class class
 *
 * class headerException;
 *
 * @inherit std::exception
 **/
    class headerException: public std::exception
    {
    public:

        /**
         * Constructor of headerException class
         *
         * headerException(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        headerException(const char * message);

        /**
         * Copy constructor of headerException class
         *
         * headerException(headerException &);
         *
         * @param   http_request_exception instance to build the headerException
         *          http_request_socket in an int to close
         * @throw   none
         **/
        headerException(const headerException &);

        /**
         * Operator overload= of headerException class
         *
         * operator=(const headerException&);
         *
         * @param   http_request_exception instance const to copy the headerException
         * @throw   none
         **/
        headerException& operator=(const headerException &);

        /**
        * Destructor of headerException class
        *
        * virtual headerException throw();
        *
        * @throw   none
        **/
        virtual ~headerException() throw();

        /**
         * Public methode of headerException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "socket error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string     _message;
    };
};

class HttpRequest {
/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Socket&                         _socket;
    Server&                         _server;
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
    HttpRequest(Socket& socket, Server& server);

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
    std::string getUrl();

/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of HttpRequest.class class
 *
 * class httpRequestException;
 *
 * @inherit std::exception
 **/
    class httpRequestException: public std::exception
    {
    public:

        /**
         * Constructor of httpRequestException class
         *
         * httpRequestException(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        httpRequestException(const char * message);

        /**
         * Copy constructor of httpRequestException class
         *
         * httpRequestException(httpRequestException &);
         *
         * @param   http_request_exception instance to build the httpRequestException
         *          http_request_socket in an int to close
         * @throw   none
         **/
        httpRequestException(const httpRequestException &);

        /**
         * Operator overload= of httpRequestException class
         *
         * operator=(const httpRequestException&);
         *
         * @param   http_request_exception instance const to copy the httpRequestException
         * @throw   none
         **/
        httpRequestException& operator=(const httpRequestException &);

        /**
        * Destructor of httpRequestException class
        *
        * virtual httpRequestException throw();
        *
        * @throw   none
        **/
        virtual ~httpRequestException() throw();

        /**
         * Public methode of httpRequestException
         *
         * virtual const char * what() const throw();
         *
         * @returns  const char * store in private std::string _message
         *          at the construction defaut constructor "socket error"
         * @param   void
         * @throw   none
         **/
        virtual const char * what() const throw();

    private:
        std::string     _message;
    };


};


#endif //WEBSERVER_HTTPREQUEST_CLASS_HPP
