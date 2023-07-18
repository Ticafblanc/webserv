//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPMESSAGE_ACLASS_HPP
#define WEBSERVER_HTTPMESSAGE_ACLASS_HPP

#include <Source_Code/3-Message/Includes/HttpMessage.Iclass.hpp>

class AHttpMessage : public IHttpMessage {

/*>*******************************private section**********************************/

protected:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Config&                                             _config;
    Socket&                                             _socketClient;
    IHttpMessage*                                       _methode;
    bool                                                _connection;
    uint32_t                                            _events;
    int                                                 _statusCode;
    std::string                                         _header;
    std::vector<char>                                   _body;
    bool                                                _requestHeadersIsComplete;
    bool                                                _requestBodyIsComplete;
    bool                                                _bodyReponseIsComplete;
    bool                                                _headersReponseIsComplete;
    bool                                                _isComplete;
    std::string                                         _startLineMethode;
    std::string                                         _startLineURL;
    std::string                                         _startLineVersion;
    std::map< std::string, std::string>                 _mapHttpHeaders;
    std::size_t                                         _contentLength;
    bool                                                _isChunked;
    std::string                                         _contentType;
    pid_t                                               _pid;
    int                                                 _pipeFdIn[2];
    int                                                 _pipeFdOut[2];

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
 * Constructor of AHttpMessage.class class
 *
 * AHttpMessage.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    AHttpMessage(Config& config, Socket& socket);

/**
* Destructor of AHttpMessage.class class
*
* AHttpMessage.class);
*
* @throw   none
**/
    virtual ~AHttpMessage();

/**
 * Copy constructor of AHttpMessage.class class
 *
 * AHttpMessage.class(const AHttpMessage.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    AHttpMessage(const AHttpMessage &);

/**
 * Operator overload= of AHttpMessage.class class
 *
 * AHttpMessage.class(const AHttpMessage.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    AHttpMessage& operator=(const AHttpMessage &);


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
 *  IHttpMessage* updateClassMessage(IHttpMessage*) override;
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void updateClassMessage(IHttpMessage*&) override;

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
 * void extractHeaderData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool checkIsAllowedMethode(int allow, int dual1, int dual2) const;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * void extractHeaderData();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void redirection();
};


#endif //WEBSERVER_HttpHeaders_CLASS_HPP
