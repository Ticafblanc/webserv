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

#include "data_server.class.hpp"
#include "header.hpp"
#include <poll.h>

#define MAX_EVENTS 100

class server{

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/
private:// see if to switch const

    enum { nbr_clients, server_fd, epoll_fd};

    data_server data;
    std::vector<int> i_arg;
    std::vector<std::string> s_arg;
    struct epoll_event event, events[MAX_EVENTS];



/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:

    server();

    server(data_server &instance);

    ~server();

    server(const server& other);

    server& operator=(const server& rhs);


/*
*====================================================================================
*|                                  Member Exception                                 |
*====================================================================================
*/

public:

    class socket_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class socketopt_exception: public std::exception
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

    class launch_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

    class epoll_exception: public std::exception
    {
    public:
        const char * what() const throw();
    };

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/

public:

    data_server getDataServer() const;
    void setDataServer(data_server& d);

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

public:

//    https://man7.org/linux/man-pages/man2/accept.2.html
    void launcher();

/*
*====================================================================================
*|                                      signal                                      |
*====================================================================================
*/

private:

    void handle(int sig);

/*
*====================================================================================
*|                                  private fonction utils                          |
*====================================================================================
*/

private:

/* set socket
 * if process fail throw server::socket_exception();
 * https://man7.org/linux/man-pages/man2/socket.2.html
 * tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 * udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 * raw_socket = socket(AF_INET, SOCK_RAW, protocol);
 */
    void set_socket();
/*https://linux.die.net/man/3/setsockopt*/
    void set_sockoption();

/* https://man7.org/linux/man-pages/man2/bind.2.html*/
    void set_bind();

/*https://man7.org/linux/man-pages/man2/listen.2.html*/
    void set_listen();

/*set fnctl like subject fcntl(fd, F_SETFL, O_NONBLOCK)*/
    void set_server_non_blocking();
/*create an instance of epoll*/
    void create_epoll();

/*set fds for news client for server socket*/
    void set_epoll_socket();

/*registe  or throw exeptiom*/
    void set_epoll_ctl();

/*wait un event in request connect or sockert already open or throw exeptiom*/
    void set_epoll_wait();
};


#endif //WEBSERV_SERVER_HPP