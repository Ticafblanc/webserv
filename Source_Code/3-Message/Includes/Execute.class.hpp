//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_EXECUTE_HPP
#define WEBSERVER_EXECUTE_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/3-Message/Includes/HttpRequest.class.hpp>

class Execute {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    HttpRequest&                                _request;
    Config&                                     _config;
    std::map<std::string, void (Execute::*)()>  _mapMethode;
    std::map<std::string, std::string>          _mapCGI;
    std::string                                 _tokenServer;
    Socket&                                     _client;
    Config*                                     _location;
    bool                                        _isFile;
    std::string                                 _cgi;
    std::ostringstream                          _oss;


/*
*====================================================================================
*|                                       Methode                                    |
*====================================================================================
*/


/**
 * Protected methode of HttpReponse.class class
 *
 * std::string post_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    void GETmethode();


/**
 * Protected methode of HttpReponse.class class
 *
 * std::string post_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    void POSTmethode();

/**
 * Protected methode of HttpReponse.class class
 *
 * std::string delete_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    void DELETEmethode();



/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of Execute.class class
 *
 * Execute.class(Config & config);
 *
 * @param   config &
 * @throw   none
 **/
    Execute(HttpRequest& httpRequest, Config & config, Socket& client);

/**
* Destructor of Execute.class class
*
* Execute.class);
*
* @throw   none
**/
    ~Execute();

/**
 * Copy constructor of Execute.class class
 *
 * Execute.class(const Execute.class &);
 *
 * @param   http_request instance to build the server
 * @throw   none
 **/
    Execute(const Execute &);

/**
 * Operator overload= of Execute.class class
 *
 * Execute.class(const Execute.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    Execute& operator=(const Execute &);


/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Operator overload= of Execute.class class
 *
 * Execute.class(const Execute.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    void buildMapMethode();
/**
 * Protected methode of HttpReponse.class class
 *
 * std::string delete_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    void executeRequest(Config & location);


/**
 * Operator overload= of Execute.class class
 *
 * Execute.class(const Execute.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    void executeLocation();

/**
 * Protected methode of HttpReponse.class class
 *
 * std::string post_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    void selectMethode();

/**
 * Protected methode of HttpReponse.class class
 *
 * std::string delete_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string getReponse();

/**
 * Protected methode of HttpReponse.class class
 *
 * std::string delete_methode();
 *
 * @returns     std::string containt error to throw
 * @param       void
 * @throw       none
 */
    std::string getContentType();

    void defaultPage(int code);

    bool checkIsAllowedMethode(int allow, int dual1, int dual2) const;

    void findRessource();

    bool isDirectory();

    bool isFile(std::string & path);

    void buildMapCGI();

    std::string checkIsCgi();

    void setFile(const std::string &path);

    void setIndex();

    void setAutoIndex();

    void setContent();

    void removeDirectory(std::string &path);

    void removeFile(std::string &path);

    void executCgi();
};


#endif //WEBSERVER_EXECUTE_HPP
