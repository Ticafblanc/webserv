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
//#include <sys/socket.h>
#include <netinet/in.h>
//#include <string.h>
//#include <sys/types.h>
//#include <fcntl.h>
//#include <sys/sendfile.h>
//#include <sys/stat.h>
//#include <errno.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/uio.h>


class server {

/*
*====================================================================================
*|                                     Private Member                               |
*====================================================================================
*/
private:
    pid_t pid;
    int server_fd;
    int new_socket;
    struct sockaddr_in address;

/*
*====================================================================================
*|                                  Member Fonction                                 |
*====================================================================================
*/

public:
    server();

    server(int server_fd_, struct sockaddr_in& address_);

    ~server();

    server(const server& other);

    server& operator=(const server& rhs);

/*
*====================================================================================
*|                                  Element access                                 |
*====================================================================================
*/



};


#endif //WEBSERV_SERVER_HPP
