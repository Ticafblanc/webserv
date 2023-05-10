/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_webserv.class.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WEBSERV_CONFIG_WEBSERV_HPP
#define WEBSERV_CONFIG_WEBSERV_HPP

#include <Include/header.hpp>
#include <Include/config_server.class.hpp>

struct config_webserv{

/*>*******************************public section*********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_webserv class
 *
 * config_webserv(std::string path_config_file);
 *
 * @param   path_config_file is a std::string is a path to config file
 *          specified at start of webserv
 * @throw   config_webserv::config_exception
 **/
    config_webserv(std::string path_config_file);

/**
* Destructor of config_webserv class
*
* ~config_webserv();
*
* @throw   none
**/
    ~config_webserv();

/**
* Constructor of config_webserv class
*
* config_webserv(const config_webserv& other);
*
* @param   void
* @throw   none
**/
    config_webserv(const config_webserv& other);

/**
* Operator = of config_webserv class
*
* config_webserv& operator=(const config_webserv& rhs);
*
* @throw   none
**/
    config_webserv& operator=(const config_webserv& rhs);


/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

/**
 * Class exception of config_webserv class
 *
 * class config_exception;
 *
 * @inherit std::exception
 **/
    class config_exception: public std::exception
    {
    public:

        /**
         * Constructor of config_exception class
         *
         * config_exception(config_webserv & config, const char* message);
         *
         * @param   config_webserv is a config_webserv reference to set the private _config
         *          to manage the close of config_webserv class
         *          message to store const char*
         * @throw   none
         **/
        config_exception(config_webserv&, const char *);

        /**
         * Copy constructor of config_exception class
         *
         * config_exception(config_exception &);
         *
         * @param   config_exception instance to build the config_exception
         * @throw   none
         **/
        config_exception(const config_exception &);

        /**
         * Operator overload= of config_exception class
         *
         * operator=(const config_exception&);
         *
         * @param   config_exception instance const to copy the config_exception
         * @throw   none
         **/
        config_exception& operator=(const config_exception &);

        /**
        * Destructor of config_exception class
        *
        * virtual ~config_exception() throw();
        *
        * @throw   none
        **/
        virtual ~config_exception() throw();

        /**
         * Public methode of config_exception
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
        config_webserv & _config;
    };


/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Protected methode of config_webserv class
 *
 * int get_max_events();
 *
 * @returns     int _max_events
 * @param       void
 */
    int get_max_events() const;

/**
 * Protected methode of config_webserv class
 *
 * int get_number_of_server();
 *
 * @returns     int _number_of_server
 * @param       void
 */
    int get_number_of_server() const;

/**
 * Protected methode of config_webserv class
 *
 * int get_vector_config_servers();
 *
 * @returns     int _vector_config_servers 0 is a localHost for debug
 * @param       void
 */
    std::vector<config_server> get_vector_config_servers() const;

/*>*******************************private section*********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    int                         _max_events;//default ngnix 1024
    int                         _number_of_server;
    std::vector<config_server>  _vector_config_servers;//server 0 is local host debug

};

#endif //WEBSERV_CONFIG_WEBSERV_HPP