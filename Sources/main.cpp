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

void handle_exit(int sig) {
    (void) sig;
    //@todo manage the end by signal
    std::cout << "exit by signal" << std::endl;
    exit(EXIT_SUCCESS);
}

void handle_reload(int sig) {
    (void) sig;
    //@todo manage the reload by signal
    std::cout << "reload by signal" << std::endl;
    exit(EXIT_SUCCESS);
}


const char * select_path(char **argv, int position_path_file_config){
    if(position_path_file_config == 0)
        return "/usr/local/etc/webserv/webserv.conf";
    else
        return argv[position_path_file_config];
}

static void check_file(int argc, char **argv){
    int position_path_file_config = (argc == 2) ? 0 : 2;
    std::string path_config_file(select_path(argv, position_path_file_config));

    try {
        config_webserv test_config_file(path_config_file);
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "webserv: configuration file " << path_config_file << " test failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "webserv: configuration file " << path_config_file << " test is successful" << std::endl;
    exit(EXIT_SUCCESS);

}

static int check_option(int argc, char **argv){
    if (argc > 3){
        std::cerr << "too many arguments" << std::endl;
        return -1;
    }
    if (argc > 1) {
        if (argv[1][0] == '-') {
            if (argv[1][1] == 's')
                (void)argv;//@todo webserv -s (stop quit reopen reload) SIGINT, SIGTERM shutdown SIGHUP reload
            else if (argv[1][1] == 't')
                check_file(argc, argv);
            else if (argv[1][1] == 'c')
                return 2;
            std::cerr << "invalid option -" << argv[1][1] << std::endl;
            return -1;
        }
        return 1;
    }
    return 0;
}

int main(int argc, char **argv, char **envp){
    (void)envp;
    std::string  path_config_file;
    int         number_try_lauch = 0;
    int         position_path_file_config = check_option(argc, argv);

    if (position_path_file_config != -1) {
        signal(SIGINT, handle_exit);
        signal(SIGTERM, handle_exit);
        signal(SIGHUP, handle_reload);
        while (number_try_lauch < 6) {
            try {
//                path_config_file += select_path(argv, position_path_file_config);
//                config_webserv config_webserv(path_config_file);
//                server server(config_webserv);
            }
            catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
            number_try_lauch++;
        }
    }
    exit(EXIT_FAILURE);
}

/* data_server data = parsing.parsefile;
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
//        serv.launcher();*/
