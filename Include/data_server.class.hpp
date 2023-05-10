/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_server.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WEBSERV_DATA_SERVER_HPP
#define WEBSERV_DATA_SERVER_HPP

#include <Include/header.hpp>

class data_address{

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of data_address class
 *
 * data_address();
 *
 * @param   void
 * @throw   none
 **/
    data_address(const std::string ip_address, const int port);

/**
* Destructor of data_address class
*
* ~data_address();
*
* @throw   none
**/
    ~data_address();

/**
* Constructor of data_address class
*
* data_address(const data_address& other);
*
* @param   void
* @throw   none
**/
    data_address(const data_address& other);

/**
 * Constructor of data_address class
 *
 * data_address& operator=(const data_address& rhs);
 *
 * @returns     data_address&
 * @param       const data_address&
 * @throw       none
 */
    data_address& operator=(const data_address& rhs);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of data_address class
 *
 * std::string& get_ip_address(int position);
 *
 * @returns     string& contain ip address of server
 * @param       position int is a position of variable in vector<std::string> table,
 *              represente the one of ip address of server
 * @throw       data_address_exception out of range
 */

    std::string &get_ip_address(int);

/**
 * Public methode of data_address class
 *
 * std::string& get_sock_address(int position);
 *
 * @returns     struct sockaddr& contain struct sockaddr of server
 * @param       position int is a position of variable in vector<struct sockaddr> table,
 *              represente the one of struct sockaddr of server
 * @throw       data_exception out of rang
 */
    struct sockaddr &get_sock_address();

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    const std::string       _ip_address;
    const int               _port;
    const int               _protocol;
    const struct sockaddr   _sock_address;
};

class config_server {

/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_server class
 *
 * config_server();
 *
 * @param   void
 * @throw   none
 **/
    config_server();

/**
* Destructor of config_server class
*
* ~config_server();
*
* @throw   none
**/
    ~config_server();

/**
* Constructor of config_server class
*
* config_server(const config_server& other);
*
* @param   void
* @throw   none
**/
    config_server(const config_server& other);

/**
 * Constructor of config_server class
 *
 * config_server& operator=(const config_server& rhs);
 *
 * @returns     config_server&
 * @param       const config_server&
 * @throw       none
 */
    config_server& operator=(const config_server& rhs);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of config_server class
 *
 * std::string& get_server_name(int position);
 *
 * @returns     string& contain name of server
 * @param       position int is a position of variable in vector<std::string> table,
 *              represente the one of name of server
 * @throw       data_exception out of rang
 */
    std::string &get_server_name(int);


/**
 * Public methode of config_server class
 *
 * void set_server_name(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       data_exception if name already exist
 */
    void add_server_name(std::string &);

/**
 * Public methode of config_server class
 *
 * std::string& get_ip_address(int position);
 *
 * @returns     string& contain ip address of server
 * @param       position int is a position of variable in vector<std::string> table,
 *              represente the one of ip address of server
 * @throw       data_exception out of rang
 */
    std::string &get_ip_address(int);


/**
 * Public methode of config_server class
 *
 * void set_ip_address(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain ip address of server to add
 * @throw       data_exception if name already exist
 */
    void add_ip_address(std::string &);

/**
 * Public methode of config_server class
 *
 * std::string& get_ip_address(int position);
 *
 * @returns     struct sockaddr& contain struct sockaddr of server
 * @param       position int is a position of variable in vector<struct sockaddr> table,
 *              represente the one of struct sockaddr of server
 * @throw       data_exception out of rang
 */
    struct sockaddr &get_sock_address(int);


/**
 * Public methode of config_server class
 *
 * void set_ip_address(std::string & ip_address);
 *
 * @returns     void
 * @param       ip_address is an std::string contain ip address of server to
 *              build struct sockaddr and add to vector
 * @throw       data_exception if name already exist
 */
    void add_sock_address(std::string &);

/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/
    std::vector<data_address>       _vector_sock_address;
    std::vector<std::string>        _vector_server_name;
    int                             _backlog;//SOMAXCONN
};

class data_server{

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
    data_server();

/**
* Destructor of data_sever_base class
*
* ~data_sever_base();
*
* @throw   none
**/
    ~data_server();

/**
* Constructor of data_sever_base class
*
* data_sever_base(const data_server& other);
*
* @param   void
* @throw   none
**/
    data_server(const data_server& other);

/**
* Constructor of data_sever_base class
*
* data_server& operator=(const data_server& rhs);
*
* @throw   none
**/
    data_server& operator=(const data_server& rhs);


/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

/**
 * Class exception of data_server class
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
 * Protected methode of data_server class
 *
 * int& get_int_data(int position);
 *
 * @returns     int&
 * @param       position int is a position of variable in vector<int> table
 * @throw       data_exception out of rang
 */
    int& get_int_data(int);



/**
 * Protected methode of data_server class
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
 * Protected methode of data_server class
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
 * Protected methode of data_server class
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
 * Protected methode of data_server class
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


/*>*******************************private section**********************************/

private:

/*
*====================================================================================
*|                                     Member                                       |
*====================================================================================
*/

    enum{number_of_servers, type, protocol, port,
        backlog,max_events};

    std::vector<int>            _vector_int_data;
    std::vector<config_server>  _vector_config_servers;
    int                         _max_events;

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

};


#endif //WEBSERV_DATA_SERVER_HPP