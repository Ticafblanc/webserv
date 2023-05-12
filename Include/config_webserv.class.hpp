///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   config_webserv.class.hpp                           :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
///*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
///*                                                                            */
///* ************************************************************************** */
//#ifndef WEBSERV_CONFIG_WEBSERV_HPP
//#define WEBSERV_CONFIG_WEBSERV_HPP
//
//#include <Include/header.hpp>
//
//struct config_webserv;
//
//struct config_server {
//
///*>********************************public section**********************************/
//
//public:
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
//
///**
// * Constructor of config_server.class class
// *
// * config_server.class();
// *
// * @param   void
// * @throw   none
// **/
//    config_server(std::ifstream &file, config_webserv& webserv);
//
///**
//* Destructor of config_server.class class
//*
//* config_server.class.class();
//*
//* @throw   none
//**/
//    ~config_server();
//
///**
//* Constructor of config_server.class class
//*
//* config_server.class(const config_server.class& other);
//*
//* @param   void
//* @throw   none
//**/
//    config_server(const config_server& other);
//
///**
// * Constructor of config_server.class class
// *
// * config_server.class& operator=(const config_server.class& rhs);
// *
// * @returns     config_server.class&
// * @param       const config_server.class&
// * @throw       none
// */
//    config_server& operator=(const config_server& rhs);
//
///*
//*====================================================================================
//*|                                  Member Exception                                 |
//*====================================================================================
//*/
//
///**
// * Class exception of config_server class
// *
// * class config_exception;
// *
// * @inherit std::exception
// **/
//    class config_exception: public std::exception
//    {
//    public:
//
//        /**
//         * Constructor of config_exception class
//         *
//         * config_exception(config_server & config, const char* message);
//         *
//         * @param   config_server is a config_server reference to set the private _config
//         *          to manage the close of config_server class
//         *          message to store const char*
//         * @throw   none
//         **/
//        config_exception(config_server&, const char *);
//
//        /**
//         * Copy constructor of config_exception class
//         *
//         * config_exception(config_exception &);
//         *
//         * @param   config_exception instance to build the config_exception
//         * @throw   none
//         **/
//        config_exception(const config_exception &);
//
//        /**
//         * Operator overload= of config_exception class
//         *
//         * operator=(const config_exception&);
//         *
//         * @param   config_exception instance const to copy the config_exception
//         * @throw   none
//         **/
//        config_exception& operator=(const config_exception &);
//
//        /**
//        * Destructor of config_exception class
//        *
//        * virtual ~config_exception() throw();
//        *
//        * @throw   none
//        **/
//        virtual ~config_exception() throw();
//
//        /**
//         * Public methode of config_exception
//         *
//         * virtual const char * what() const throw();
//         *
//         * @returns  const char * store in private std::string _message
//         *          at the construction defaut constructor "socket error"
//         * @param   void
//         * @throw   none
//         **/
//        virtual const char * what() const throw();
//
//    private:
//        std::string     _message;
//        config_server & _config;
//    };
//
//
///*
//*====================================================================================
//*|                                  Element access                                 |
//*====================================================================================
//*/
//
///**
// * Public methode of config_server.class class
// *
// * std::vector<std::string> &get_vector_server_name() const;
// *
// * @returns     std::vector<std::string>& contain all names of server
// * @param       void
// * @throw       none
// */
//    std::vector<std::string> &get_vector_server_name() const;
//
//
///**
// * Public methode of config_server.class class
// *
// * void set_vector_server_name(std::string & name);
// *
// * @returns     void
// * @param       name is an std::string contain name of server to add
// * @throw       config_exception if name already exist
// */
//    void add_vector_server_name(std::string &);
//
///**
// * Public methode of config_server.class class
// *
// * std::string& get_ip_address();
// *
// * @returns     std::vector<std::string>& contain all names of server
// * @param       void
// * @throw       config_exception out of rang
// */
//    std::vector<std::string>  &get_vector_sock_address() const;
//
//
///**
// * Public methode of config_server.class class
// *
// * void add_vector_sock_address(std::string ip_address, const int port);
// *
// * @returns     void
// * @param       ip_adress is a std::string with ip_address
// *              port is an int with port to add
// * @throw       config_exception if ip/port already exist in _webserv instance
// */
//    void add_vector_sock_address(std::string, const int );
//
///**
// * Public methode of config_server.class class
// *
// * int &get_backlog();
// *
// * @returns     int with the maximum number of pending connections
// * @param       void
// * @throw       none
// */
//    int &get_backlog();
//
//
///**
// * Public methode of config_server.class class
// *
// * void set_backlog(unsign int backlog);
// *
// * @returns     void
// * @param       backlog is an int contain the maximum number of pending connections
// * @throw       config_exception if
// */
//    void set_backlog(unsigned int);
//
///*>*******************************private section**********************************/
//
//private:
//
///*
//*====================================================================================
//*|                                     Member                                       |
//*====================================================================================
//*/
//    std::vector<std::string>        _vector_server_name;
//    std::vector<config_address>     _vector_sock_address;
//    unsigned int                    _backlog;//SOMAXCONN
//
//};
//
//
//
///*
//*==========================================================================================================
//*|                                                  Config Webserv                                        |
//*==========================================================================================================
//*/
//
//
//
//struct config_webserv{
//
///*>*******************************public section*********************************/
//
//public:
//
///*
//*====================================================================================
//*|                                  Member Fonction                                 |
//*====================================================================================
//*/
//
///**
// * Constructor of config_webserv class
// *
// * config_webserv(std::string path_config_file);
// *
// * @param   path_config_file is a std::string is a path to config file
// *          specified at start of webserv
// * @throw   config_webserv::config_exception
// **/
//    config_webserv(std::string path_config_file);
//
///**
//* Destructor of config_webserv class
//*
//* ~config_webserv();
//*
//* @throw   none
//**/
//    ~config_webserv();
//
///**
//* Constructor of config_webserv class
//*
//* config_webserv(const config_webserv& other);
//*
//* @param   void
//* @throw   none
//**/
//    config_webserv(const config_webserv& other);
//
///**
//* Operator = of config_webserv class
//*
//* config_webserv& operator=(const config_webserv& rhs);
//*
//* @throw   none
//**/
//    config_webserv& operator=(const config_webserv& rhs);
//
//
///*
//*====================================================================================
//*|                                  Member Exception                                 |
//*====================================================================================
//*/
//
///**
// * Class exception of config_webserv class
// *
// * class config_exception;
// *
// * @inherit std::exception
// **/
//    class config_exception: public std::exception
//    {
//    public:
//
//        /**
//         * Constructor of config_exception class
//         *
//         * config_exception(config_webserv & config, const char* message);
//         *
//         * @param   config_webserv is a config_webserv reference to set the private _config
//         *          to manage the close of config_webserv class
//         *          message to store const char*
//         * @throw   none
//         **/
//        config_exception(config_webserv&, const char *);
//
//        /**
//         * Copy constructor of config_exception class
//         *
//         * config_exception(config_exception &);
//         *
//         * @param   config_exception instance to build the config_exception
//         * @throw   none
//         **/
//        config_exception(const config_exception &);
//
//        /**
//         * Operator overload= of config_exception class
//         *
//         * operator=(const config_exception&);
//         *
//         * @param   config_exception instance const to copy the config_exception
//         * @throw   none
//         **/
//        config_exception& operator=(const config_exception &);
//
//        /**
//        * Destructor of config_exception class
//        *
//        * virtual ~config_exception() throw();
//        *
//        * @throw   none
//        **/
//        virtual ~config_exception() throw();
//
//        /**
//         * Public methode of config_exception
//         *
//         * virtual const char * what() const throw();
//         *
//         * @returns  const char * store in private std::string _message
//         *          at the construction defaut constructor "socket error"
//         * @param   void
//         * @throw   none
//         **/
//        virtual const char * what() const throw();
//
//    private:
//        std::string     _message;
//        config_webserv & _config;
//    };
//
///*
//*====================================================================================
//*|                                  Element access                                 |
//*====================================================================================
//*/
//
///**
// * Protected methode of config_webserv class
// *
// * int get_max_events();
// *
// * @returns     int _max_events
// * @param       void
// */
//    int get_max_events() const;
//
///**
// * Protected methode of config_webserv class
// *
// * int get_number_of_server();
// *
// * @returns     int _number_of_server
// * @param       void
// */
//    int get_number_of_server() const;
//
///**
// * Protected methode of config_webserv class
// *
// * int get_vector_config_servers();
// *
// * @returns     int _vector_config_servers 0 is a localHost for debug
// * @param       void
// */
//    std::vector<config_server> get_vector_config_servers() const;
//
///*>*******************************private section*********************************/
//
//private:
//
///*
//*====================================================================================
//*|                                     Member                                       |
//*====================================================================================
//*/
//
//    int                                                     _max_events;//default ngnix 1024
//    int                                                     _number_of_server;
//    std::vector<config_server>                              _vector_config_servers;//server 0 is local host debug
//    std::vector<std::pair<unsigned int, unsigned short > >  _ip_port_list;//to list of ip and port combinaison
//
//};
//
//#endif //WEBSERV_CONFIG_WEBSERV_HPP