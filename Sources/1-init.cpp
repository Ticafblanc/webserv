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
    if (!cw.init)
    {
        cw.init = 1;
        cw.nb_serv = 2;
        cw.serv = new server *;
        for (int i = 0; i < cw.nb_serv; ++i) {
            cw.serv[i] = new server;
        }
    }
    return (&cw);
}

void init(std::string str){
    (void)str;
    Webserv();
//    throw std::exception();
}