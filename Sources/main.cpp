/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossign <jrossign@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:57:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/05/08 14:36:31 by jrossign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/webserv.hpp"

int main(int argc, char **argv, char **envp){
    (void)envp;
    std::vector<server> vec;
    try{
        if(argc == 2)
            vec = init(argv[1]);
        else
            vec = init("/usr/local/etc/webserv/webserv.conf");//parse default file
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
