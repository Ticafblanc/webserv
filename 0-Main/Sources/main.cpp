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

#include "0-Main/Includes/webserv.hpp"

void handleExit(int sig) {
    (void) sig;
    //@todo manage the end by signal
//    printLogFile("/usr/local/var/logs/log_error.txt");
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

static void checkFile(int argc, char **argv){
    int positionPathFileConfig = (argc == 2) ? 0 : 2;
    std::string pathConfigFile(selectPath(argv, positionPathFileConfig));

    try {
//        Config testConfigFile(pathConfigFile);
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "webserv: configuration file " << pathConfigFile << " test failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "webserv: configuration file " << pathConfigFile << " test is successful" << std::endl;
    exit(EXIT_SUCCESS);

}

static int checkOption(int argc, char **argv){
    if (argc > 3){
        std::cerr << "too many arguments" << std::endl;
        return -1;
    }
    if (argc > 1) {
        if (argv[1][0] == '-') {
            if (argv[1][1] == 's')
                (void)argv;//@todo webserv -s (stop quit reopen reload) SIGINT, SIGTERM shutdown SIGHUP reload
            else if (argv[1][1] == 't')
                checkFile(argc, argv);
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
    (void)config;
    while(true) {
        for ( std::vector<std::pair<Server, Epoll> >::iterator it = config._Http._vecPairServerEpoll.begin();
        it != config._Http._vecPairServerEpoll.end(); ++it) {
            try {
                std::cout << "fd = " << it->first._vectorServerSocket.begin()->data.fd << " event = " << it->second.getEvents()->data.fd << " nb event = " <<it->second.getNumberTriggeredEvents()<< std::endl;
                if(it->second.EpollWait(2000)) {
                    std::cout << "event = " << it->second.getEvents()->data.fd << std::endl;
                }
//                if(it->EpollWait(200)){
//                    for (int i = 0; i < it->getNumberTriggeredEvents(); ++i) {
//                        std::map<int, Socket>::iterator tok = config._mapFdSocket.find(it->_epoll.getEvents()[i].data.fd);
//                        if (tok != config._mapFdSocket.end())
//                            tok->second.manageEvent(it->_epoll.getEvents()[i], tok->second);
//                        else {
//                            if (it->getEvents()[i].data.fd == 0)
//                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//                            std::string error("file descriptor inconnu => " );
//                            error += intToString(it->_epoll.getEvents()->data.fd);
//                            writeLogFile(error,"/webserv/config_content_server/for_var/logs/log_error.txt");
//                            close(it->_epoll.getEvents()->data.fd);//see if necessary to check fd before close
//                        }
//                    }
//                }
            }catch (std::exception & e){
                std::cerr << e.what() << std::endl;
//                writeLogFile(e.what(), "/webserv/config_content_server/for_var/logs/log_error.txt");
            }
        }
    }
}

int main(int argc, char **argv, char **envp){
    (void)envp;
    std::string pathConfigFile;
    int         positionPathFileConfig = checkOption(argc, argv);

    if (positionPathFileConfig != -1) {
        signal(SIGINT, handleExit);
        signal(SIGTERM, handleExit);
        signal(SIGHUP, handleReload);
        pathConfigFile = selectPath(argv, positionPathFileConfig);
        try {
            Config webserv(pathConfigFile, envp);//@todo add path to constructo after the test
            launcher(webserv);//@todo manage thread
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
//            writeLogFile(e.what(), "/webserv/config_content_server/for_var/logs/log_error.txt");
        }
    }
//    printLogFile("/webserv/config_content_server/for_var/logs/log_error.txt");
    exit(EXIT_FAILURE);
}


