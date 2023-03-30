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

class server{

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/
private:// see if to switch const

    data_server data;

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

    data_server getDataServer() const;
    void setDataServer(data_server& d);

/*
*====================================================================================
*|                                      Launcher                                    |
*====================================================================================
*/

//    https://man7.org/linux/man-pages/man2/accept.2.html
    int launcher();

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

//      https://man7.org/linux/man-pages/man2/bind.2.html
    void set_bind();

//    https://man7.org/linux/man-pages/man2/listen.2.html
    void set_listen();

};



#endif //WEBSERV_SERVER_HPP
