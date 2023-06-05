//
// Created by Matthis DoQuocBao on 2023-06-05.
//

#ifndef WEBSERVER_CONFIG_CLASS_HPP
#define WEBSERVER_CONFIG_CLASS_HPP

#include "0-Main/Includes/webserv.hpp"


class Config {
/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of 3-Config.class class
 *
 * 3-Config.class();
 *
 * @param   void
 * @throw   none
 **/
    Config();

/**
 * Constructor of 3-Config.class class
 *
 * 3-Config.class(std::string &);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   none
 **/
    Config(std::string &);

/**
* Destructor of 3-Config.class class
*
* 3-Config.class @throw   none
**/
    ~Config();

/**
 * Copy constructor of 3-Config.class class
 *
 * 3-Config.class(3-Config.class &);
 *
 * @param   configWebserv instance to build the serverSocket
 * @throw   none
 **/
    Config(Config &);

/**
 * Operator overload= of 3-Config.class class
 *
 * 3-Config.class& operator=(const 3-Config.class &);
 *
 * @param   configWebserv instance const to copy the serverSocket
 * @throw   none
 **/
    Config& operator=(const Config &);

/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Protected methode of 3-Config.class struct
 *
 * std::string parseBlocEvent();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocEvent();

/**
 * Protected methode of 3-Config.class struct
 *
 * std::string parseBlocHttp();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocHttp();

/**
 * Protected methode of 3-Config.class struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setWorkerProcesses();

/**
 * Public methode of 3-Config.class struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of 3-Config.class struct
 *
 * void setDefaultValue();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setDefaultValue();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    pegParser                                                  _pegParser;
    std::map<std::string, std::string (Config::*)()>    _mapTokenListAction;
    int                                                        _workerProcess;
    blocEvents                                                 _blocEvents;//required
    blocHttp                                                   _blocHttp;//if not set as default
    std::vector<blocServer>                                    _vectorServer;
    std::map<int, Socket>                                _mapFdSocket;
};

setLogFile("/webserv/config_content_server/for_var/log/log_error.txt");//@todo add log
#endif //WEBSERVER_CONFIG_CLASS_HPP
