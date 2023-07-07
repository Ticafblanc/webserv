//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_HTTPMESSAGE_CLASS_HPP
#define WEBSERVER_HTTPMESSAGE_CLASS_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/4-Utils/Template/PegParser.class.tpp>

class HttpMessage {
/*>*******************************private section**********************************/

typedef bool (HttpMessage::*dataIsComplete)(std::size_t&);

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    Config&                                             _config;
    Config*                                             _location;

    Socket&                                             _socketClient;
    std::string                                         _serverToken;//
    std::size_t                                         _totalBytesExchange;
    std::size_t                                         _contentLength;
    bool                                                _headerIsComplete;
    bool                                                _chunkedIsComplete;
    bool                                                _bodyIsComplete;
    bool                                                _requestIsComplete;
    std::vector<char>                                   _buffer;//
    dataIsComplete                                      _methodeToRecv;//
    std::string                                         _data;
    std::vector<std::string>                            _vecdata;
    PegParser<HttpMessage>                              _peg;
    std::string                                         _startLineMethode;//
    std::string                                         _startLineURL;//
    std::string                                         _startLineVersion;//
    std::string                                         _startLineStatusCode;
    int                                                 _statusCode;
    std::string                                         _queryString;
    std::map< std::string, std::string>                 _mapHttpHeadersRequest;
    std::map< std::string, std::string>                 _mapHttpHeadersReponse;
    std::ostringstream                                  _oss;
    std::string                                         _contentType;
    pid_t                                               _pid;
    int                                                 _pipeFdIn[2];
    int                                                 _pipeFdOut[2];

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
 * bool recvHeaderfirst();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool recvHeader();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool headerIsNotComplete();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool headerIsNotComplete(std::size_t& bytesExchange);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool checkErrorBytesRecv();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool checkErrorBytesExchange(std::size_t& bytesExchange);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool recvHeaderChunck();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool recvChunck();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool headerIsNotComplete();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool chunkIsComplete(std::string & str);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool recvHeaderfirst();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool recvBody();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool headerIsNotComplete();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool bodyIsComplete(std::string & str);





/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * bool bodyIsNotComplete();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool bodyIsNotComplete();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string bufferToDataString();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string bufferToDataString();



















/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string convertBufferToString();
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
 * bool messageIsNotComplete();
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool messageIsNotComplete();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string methodeGET(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string methodeGET(std::string &);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string methodePOST(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string methodePOST(std::string &);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string methodeDELETE(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string methodeDELETE(std::string &);

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
    void extractHeaderData();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string addToMapHttpHeader(std::string &);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string addToMapHttpHeader(std::string &);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string Host(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string Host(std::string &token);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string ContentLength(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string ContentLength(std::string &token);

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    std::string TransfereEncoding(std::string &token);


/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void setContentLenght();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool isComplete() const;

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void findBestConfig(std::vector<std::pair<std::string, Config> > &UriConfig);
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    void findRessource();
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool checkIsPHP();
/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool setIndex();

/**
 * Private methode of server class
 *
 * extract data and put in std::string
 *
 * std::string TransfereEncoding(std::string &token);
 *
 * @returns string with message content
 * @param   client_socket send message
 * @throws  server::server_exception
 * */
    bool setAutoIndex();

    friend void PegParser<HttpMessage>::setMapTokenHeaderStartLine();
    friend void PegParser<HttpMessage>::setMapTokenHeadersInformation();

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of HttpMessage.class class
 *
 * HttpMessage.class(int socket, int clientHeaderBufferSize,
                         int clientBodyBufferSize, int clientMaxBodySize);
 *
 * @param   config &
 * @throw   none
 **/
    HttpMessage(Config& config, Socket& socket);

/**
* Destructor of HttpMessage.class class
*
* HttpMessage.class);
*
* @throw   none
**/
    ~HttpMessage();

/**
 * Copy constructor of HttpMessage.class class
 *
 * HttpMessage.class(const HttpMessage.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    HttpMessage(const HttpMessage &);

/**
 * Operator overload= of HttpMessage.class class
 *
 * HttpMessage.class(const HttpMessage.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    HttpMessage& operator=(const HttpMessage &);

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


#endif //WEBSERVER_HTTPMESSAGE_CLASS_HPP