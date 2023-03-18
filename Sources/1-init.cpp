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
    if (!cw._init)
    {
        cw._init = 1;
        cw._server();
    }
    return (&cw);
}

void init(std::string str){
    (void)str;
    //build 4 server for test during wait parsing
    for (int i = 0; i < 4; ++i) {
        Webserv()->_server.push_back(server(pid_t &, socket(AF_INET, SOCK_STREAM, 0)))

    }

//    throw std::exception();
}