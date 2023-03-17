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
    try{
        if(argc == 2)
            init(argv[1]);//parse file
        else
            init("config_files/default")//parse default file
        else
            throw std::exception();
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    Webserv();
    launch_webserv();

    exit(EXIT_SUCCESS);
}

