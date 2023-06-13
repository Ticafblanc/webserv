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

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/1-Config/Includes/ConfigFile.class.hpp>
#include <Source_Code/2-Engin/Includes/Epoll.class.hpp>

void handleExit(int sig) {
    (void) sig;
    //@todo manage the end by signal
//    printLogFile("/usr/local/var/log/log_error.txt");
    std::cout << "exit by signal" << std::endl;
    exit(EXIT_SUCCESS);
}

void handleReload(int sig) {
    (void) sig;
    //@todo manage the reload by signal
    std::cout << "reload by signal" << std::endl;
    exit(EXIT_SUCCESS);
}


const char * selectPath(char **argv, int positionPathFileConfig){
    if(positionPathFileConfig == 0)
        return "/usr/local/etc/webserv/webserv.conf";
    else if(positionPathFileConfig == 3 )
        return "";
    else
        return argv[positionPathFileConfig];
}

static void checkFile(int argc, char **argv, char ** envp){
    int positionPathFileConfig = (argc == 2) ? 0 : 2;
    std::string pathConfigFile(selectPath(argv, positionPathFileConfig));

    try {
        Config webserv(pathConfigFile, envp);
        ConfigFile extractConfigFile(webserv);
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "webserv: configuration file " << pathConfigFile << " test failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "webserv: configuration file " << pathConfigFile << " test is successful" << std::endl;
    exit(EXIT_SUCCESS);

}

static int checkOption(int argc, char **argv, char ** envp){
    if (argc > 3){
        std::cerr << "too many arguments" << std::endl;
        return -1;
    }
    if (argc > 1) {
        if (argv[1][0] == '-') {
            if (argv[1][1] == 's')
                (void)argv;//@todo webserv -s (stop quit reopen reload) SIGINT, SIGTERM shutdown SIGHUP reload
            else if (argv[1][1] == 't')
                checkFile(argc, argv, envp);
            else if (argv[1][1] == 'd')
                return 3;
            else if (argv[1][1] == 'c' && argc == 3)
                return 2;
            std::cerr << "invalid option -" << argv[1][1] << std::endl;
            return -1;
        }
        return 1;
    }
    return 0;
}

static void launcher(Config & config) {
    Epoll epoll(config);
    epoll.launchEpoll();
    while(true) {
        try {
            epoll.EpollWait();
        }catch (std::exception & e){
            std::cerr << e.what() << std::endl;
            config.errorLog.writeLogFile(e.what());
        }
    }
}

int main(int argc, char **argv, char **envp){
    std::string pathConfigFile;
    int         positionPathFileConfig = checkOption(argc, argv, envp);

    if (positionPathFileConfig != -1) {
        signal(SIGINT, handleExit);
        signal(SIGTERM, handleExit);
        signal(SIGHUP, handleReload);
        pathConfigFile = selectPath(argv, positionPathFileConfig);
        try {
            if(!pathConfigFile.empty()){
                Config webserv(pathConfigFile, envp);
                ConfigFile extractConfigFile(webserv);
                launcher(webserv);//@todo manage thread
            } else{
                Config webserv(envp);
                launcher(webserv);//@todo manage thread
            }
        }
        catch (const std::exception &e) {
            std::cout << "Config error on => " << e.what() << std::endl;
        }
    }
    exit(EXIT_FAILURE);
}













//    sockaddr_in _sockaddress = {};
//    memset(&_sockaddress.sin_zero, 0, sizeof(_sockaddress.sin_zero));
//    _sockaddress.sin_family = AF_INET;
//    _sockaddress.sin_addr.s_addr = inet_addr("0.0.0.0");
//    _sockaddress.sin_port = htons(8081);
//    int _server_socket = socket(AF_INET, SOCK_STREAM, 0);
//    int option_val = 1;
//    int s = setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR,
//                   &option_val, (socklen_t)sizeof(option_val));
//    int f = bind(_server_socket, reinterpret_cast<struct sockaddr *>(&_sockaddress), sizeof(_sockaddress));
//    int l = listen(_server_socket, 10);
//    fcntl(_server_socket, F_SETFL, O_NONBLOCK );
//    epoll_event event, events[10];
//    event.data.fd = _server_socket;
//    event.events = EPOLLIN;
//    int _epoll_instance = epoll_create(1);
//    int e = epoll_ctl( _epoll_instance, EPOLL_CTL_ADD, _server_socket, &event);
//    (void)s;
//    (void)f;
//    (void)l;
//    (void)e;
//    int _number_triggered_events = epoll_wait(_epoll_instance, events,10, -1);
//
//    std::cout<< _number_triggered_events<<std::endl;