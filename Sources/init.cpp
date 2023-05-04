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

std::vector<server> init(string str){
    Parser parser(str.c_str());
    vector<data_server> data = parser.get_data();
    std::vector<server> vec(data.size());
    std::vector<data_server>::iterator It = data.begin();
    std::vector<server>::iterator Vt = vec.begin();
    for (; It != data.end(); Vt++, It++){
        It->setDomain(AF_INET);
        It->setType(SOCK_STREAM);
        It->setProtocol(0);
        It->setBacklog(10);
        It->setAddress();
        It->setLevel(SOL_SOCKET);
        It->setOptionName(SO_REUSEADDR);
        It->setOptionVal(1);
        Vt->setDataServer(*It);
    }
    return vec;


}
