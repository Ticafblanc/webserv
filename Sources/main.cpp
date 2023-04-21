/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-main.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:57:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 18:57:57 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/webserv.hpp"

int main(int argc, char **argv, char **envp){
    (void)envp;
    std::vector<server> vec;
    try{
        if(argc == 2) {
            Parser parser(argv[1]);
            vec = init(parser.get_data());
        }
        else {
            std::string def("../user->local");
            Parser parser(def.c_str());
            vec = init(parser.get_data());
        }
        std::vector<server>::iterator It = vec.begin();
        for (; It != vec.end(); ++It){
            It->launcher();
        }
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        std::cout <<"end failure"<< std::endl;
        exit(EXIT_FAILURE);
    }
    /*see if try catch to do*/
    std::cout <<"end succes"<< std::endl;
    exit(EXIT_SUCCESS);
}

