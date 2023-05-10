//
// Created by Matthis Doquocbao on 5/10/23.
//

#ifndef WEBSERVER_CONFIG_SERVER_CLASS_HPP
#define WEBSERVER_CONFIG_SERVER_CLASS_HPP


class config_server {
/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_server.class class
 *
 * config_server.class();
 *
 * @param   void
 * @throw   none
 **/
    config_server();

/**
* Destructor of config_server.class class
*
* config_server.class.class();
*
* @throw   none
**/
    ~config_server();

/**
* Constructor of config_server.class class
*
* config_server.class(const config_server.class& other);
*
* @param   void
* @throw   none
**/
    config_server(const config_server& other);

/**
 * Constructor of config_server.class class
 *
 * config_server.class& operator=(const config_server.class& rhs);
 *
 * @returns     config_server.class&
 * @param       const config_server.class&
 * @throw       none
 */
    config_server& operator=(const config_server& rhs);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of config_server.class class
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
 * Public methode of config_server.class class
 *
 * void set_server_name(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain name of server to add
 * @throw       data_exception if name already exist
 */
    void add_server_name(std::string &);

/**
 * Public methode of config_server.class class
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
 * Public methode of config_server.class class
 *
 * void set_ip_address(std::string & name);
 *
 * @returns     void
 * @param       name is an std::string contain ip address of server to add
 * @throw       data_exception if name already exist
 */
    void add_ip_address(std::string &);

/**
 * Public methode of config_server.class class
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
 * Public methode of config_server.class class
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
    std::vector<config_address>       _vector_sock_address;
    std::vector<std::string>        _vector_server_name;
    int                             _backlog;//SOMAXCONN

};


#endif //WEBSERVER_CONFIG_SERVER_CLASS_HPP
