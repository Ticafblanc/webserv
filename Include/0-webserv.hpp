/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:23:33 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 16:23:37 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char** environ;

#pragma once

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/*
*====================================================================================
*|                                         std headers                              |
*====================================================================================
*/

#include "server.class.hpp"
#include "Parser.hpp"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fstream>
#include <exception>

#ifdef __linux__
# include <sendfile.h>
#else
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
#endif

using std::string;
using std::vector;
using std::exception;
using std::cout;
using std::cerr;

/*
*====================================================================================
*|                                         class                                    |
*====================================================================================
*/

#include "server.class.hpp"//buidl and manage server

typedef struct webserv_content{
   webserv_content() : _nb_server(4), _server(){};
   int _nb_server;
   std::vector<server> _server;
} t_webserv;

/*init webserve (parsing and preliminary check)*/
t_webserv* Webserv(void);//singleton is main on acces to data to fill during de parsing and use after
std::vector<server> init(std::string str);//main init .... paring to do

/*launch server web*/

/*manage server*/


#endif //WEBSERV_HPP
