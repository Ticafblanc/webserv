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
    char std::string = {"127.0.0.1"};

//    t_data_server data1(1, ip, 8081, AF_INET, SOCK_STREAM, 0, 10);
//    t_data_server data2(2, ip, 8082, AF_INET, SOCK_STREAM, 0, 10);
//    t_data_server data3(3, ip, 8083, AF_INET, SOCK_STREAM, 0, 10);
//    t_data_server data4(4, ip, 8084, AF_INET, SOCK_STREAM, 0, 10);
//    t_data_server data5(5, ip, 8085, AF_INET, SOCK_STREAM, 0, 10);
//    server ser1(data1);
//    server ser2(data2);
//    server ser3(data3);
//    server ser4(data4);
//    server ser5(data5);
}