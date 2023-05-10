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

struct config_webserv{

/*>*******************************public section*********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of data_sever_base class
 *
 * data_sever_base();
 *
 * @param   void
 * @throw   none
 **/
    config_webserv();

/**
* Destructor of data_sever_base class
*
* ~data_sever_base();
*
* @throw   none
**/
    ~config_webserv();

/**
* Constructor of data_sever_base class
*
* data_sever_base(const config_webserv& other);
*
* @param   void
* @throw   none
**/
    config_webserv(const config_webserv& other);

/**
* Constructor of data_sever_base class
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
 * class data_exception;
 *
 * @inherit std::exception
 **/
    class data_exception: public std::exception
    {
    public:
        /**
         * Constructor of data_exception class
         *
         * data_exception();
         *
         * @param   void
         * @throw   none
         **/
        data_exception();

        /**
         * Constructor of data_exception class
         *
         * data_exception(const char*);
         *
         * @param   exception message to store const char*
         * @throw   none
         **/
        data_exception(const char *);

        /**
         * Copy constructor of data_exception class
         *
         * data_exception(data_exception &);
         *
         * @param   data_exception instance to build the data_exception
         * @throw   none
         **/
        data_exception(const data_exception &);

        /**
         * Operator overload= of data_exception class
         *
         * operator=(const data_exception&);
         *
         * @param   data_exception instance const to copy the data_exception
         * @throw   none
         **/
        data_exception& operator=(const data_exception &);

        /**
        * Destructor of data_exception class
        *
        * virtual ~data_exception() throw();
        *
        * @throw   none
        **/
        virtual ~data_exception() throw();

        /**
         * Public methode of data_exception
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
        std::string _message;
    };


/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Protected methode of config_webserv class
 *
 * int& get_int_data(int position);
 *
 * @returns     int&
 * @param       position int is a position of variable in vector<int> table
 * @throw       data_exception out of rang
 */
    int& get_int_data(int);



/**
 * Protected methode of config_webserv class
 *
 * std::string& get_ip_address(int sever_number, int position);
 *
 * @returns     string& contain name of server
 * @param       sever_number is an int, he is the server number in std::vector<vector<std::string> >
 *              to acces liste of ip address for each server
 *
 *              position int is a position of variable in vector<std::string> table,
 *              represente the one of ip address of server
 * @throw       data_exception out of range
 */
    std::string& get_ip_address(int, int);

/**
 * Protected methode of config_webserv class
 *
 * void set_ip_address(int server_number, std::string & ip_address);
 *
 * @returns     void
 * @param       sever_number is an int, he is the server number in std::vector<vector<std::string> >
 *              to acces liste of name for each server
 *
 *              ip_address is an std::string contain ip address of server to add
 * @throw       data_exception if ip already exist
 */
    void add_ip_address(int, std::string &);

/**
 * Protected methode of config_webserv class
 *
 * int& get_Port(int sever_number, int position);
 *
 * @returns     int& contain the port to follow
 * @param       sever_number is an int, he is the server number in std::vector<vector<int> >
 *              to acces liste of ip address for each server
 *
 *              position int is a position of variable in vector<int> table,
 *              represente the one of port of server
 * @throw       data_exception out of range
 */
    int& get_Port(int, int);

/**
 * Protected methode of config_webserv class
 *
 * void add_Port(int server_number, int port);
 *
 * @returns     void
 * @param       sever_number is an int, he is the server number in std::vector<vector<std::string> >
 *              to acces liste of name for each server
 *
 *              port is an int contain port of server to add
 * @throw       data_exception if ip already exist
 */
    void add_Port(int, int);

    int& getProtocol();
    /*set protocol to 0*/
    void setProtocol(int );

    int&  getBacklog();
    /*set time to follow socket fd set at 10 for now*/
    void setBacklog(int );

    int& getServerFd();
    /*value of socket */
    void setServerFd(int );

    int& getNewSocket();
    /*set value of new socket after accpet*/
    void setNewSocket(int );

    sockaddr_in& getAddress();
    /*set struct sockaddr_in */
    void setAddress(int domain, const std::string& ip_address, int port);
    void setAddress(int dom, int por);
    void setAddress();

    size_t& getAddrlen() ;
    /*store size of struct sockaddr_in*/
    void setAddrlen(const std::size_t &);

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/




    std::vector<config_server>  vector_config_servers;
    int                         max_events;
    int                         number_of_server;

};


#endif //WEBSERV_CONFIG_WEBSERV_HPP