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
#ifndef WEBSERV_HPP
# define WEBSERV_HPP
# include "header.hpp"
extern char** environ;

/*
*====================================================================================
*|                                         std headers                              |
*====================================================================================
*/


/*
*====================================================================================
*|                                         class                                    |
*====================================================================================
*/
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
