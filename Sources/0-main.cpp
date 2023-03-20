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
void handle(int sig){

}
int main(int argc, char **argv, char **envp){
    try{
        if(argc == 2)
            init(argv[1]);//parse file
        else
            init("config_files/default");//parse default file
//        for (int i = 0; i < Webserv()->_nb_server; ++i) {
//            Webserv()->_server[i].launcher(Webserv()->_server[i].getServerFd(),
//                                           (sockaddr *)&Webserv()->_server[i].getAddress(),
//                                           (socklen_t*)&Webserv()->_server[i].getAddrlen());
//        }
//        for (int i = 0; i < Webserv()->_nb_server; ++i)
//            wait(NULL);
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    /*see if try catch to do*/
    std::cout <<"fin "<< std::endl;
    exit(EXIT_SUCCESS);
}

