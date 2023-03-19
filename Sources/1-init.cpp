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
    (void)str;
    //build 4 server for test during wait parsing
    t_webserv *cw = Webserv();
    std::cout << "Hello" << std::endl;
    struct sockaddr_in address[4];
    for (int i = 0; i < Webserv()->_nb_server; ++i) {
        address[i].sin_family = AF_INET;
        address[i].sin_addr.s_addr = inet_addr("127.0.0.1");
        address[i].sin_port = htons( 8081 );
        memset(address[i].sin_zero, '\0', sizeof address[i].sin_zero);
        Webserv()->_server.push_back(server(socket(AF_INET, SOCK_STREAM, 0), address[i]));
        std::cout<< "coucou = "<< cw->_server.size() << std::endl;
    }
    std::cout << "test" <<std::endl;

//    throw std::exception();
}