//
// Created by Matthis DoQuocBao on 2023-06-09.
//

#ifndef WEBSERVER_EXECUTE_HPP
#define WEBSERVER_EXECUTE_HPP

#include "HttpRequest.class.hpp"

class Execute {

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                       Member                                     |
*====================================================================================
*/
    HttpRequest&                                _httpRequest;
    std::map<std::string, void (Execute::*)()>  _mapMethode;
    std::string                                 _reponse;
    std::string                                 _contentType;

/*
*====================================================================================
*|                                       Methode                                    |
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
 * Operator overload= of Execute.class class
 *
 * Execute.class(const Execute.class &);
 *
 * @param   http_request instance const to copy the server
 * @throw   none
 **/
    void selectLocation();

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
    Execute(HttpRequest& httpRequest);

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
/*
*====================================================================================
*|                                  Class Exception                                 |
*====================================================================================
*/


/**
 * Class exception of Execute.class class
 *
 * class executeException;
 *
 * @inherit std::exception
 **/
    class executeException: public std::exception
    {
    public:

        /**
         * Constructor of executeException class
         *
         * executeException(server & server , const char * message);
         *
         * @param   server is a server reference to set the private _server
         *          to manage the close of server class
         *          message to store const char*
         * @throw   none
         **/
        executeException(const char * message);

        /**
         * Copy constructor of executeException class
         *
         * executeException(executeException &);
         *
         * @param   http_request_exception instance to build the executeException
         *          http_request_socket in an int to close
         * @throw   none
         **/
        executeException(const executeException &);

        /**
         * Operator overload= of executeException class
         *
         * operator=(const executeException&);
         *
         * @param   http_request_exception instance const to copy the executeException
         * @throw   none
         **/
        executeException& operator=(const executeException &);

        /**
        * Destructor of executeException class
        *
        * virtual executeException throw();
        *
        * @throw   none
        **/
        virtual ~executeException() throw();

        /**
         * Public methode of executeException
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


#endif //WEBSERVER_EXECUTE_HPP
