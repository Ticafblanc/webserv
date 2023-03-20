/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-init.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:11:48 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/03 15:11:50 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/0-webserv.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

t_webserv* Webserv(){
    static t_webserv cw;
    return (&cw);
}

void init(std::string str){
    int fds = socket(AF_INET, SOCK_STREAM, 0);
    if (fds == 0)
        throw server::socket_exception();
    (void)str;//to start parsing =>>
    //test to run during wait parsing
    std::cout << "create void class and add arg after and insert in vector x 2" << std::endl;
    server serv;
    serv.setIdServer(1);
    serv.set_socket(AF_INET, SOCK_STREAM, 0);//set sochet
    serv.set_address(AF_INET, "127.0.0.1", 8081);// set address struct
    serv.set_bind(serv.getServerFd(), (sockaddr *)&serv.getAddress(),serv.getAddrlen());//set bind
    serv.set_listen(serv.getServerFd(), 10);//set listen
    Webserv()->_server.push_back(serv);

    server serv1;
    serv1.setIdServer(2);
    serv1.set_socket(AF_INET, SOCK_STREAM, 0);//set sochet
    serv1.set_address(AF_INET, "127.0.0.1", 8082);// set address struct
    serv1.set_bind(serv1.getServerFd(), (sockaddr *)&serv1.getAddress(),serv1.getAddrlen());//set bind
    serv1.set_listen(serv1.getServerFd(), 10);//set listen
    Webserv()->_server.push_back(serv1);

    std::cout << "create class with arg x 2" << std::endl;
    Webserv()->_server.push_back(server(4, "127.0.0.1", 4242, AF_INET, SOCK_STREAM, 0, 10));

    Webserv()->_server.push_back(server(4, "127.0.0.1", 4243, AF_INET, SOCK_STREAM, 0, 10));
    std::cout << "size of vector = " <<Webserv()->_server.size() << std::endl;
}