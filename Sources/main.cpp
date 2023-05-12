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

#include <Include/webserv.hpp>


void print_info_line(std::pair<std::string, std::vector<std::string> > line, std::string &indente){
//    std::multimap<std::string, std::vector<std::string> >::iterator it_line = line.begin();
//    for (; it_info_line != bloc.info_line.end(); ++it_info_line) {
        std::cout << indente << "key = " << line.first ;
        for (std::vector<std::string>::iterator i = line.second.begin(); i != line.second.end() ; ++i) {
            std::cout << " " << *i;
//        }
//        std::cout << std::endl;
    }
}

void print_info_bloc(s_bloc & bloc, std::string &indente){
    if(bloc.info_line.empty() && bloc.info_bloc.empty())
        return;
    std::multimap<std::string, std::vector<std::string> >::iterator it_line = bloc.info_line.begin();
    for (; it_line != bloc.info_line.end(); ++it_line) {
        print_info_line(*it_line, indente);
    }
    std::multimap<std::pair<std::string, std::vector<std::string> >, s_bloc>::iterator it_info_bloc = bloc.info_bloc.begin();
    indente += "\t";
    for (; it_info_bloc != bloc.info_bloc.end(); ++it_info_bloc) {
        print_info_line(it_info_bloc->first, indente);
        print_info_bloc(it_info_bloc->second, indente);
        std::cout << std::endl;
    }
    indente.erase(indente.end()-1);
}

void print_parsing(s_bloc & bloc){
    std::string indente;
    print_info_bloc(bloc, indente);
}


const char * select_path(int argc, char **argv){
    if(argc == 2)
        return argv[1];
    else
        return "/usr/local/etc/webserv/webserv.conf";
}

int main(int argc, char **argv, char **envp){
    (void)envp;
    (void)argc;
    (void)argv;
    //@todo manage number of try before crash
//    const config_webserv config(argv[1]);
    try{
        parse_config_file config_file(select_path(argc, argv));
        std::cout << config_file.get_bloc_config_file().info_bloc.size() << " " << std::endl;
        print_parsing(config_file.get_bloc_config_file());
//        Parser parsing(select_path(argc, argv));
//        data_server data = parsing.parsefile;
//        data_server data;
//        std::string ip =  "127.0.0.1";
//        int port = 8081;
//        data.setIp_address(ip);
//        data.setPort(port);
//        data.setDomain(AF_INET);
//        data.setType(SOCK_STREAM);
//        data.setProtocol(0);
//        data.setBacklog(10);
//        data.setAddress(AF_INET, 8081);
//        data.setLevel(SOL_SOCKET);
//        data.setOptionName(SO_REUSEADDR);
//        data.setOptionVal(1);
//        server serv(data);
//        serv.launcher();
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

