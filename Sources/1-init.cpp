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

t_webserv* Webserv(){
    static t_webserv cw;
    return (&cw);
}

void init(std::string str){
    (void)str;//to start parsing =>>
    //test to run during wait parsing
    struct sockaddr_in address;

    std::cout << "create void class and add arg after and insert in vector" << std::endl;
    Webserv()->_server.push_back(server());//create void
    Webserv()->_server[0].setIdServer(0);//set id server
    Webserv()->_server[0].set_socket(AF_INET, SOCK_STREAM, 0);//set sochet
    Webserv()->_server[0].set_address(AF_INET, "127.0.0.1", 8081);// set address struct
    Webserv()->_server[0].set_bind(Webserv()->_server[0].getServerFd(), (sockaddr *)&Webserv()->_server[0].getAddress(), Webserv()->_server[0].getAddrlen());//set bind
    Webserv()->_server[0].set_listen(Webserv()->_server[0].getServerFd(), 10);//set listen

    Webserv()->_server.push_back(server());//create void
    Webserv()->_server[1].setIdServer(1);//set id server
    Webserv()->_server[1].set_socket(AF_INET, SOCK_STREAM, 0);//set sochet
    Webserv()->_server[1].set_address(AF_INET, "127.0.0.1", 8082);// set address struct
    Webserv()->_server[1].set_bind(Webserv()->_server[1].getServerFd(), (sockaddr *) &Webserv()->_server[1].getAddress(), Webserv()->_server[1].getAddrlen());//set bind
    Webserv()->_server[1].set_listen(Webserv()->_server[1].getServerFd(), 10);//set listen

    std::cout << "create class with arg" << std::endl;
    Webserv()->_server.push_back(server(2, "127.0.0.1", 4242, AF_INET, SOCK_STREAM, 0, 10));

    Webserv()->_server.push_back(server(3, "127.0.0.1", 4243, AF_INET, SOCK_STREAM, 0, 10));
    std::cout << "test = " << Webserv()->_server.size() << std::endl;
}