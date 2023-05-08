/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:57:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 18:57:57 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/webserv.hpp"

//static const char * select_path(int argc, char **argv){
//    if(argc == 2)
//        return argv[1];
//    else
//        return "/usr/local/etc/webserv/webserv.conf";
//}

int main(int argc, char **argv, char **envp){
    (void)envp;
    (void)argc;
    (void)argv;
    //@todo manage number of try before crash
    try{
//        Parser parsing(select_path(argc, argv));
//        data_server data = parsing.parsefile;
        data_server data;
        std::string ip =  "127.0.0.1";
        int port = 8081;
        data.setIp_address(ip);
        data.setPort(port);
        data.setDomain(AF_INET);
        data.setType(SOCK_STREAM);
        data.setProtocol(0);
        data.setBacklog(10);
        data.setAddress(AF_INET, 8081);
        data.setLevel(SOL_SOCKET);
        data.setOptionName(SO_REUSEADDR);
        data.setOptionVal(1);
        server serv(data);
        serv.launcher();
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

