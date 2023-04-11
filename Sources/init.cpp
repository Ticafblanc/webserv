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

#include "../Include/webserv.hpp"

std::vector<server> init(std::string str){
    (void)str;
    std::vector<server> vec(4);
    std::vector<data_server> data(4);
    std::vector<data_server>::iterator It = data.begin();
    std::string ip =  "127.0.0.1";
    int port = 8081;
    for (int i = 0; It != data.end(); ++It, ++i, ++port) {
        It->setIdServer(i);
        It->setIp_address(ip);
        It->setPort(port);
        It->setDomain(AF_INET);
        It->setType(SOCK_STREAM);
        It->setProtocol(0);
        It->setBacklog(10);
        It->setAddress();
        It->setLevel(SOL_SOCKET);
        It->setOptionName(SO_REUSEADDR);
        It->setOptionVal(1);
        // std::cout << i << std::endl;
    }
    std::vector<server>::iterator Vt = vec.begin();
    It = data.begin();
    for (; Vt != vec.end(); ++Vt, ++It){
        Vt->setDataServer(*It);
        // std::cout << "coucou" << std::endl;
    }
    return vec;
}
