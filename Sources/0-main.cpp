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
    while (1){
        std::cout << "start servers" << std::endl;
        pid = fork();
        if(pid < 0)
            exit(EXIT_FAILURE);
        if(pid == 0){

        }
    }
}

int main(int argc, char **argv, char **envp){
//    init(argv[1]);

    webserv_loop();

    exit(0);
}

