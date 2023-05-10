//
// Created by Matthis Doquocbao on 5/10/23.
//

#ifndef WEBSERVER_CONFIG_ADDRESS_CLASS_HPP
#define WEBSERVER_CONFIG_ADDRESS_CLASS_HPP


class config_address {
/*>********************************public section**********************************/

public:

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

/**
 * Constructor of config_address.class class
 *
 * config_address.class();
 *
 * @param   void
 * @throw   none
 **/
    config_address(const std::string ip_address, const int port);

/**
* Destructor of config_address.class class
*
* config_address.class.class();
*
* @throw   none
**/
    ~config_address();

/**
* Constructor of config_address.class class
*
* config_address.class(const config_address.class& other);
*
* @param   void
* @throw   none
**/
    config_address(const config_address& other);

/**
 * Constructor of config_address.class class
 *
 * config_address.class& operator=(const config_address.class& rhs);
 *
 * @returns     config_address.class&
 * @param       const config_address.class&
 * @throw       none
 */
    config_address& operator=(const config_address& rhs);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/**
 * Public methode of config_address.class class
 *
 * std::string& get_ip_address(int position);
 *
 * @returns     string& contain ip address of server
 * @param       position int is a position of variable in vector<std::string> table,
 *              represente the one of ip address of server
 * @throw       config_address_exception out of range
 */

    std::string &get_ip_address(int);

/**
 * Public methode of config_address.class class
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
    int                     _server_socket;
    struct epoll_event      _event;

};


#endif //WEBSERVER_CONFIG_ADDRESS_CLASS_HPP
