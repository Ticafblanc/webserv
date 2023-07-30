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

#include <Source_Code/1-Config/Includes/Config.hpp>
#include <Source_Code/1-Config/Includes/ConfigFile.class.hpp>
#include <Source_Code/2-Engin/Includes/Epoll.class.hpp>
#include <Source_Code/0-ClI/Includes/Cli.class.hpp>

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
        return "/webserv/Docker_build/etc/webserv/webserv.conf";
//        return "/usr/local/etc/webserv/webserv.conf";
    else if(positionPathFileConfig == 3 )
        return "";
    else
        return argv[positionPathFileConfig];
}

static void checkFile(int argc, char **argv){
    int positionPathFileConfig = (argc == 2) ? 0 : 2;
    std::string pathConfigFile(selectPath(argv, positionPathFileConfig));

    try {
        PegParser<ConfigFile> peg(pathConfigFile.c_str(), "#");
//        Token     token;
//        Config webserv(token);
//        ConfigFile extractConfigFile(webserv, peg);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "webserv: configuration file " << pathConfigFile << " test failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "webserv: configuration file " << pathConfigFile << " test is successful" << std::endl;
    exit(EXIT_SUCCESS);

}



//static void launcher(Config & config) {
//    Epoll epoll(config);
//    epoll.launchEpoll();
//    while(true) {
//        try {
//            epoll.EpollWait();
//        }catch (std::exception & e){
//            config._accessLog.setIndent("");
//            config._accessLog.setLogEnable(true);
//            std::ostringstream oss;
//            oss << "last event >> " << config._accessLog;
//            config._errorLog.writeMessageLogFile(oss.str());
//            config._errorLog.writeMessageLogFile(e.what());
//        }
//    }
//}
static bool isMainProgram(){
    return (system("pidof webserv > /dev/null 2>&1") == 0);
}

static void initSignal(){
    signal(SIGINT, handleExit);
    signal(SIGTERM, handleExit);
    signal(SIGHUP, handleReload);
}


int main(int argc, char **argv){
    Cli cli(argc, argv);
    try {
        cli.checkArg();
    }catch (std::exception& e){
        return 1;
    }

    if (isMainProgram()){
        std::cout << "Welcome to Webserv !!\n";
        initSignal();
        if (raise(SIGHUP) != 0){
            std::cerr << "Erreur to launch Webserv";
            return 1;
        }
        while (true);
    } else{
        std::cout << "Webserv is already open\n";
        cli.
    }
    std::string pathConfigFile;
    int         positionPathFileConfig = checkOption(argc, argv);

   if (positionPathFileConfig != -1) {

        pathConfigFile = selectPath(argv, positionPathFileConfig);
//        Token     token;
//        Config webserv(token);
        try {
            PegParser<ConfigFile> peg(pathConfigFile.c_str(), "#");
//            ConfigFile extractConfigFile(webserv, peg);
        }
        catch (const std::exception &e) {
            std::cout << "Config error on => " << e.what() << std::endl;
        }
//        launcher(webserv);//@todo manage thread

    }
    exit(EXIT_FAILURE);
}
