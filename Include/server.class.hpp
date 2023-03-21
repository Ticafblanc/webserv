/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:47:07 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/17 14:47:10 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_SERVER_HPP
# define WEBSERV_SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
//#include <string.h>
//#include <sys/types.h>
//#include <fcntl.h>
//#include <sys/sendfile.h>
//#include <sys/stat.h>

//#include <sys/types.h>
//#include <sys/uio.h>


class server {

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/
private:// see if to switch const
    int id_server;
    pid_t pid;
    int server_fd;
    int new_socket;
    size_t addr_len;
    struct sockaddr_in address;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:
    server();

    server(const int id, const char * ip_address, const int port, const int domain, const int type, const int protocol, const int backlog);

    ~server();

    server(const server& other);

    server& operator=(const server& rhs);


/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/
    class socket_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class arg_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class bind_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class listen_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class accept_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

int& getIdServer();

pid_t getPid() const;

int& getServerFd();

int& getNewSocket();

sockaddr_in& getAddress();

size_t& getAddrlen();

void setIdServer(int idServer);

//      https://man7.org/linux/man-pages/man2/socket.2.html
//    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
//    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
//    raw_socket = socket(AF_INET, SOCK_RAW, protocol);
void set_socket(int domain, int type, int protocol);

//      https://linux.die.net/man/3/inet_addr
//      https://linux.die.net/man/3/htons
//    struct sockaddr_in {
//        sa_family_t    sin_family; /* address family: AF_INET */
//        in_port_t      sin_port;   /* port in network byte order */
//        struct in_addr sin_addr;   /* internet address */
//    };
//
//    /* Internet address */
//    struct in_addr {
//        uint32_t       s_addr;     /* address in network byte order */
//    };
void set_address(const int domain, const char * ip_address, const int port);

//      https://man7.org/linux/man-pages/man2/bind.2.html
void set_bind(const int sockfd, struct sockaddr *addr, const size_t size);

//    https://man7.org/linux/man-pages/man2/listen.2.html
void set_listen(const int sockfd, const int backlog) ;

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

//    https://man7.org/linux/man-pages/man2/accept.2.html
int launcher(const int sockfd, struct sockaddr* addr, socklen_t* addrlen);

/*
*====================================================================================
*|                                      signal                                      |
*====================================================================================
*/

static void handle(int sig) ;
};



#endif //WEBSERV_SERVER_HPP
