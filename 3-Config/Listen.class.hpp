//
// Created by Matthis DoQuocBao on 2023-06-10.
//

#ifndef WEBSERVER_LISTEN_HPP
#define WEBSERVER_LISTEN_HPP

#include "0-Main/Includes/webserv.hpp"

class Listen {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of configServer.class class
 *
 * Listen(Config& config);
 *
 * @param   input is a string reference extract befor;
 * @param   config is config webserv reference
 * @throw   none
 **/
    explicit Listen(Config& config, ConfigServer& configServer);

/**
* Destructor of Listen.class class
*
* Listen*
* @throw   none
**/
    ~Listen();

/**
 * Constructor of configServer.class class
 *
 * Listen(const Listen & Listen);
 *
 * @param   listenData &
 * @throw   none
 **/
    Listen(const Listen&);

/**
* Destructor of Listen.class class
*
*  Listen& operator=(const Listen& Listen);
*
* @param   listenData&
* @throw   none
**/
    Listen& operator=(const Listen&);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of Listen.class class
 *
 * std::string parseListenData();
 *
 * @returns     std::vector<std::string>& contain all names of serverSocket
 * @param       void
 * @throw       none
 */
    std::string parseListenData();

    std::string parseListenData(std::string in);

/**
 * private function of config_webserv.class
 *
 * check if the _input member is valid
 * is a valid ip address.
 *
 * @return std::string of an error message
 * @param none
 * @throws none
 */
    std::string check_input();

/**
 * private function of config_webserv.class
 *
 * check if the ip address pass in the function
 * is a valid ip address.
 *
 * @return none
 * @param ip_address is a stringstream, error is a string for the error message if an error occur
 * @throws none
 */
    std::string check_ip(std::string, std::string &);

/**
 * private function of config_webserv.class
 *
 * check if the ip address pass in the function
 * is a valid ip address.
 *
 * @return none
 * @param port is a stringstream, error is a string for the error message if an error occur
 * @throws none
 */
    void check_port(std::string, std::string &);

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    Config&                 _config;
    ConfigServer&           _configServer;

};


#endif //WEBSERVER_LISTEN_HPP
