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
<<<<<<< HEAD:Include/webserv.hpp
=======

extern char** environ;

#pragma once
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
//#include <sys/sendfile.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#define PORT 8081

>>>>>>> Matthis:Doc/learn/mini_sever/Include/webserv.hpp
#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include <iostream>
# include <string>
# include <vector>
# include "Parser.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

#endif //WEBSERV_HPP
