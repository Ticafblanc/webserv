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
    std::vector<server> vec(4);
    std::vector<data_server>::iterator It = data.begin();
    std::vector<server>::iterator Vt = vec.begin();
    It = data.begin();
    for (; Vt != vec.end(); ++Vt, ++It){
        Vt->setDataServer(*It);
        // std::cout << "coucou" << std::endl;
    }
    return vec;
}
