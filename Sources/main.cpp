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

#include "../Include/webserv.hpp"
#include "utils.cpp"

void handleExit(int sig) {
    (void) sig;
    //@todo manage the end by signal
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
    else
        return argv[positionPathFileConfig];
}

static void check_file(int argc, char **argv){
    int positionPathFileConfig = (argc == 2) ? 0 : 2;
    std::string pathConfigFile(selectPath(argv, positionPathFileConfig));

    try {
        config_webserv test_config_file(pathConfigFile);
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
                check_file(argc, argv);
            else if (argv[1][1] == 'c' && argc == 3)
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
    std::string  pathConfigFile;
//    int         number_try_lauch = 0;
    setLogFile("/usr/local/var/log/log_error.txt");
    int         positionPathFileConfig = checkOption(argc, argv);

    if (positionPathFileConfig != -1) {
        signal(SIGINT, handleExit);
        signal(SIGTERM, handleExit);
        signal(SIGHUP, handleReload);
        pathConfigFile += selectPath(argv, positionPathFileConfig);
//        while (number_try_lauch < 1) {
            try {
                config_webserv config_webserv;//@todo add path to constructo after the test
                server server(config_webserv);
                server.launcher();
            }
            catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
//            number_try_lauch++;
//        }
    }
    printLogFile("/usr/local/var/log/log_error.txt");
    exit(EXIT_FAILURE);
}


