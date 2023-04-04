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

#include "header.hpp"
#include "data_server.class.hpp"
#include <poll.h>
#include <ostream>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

class server{

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/
private:// see if to switch const

    enum { nbr_events,};

    data_server data;
    std::vector<int> i_arg;
    std::vector<std::string> s_arg;
    struct epoll_event i_epoll, t_epoll[MAX_EVENTS];




/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:

    server();

    server(data_server &);

    ~server();

    server(const server& other);

    server(const data_server &data, const vector<int> &iArg, const vector<std::string> &sArg, const epoll_event &iEpoll,
           epoll_event *tEpoll);

    friend std::ostream &operator<<(std::ostream &os, const server &server);

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
    void set_server_non_blocking(int fd);

/*set epoll table  for client for server socket*/
    void set_t_epoll(int fd);
/*create new epoll event instance or throw exeptiom*/
    void create_epoll();
/*get flag store in socket after poll*/
    int get_flag(int fd);

};


#endif //WEBSERV_SERVER_HPP
