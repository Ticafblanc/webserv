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

void  webserv_loop(){
    pid_t pid;
    int server_fd;
    int new_socket;
    struct sockaddr_in address;/*
 *struct ot store variable of server (ip, port, etc..)
 * struct sockaddr_in {// https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html //
	__uint8_t       sin_len;
	sa_family_t     sin_family;
	in_port_t       sin_port;
	struct  in_addr sin_addr;
	char            sin_zero[8];
    }; */
    int addrlen = sizeof(address);//
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "server_fd 1 = " << server_fd << " AF_INET = " << AF_INET << " SOCK_STREAM = " <<  SOCK_STREAM << std::endl;
//    server_fd = socket(AF_INET, SOCK_STREAM, 0);
//    std::cout << "server_fd 2 = " << server_fd << " AF_INET = " << AF_INET << " SOCK_STREAM = " <<  SOCK_STREAM << std::endl;
    if (server_fd == 0)
    {
        perror("In sockets");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr =  inet_addr("127.0.0.1");//set ip to numbers IN STRUCT
    address.sin_port = htons( 8081 ); //set port in struct
//    std::cout << address.sin_addr.s_addr << " " << inet_addr("127.0.0.1") << std::endl;

    memset(address.sin_zero, '\0', sizeof address.sin_zero);//set zero

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {=
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while (1){
        std::cout << "start servers" << std::endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if(pid < 0)
            exit(EXIT_FAILURE);
        if(pid == 0){
            std::cout << address.sin_addr.s_addr << " " << inet_addr("127.0.0.1") << std::endl;

        }
    }
}

int main(int argc, char **argv, char **envp){
//    init(argv[1]);

    webserv_loop();

    exit(0);
}

