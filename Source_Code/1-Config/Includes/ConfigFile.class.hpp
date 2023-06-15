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

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/4-Utils/Includes/PegParser.class.tpp>
#include <Source_Code/1-Config/Includes/Listen.class.hpp>

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
    ConfigFile(Config & config, PegParser<ConfigFile>& peg);

/**
 * Constructor of ConfigFile class
 *
 * ConfigFile(Config & config, std::string & pathToConfigFile, char ** envp);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   none
 **/
    ConfigFile(ConfigFile& configFile, Config * config);


    /**
* Destructor of ConfigFile class
*
* ConfigFile @throw   none
**/
    virtual ~ConfigFile();
//
///**
// * Copy constructor of ConfigFile class
// *
// * ConfigFile(ConfigFile &);
// *
// * @param   configWebserv instance to build the serverSocket
// * @throw   none
// **/
//    ConfigFile(const ConfigFile &);
//
///**
// * Operator overload= of ConfigFile class
// *
// * ConfigFile& operator=(const ConfigFile &);
// *
// * @param   configWebserv instance const to copy the serverSocket
// * @throw   none
// **/
//    ConfigFile& operator=(const ConfigFile &);


/*>*******************************private section**********************************/

private:
/*
*====================================================================================
*|                                  Element access                                  |
*====================================================================================
*/

/**
 * Public methode of ConfigFile struct
 *
 * void parseFile();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void parseFile();

/**
 * Public methode of ConfigFile struct
 *
 * void parseFile();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void parseBloc();

/**
 * Protected methode of ConfigFile struct
 *
 * std::string blocToken(std::string & token);
 *
 * @returns     void
 * @param       void
 */
    std::string blocToken(std::string & token);

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
 * Protected methode of ConfigFile struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setClientBodyBufferSize(std::string &);

/**
 * Protected methode of ConfigFile struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setClientHeaderBufferSize(std::string &);

/**
 * Protected methode of ConfigFile struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setClientMaxBodySize(std::string &);

/**
 * Protected methode of ConfigFile struct
 *
 * std::string setWorkerProcesses();
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string setWorkerConnections(std::string &);

/**
 * Protected methode of ConfigFile struct
 *
 * std::string addVectorListen(std::string &);
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string addVectorListen(std::string &);

    /**
 * Protected methode of ConfigFile struct
 *
 * sstd::string addIndex(std::string &);
 *
 * @returns     std::string if error in data for this token
 * @param       void
 */
    std::string addIndex(std::string &);

    /**
* Protected methode of ConfigFile struct
*
* std::string addVectorServerName(std::string &);
*
* @returns     std::string if error in data for this token
* @param       void
*/
    std::string addVectorServerName(std::string &);

    /**
* Protected methode of ConfigFile struct
*
* std::string setRoot(std::string &);
*
* @returns     std::string if error in data for this token
* @param       void
*/
    std::string setRoot(std::string &);

    /**
* Protected methode of ConfigFile struct
*
* std::string setAllowMethods(std::string &);
*
* @returns     std::string if error in data for this token
* @param       void
*/
    std::string setAllowMethods(std::string &);


/**
* Protected methode of ConfigFile struct
*
* std::string setAutoIndex(std::string &);
*
* @returns     std::string if error in data for this token
* @param       void
*/
    std::string setAutoIndex(std::string &);

/**
* Protected methode of ConfigFile struct
*
* std::string setErrorPage(std::string &);
*
* @returns     std::string if error in data for this token
* @param       void
*/
    std::string setErrorPage(std::string &);

/**
* Protected methode of ConfigFile struct
*
* std::string setReturn(std::string &);
*
* @returns     std::string if error in data for this token
* @param       void
*/
    std::string setReturn(std::string &);

/**
* Protected methode of ConfigFile struct
*
* std::string setReturn(std::string &);
*
* @returns     std::string if error in data for this token
* @param       void
*/
    std::string setCgiPass(std::string &);

/**
 * Public methode of ConfigFile struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapToken(const std::string & token);
/**
 * Public methode of ConfigFile struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapTokenEvents();

/**
 * Public methode of ConfigFile struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapTokenHttp();

/**
 * Public methode of ConfigFile struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapTokenFile();


    /**
 * Public methode of ConfigFile struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapTokenServer();

    /**
 * Public methode of ConfigFile struct
 *
 * void setMapToken();
 *
 * @returns     void
 * @param       void
 * @throw       none
 */
    void setMapTokenLocation();

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    Config&                                                             _config;
    PegParser<ConfigFile>&                                              _peg;
    Config*                                                             _parent;
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