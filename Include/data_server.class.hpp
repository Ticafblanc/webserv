//
// Created by Matthis DoQuocBao on 2023-03-27.
//

#pragma once

#ifndef WEBSERV_DATA_SERVER_HPP
#define WEBSERV_DATA_SERVER_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include <unistd.h>

class data_server{
/*
*====================================================================================
*|                                     Public Member                                |
*====================================================================================
*/

public:

    enum{ id_server, port, domain, type, protocol,
            backlog, server_fd, new_socket, level,
            optionname, optionval,};
    enum{ server_name, ip_address, };

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/

private:

    std::vector<int> i_data;
    std::vector<std::string> s_data;
    pid_t pid;//follow process see if ok
    std::size_t addr_len;
    struct sockaddr_in address;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:

    data_server();
    ~data_server();
    data_server(const data_server& other);
    data_server& operator=(const data_server& rhs);

/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

public:

    class data_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class arg_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

/*
 * https://linux.die.net/man/3/inet_addr
 * https://linux.die.net/man/3/htons
 * struct sockaddr_in {
 *      sa_family_t    sin_family;address family: AF_INET
 *      in_port_t      sin_port;   port in network byte order
 *      struct in_addr sin_addr;   internet address
 *      };
 *
 * Internet address
 * struct in_addr {
 *      uint32_t       s_addr;     address in network byte order
 *      };
 *
 * https://man7.org/linux/man-pages/man2/socket.2.html
 * tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = socket(AF_INET, SOCK_RAW, protocol);
*/

public:

    std::vector<int>& getIData();
    std::vector<std::string>& getSData();

    std::string& getServerName();
    /*set name of server*/
    void setServer_name(std::string &);

    std::string& getIpAddress();
    /*set Ip address */
    void setIp_address(std::string &);

    int& getIdServer();
    /* number of server first server = 0 and last = (nbr server-1)*/
    void setIdServer(int );

    int& getPort();
    /*number of port t follow*/
    void setPort(int );

    int& getDomain();
    /* number of Domain always AF_INET when TCP or User Datagram Protocol (UDP)*/
    void setDomain(int );

    int& getType();
    /*set type SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW, SOCK_RDM, SOCK_PACKET
     * for service tcp => SOCK_STREAM*/
    void setType(int );

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

    int& getLevel();
    /*set level for soc option to SOL_SOCKET and  we will see */
    void setLevel(int);

    int& getOptionName();
    /*set option_name for soc option to SO_REUSEADDR on mac and  SO_REUSEADDR|SO_REUSEPORT on linux */
    void setOptionName(int);

    int& getOptionVal();
    /*set option_Value for soc option to 0 or 1 */
    void setOptionVal(int);

    pid_t& getPid();
    /*store pid of process*/
    void setPid(pid_t &);

    void close_server_fd();

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

private:
/*check if file descriptor is open
 * if process fail throw server::socket_exception();
 */
    int fd_isopen();

/*check if socket  is open
 * if process fail throw server::socket_exception();
 */
    int socket_isopen();
};


#endif //WEBSERV_DATA_SERVER_HPP
