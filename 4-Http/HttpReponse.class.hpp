//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPREPONSE_CLASS_HPP
#define WEBSERVER_HTTPREPONSE_CLASS_HPP

#include "Execute.class.hpp"

class HeaderReponse {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/

    Execute&                                                                _execute;
    Server&                                                                 _server;
    std::string                                                             _startLineVersion;
    std::string                                                             _startLineStatusCode;
    std::map<std::string, std::string>                                      _mapHttpHeaders;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

    void addStatusCode();

    void addHttpHeaders(const string &token, const string &value);

    void addDate();

    void addContentInfo();

    void addConnectionClose();


/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HeaderReponse class
 *
 * HeaderReponse();
 *
 * @param   config &
 * @throw   none
 **/
    HeaderReponse(Execute & execute, Server & server);

/**
 * Copy constructor of HeaderReponse class
 *
 * HeaderReponse(const HeaderReponse &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HeaderReponse(const HeaderReponse &);

/**
 * Operator overload= of HeaderReponse class
 *
 * HeaderReponse(const HeaderReponse &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HeaderReponse& operator=(const HeaderReponse &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

    const std::string & getHeaderReponse();

};


class HttpReponse {
/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Server&                         _server;
    Socket&                         _socket;
    Execute&                        _execute;
    ssize_t                         _bytesSend;
    std::vector<std::string>        _buffer;
    HeaderReponse                   _headReponse;

/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/

/**
 * Private methode of HttpReponse.class class
 *
 * manage event like receive message
 *
 *     void sendMessage();
 *
 * @returns void
 * @param   void
 * @throws  http_request::http_request_exception
 * */
    void sendMessage();

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
    void sendData(const std::string& message);


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
    void checkBytesSend();

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
 * Constructor of HttpReponse.class class
 *
 * HttpReponse.class(Config & config);
 *
 * @param   config &
 * @throw   none
 **/
    HttpReponse(Socket& socket, Execute & execute, Server& server);

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
*|                                  Element access                                  |
*====================================================================================
*/


/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of HttpReponse.class class
 *
 * class httpReponseException;
 *
 * @inherit std::exception
 **/
    class httpReponseException: public std::exception
    {
    public:

        /**
         * Constructor of httpReponseException class
         *
         * httpReponseException(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        httpReponseException(const char * message);

        /**
         * Copy constructor of httpReponseException class
         *
         * httpReponseException(httpReponseException &);
         *
         * @param   http_request_exception instance to build the httpReponseException
         *          http_request_socket in an int to close
         * @throw   none
         **/
        httpReponseException(const httpReponseException &);

        /**
         * Operator overload= of httpReponseException class
         *
         * operator=(const httpReponseException&);
         *
         * @param   http_request_exception instance const to copy the httpReponseException
         * @throw   none
         **/
        httpReponseException& operator=(const httpReponseException &);

        /**
        * Destructor of httpReponseException class
        *
        * virtual httpReponseException throw();
        *
        * @throw   none
        **/
        virtual ~httpReponseException() throw();

        /**
         * Public methode of httpReponseException
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

    void chunckMessage();
};


#endif //WEBSERVER_HTTPREPONSE_CLASS_HPP