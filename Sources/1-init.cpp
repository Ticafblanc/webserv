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
    std::vector<server> *serv = &Webserv()->_server;
    std::cout << "create void class and add arg after and insert in vector x 2" << std::endl;serv->push_back(server());//create void
   serv->at(0).setIdServer(0);//set id server
   serv->at(0).set_socket(AF_INET, SOCK_STREAM, 0);//set sochet
   serv->at(0).set_address(AF_INET, "127.0.0.1", 8080);// set address struct
   serv->at(0).set_bind(serv->at(0).getServerFd(), (sockaddr *)&serv->at(0).getAddress(),serv->at(0).getAddrlen());//set bind
   serv->at(0).set_listen(serv->at(0).getServerFd(), 10);//set listen

   serv->push_back(server());//create void
   serv->at(1).setIdServer(1);//set id server
   serv->at(1).set_socket(AF_INET, SOCK_STREAM, 0);//set sochet
   serv->at(1).set_address(AF_INET, "127.0.0.1", 8082);// set address struct
   serv->at(1).set_bind(serv->at(1).getServerFd(), (sockaddr *)&serv->at(1).getAddress(),serv->at(1).getAddrlen());//set bind
   serv->at(1).set_listen(serv->at(1).getServerFd(), 10);//set listen
    std::cout << "create class with arg x 2" << std::endl;
   serv->push_back(server(2, "127.0.0.1", 4242, AF_INET, SOCK_STREAM, 0, 10));

   serv->push_back(server(3, "127.0.0.1", 4243, AF_INET, SOCK_STREAM, 0, 10));
    std::cout << "size of vector = " <<serv->size() << std::endl;
}