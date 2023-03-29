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

//extern char** environ;

#pragma once

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/*
*====================================================================================
*|                                         std headers                              |
*====================================================================================
*/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "server.class.hpp"

/*
*====================================================================================
*|                                         class                                    |
*====================================================================================
*/

#include "server.class.hpp"//buidl and manage server

/*init webserve (parsing and preliminary check)*/
//t_webserv* Webserv(void);//singleton is main on acces to data to fill during de parsing and use after
std::vector<server> init(std::string str);//main init .... paring to do

/*launch server web*/

/*manage server*/


#endif //WEBSERV_HPP