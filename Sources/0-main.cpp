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

#include "../Include/0-webserv.hpp"

int main(int argc, char **argv, char **envp){
    Webserv();
    init("sdfs");
//    try{
//        if(argc == 2)
//            init(argv[1]);//parse file
//        else
//            init("config_files/default");//parse default file
//    }
//    catch(const std::exception& e){
//        std::cout << e.what() << " error" << std::endl;
//        exit(EXIT_FAILURE);
//    }
    /*see if try catch to do*/
    std::cout << Webserv()->_server.size() << std::endl;
    exit(EXIT_SUCCESS);
}

