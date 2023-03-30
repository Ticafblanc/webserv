//
// Created by Matthis DoQuocBao on 2023-03-27.
//

#ifndef WEBSERV_DATA_SERVER_HPP
#define WEBSERV_DATA_SERVER_HPP

#include "webserv.hpp"
#include "Route.hpp"

class data_server{
/*
*====================================================================================
*|                                     Public Member                                |
*====================================================================================
*/

public:

    enum{ id_server, port, domain, type, protocol,
            backlog, server_fd, new_socket, };
    enum{ server_name, ip_address, };

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/

private:

    vector<int> i_data;
    vector<std::string> s_data;
    pid_t pid;//follow process see if ok
    std::size_t addr_len;
    struct sockaddr_in address;
    string server_name;
	unsigned int port;
	string host;
	vector<string> default_error_pages;
	vector<string> route;

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
    void setServer_name(std::string &);

    std::string& getIpAddress();
    void setIp_address(std::string &);

    int& getIdServer() ;
    void setIdServer(int );

    int& getPort();
    void setPort(int );

    int& getDomain();
    void setDomain(int );

    int& getType();
    void setType(int );

    int& getProtocol();
    void setProtocol(int );

    int&  getBacklog();
    void setBacklog(int );

    int& getServerFd();
    void setServerFd(int );

    int& getNewSocket();
    void setNewSocket(int );

    sockaddr_in& getAddress();
    void setAddress(int domain, const std::string& ip_address, int port);
    void setAddress();

    size_t& getAddrlen() ;
    void setAddrlen(std::size_t &);

    pid_t& getPid();
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
