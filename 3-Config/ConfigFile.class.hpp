/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

#include "0-Main/Includes/webserv.hpp"
#include "3-Config/Http.class.hpp"
#include "3-Config/Events.class.hpp"

class ConfigFile {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of ConfigFile class
 *
 * ConfigFile(Config & config, std::string & pathToConfigFile, char ** envp);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   none
 **/
    explicit ConfigFile(Config & config);

/**
* Destructor of ConfigFile class
*
* ConfigFile @throw   none
**/
    ~ConfigFile();

/**
 * Copy constructor of ConfigFile class
 *
 * ConfigFile(ConfigFile &);
 *
 * @param   configWebserv instance to build the serverSocket
 * @throw   none
 **/
    ConfigFile(const ConfigFile &);

/**
 * Operator overload= of ConfigFile class
 *
 * ConfigFile& operator=(const ConfigFile &);
 *
 * @param   configWebserv instance const to copy the serverSocket
 * @throw   none
 **/
    ConfigFile& operator=(const ConfigFile &);


/*>*******************************private section**********************************/

private:
/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Protected methode of ConfigFile struct
 *
 * std::string parseBlocEvent();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocEvent(std::string &);

/**
 * Protected methode of ConfigFile struct
 *
 * std::string parseBlocHttp();
 *
 * @returns     void
 * @param       void
 */
    std::string parseBlocHttp(std::string &);


/**
 * Protected methode of ConfigFile struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setWorkerProcesses(std::string &);

/**
 * Public methode of ConfigFile struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken();

/**
 * Public methode of ConfigFile struct
 *
 * void parseConfigFile();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void parseConfigFile();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    Config&                                                             _config;
    std::map<std::string, std::string (ConfigFile::*)(std::string &)>   _mapTokenListAction;
    Events                                                              _Events;
    Http                                                                _Http;


};


//        data.setType(SOCK_STREAM);
//        data.setProtocol(0);
//        data.setBacklog(10);
//        data.setAddress(AF_INET, 8081);
//        data.setLevel(SOL_SOCKET);
//        data.setOptionName(SO_REUSEADDR);
//        data.setOptionVal(1);
//        serverSocket serv(data);


#endif //WEBSERV_CONFIG_HPP