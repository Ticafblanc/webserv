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
        std::vector<server> serv =  Webserv()->_server;
        for (int i = 0; i < Webserv()->_nb_server; ++i) {
            std::cout << "couc" <<std::endl;
//            Webserv()->_server[i].launcher(Webserv()->_server[i].getServerFd(),
//                                           (sockaddr *)&Webserv()->_server[i].getAddress(),
//                                           (socklen_t*)&Webserv()->_server[i].getAddrlen());
        }
        waitpid(-1, NULL, 0);
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

