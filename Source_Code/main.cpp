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

//#include <Source_Code/1-Config/Includes/Config.hpp>
//#include <Source_Code/1-Config/Includes/ConfigFile.class.hpp>
//#include <Source_Code/2-Engin/Includes/Epoll.class.hpp>
#include <Source_Code/0-ClI/Includes/Cli.class.hpp>


int main(int argc, char **argv) {
    Cli cli(argc, argv);
    while (!cli.isStop()) {
        kill(cli.getPid(), SIGHUP);
        pause();
    }
    return cli.getStatus();
}




//int positionPathFileConfig = (argc == 2) ? 0 : 2;
//std::string pathConfigFile(selectPath(argv, positionPathFileConfig));
//
//try {
//PegParser<ConfigFile> peg(pathConfigFile.c_str(), "#");
////        Token     token;
////        Config webserv(token);
////        ConfigFile extractConfigFile(webserv, peg);
//}
//catch (const std::exception &e) {
//std::cerr << e.what() << std::endl;
//std::cerr << "webserv: configuration file " << pathConfigFile << " test failed" << std::endl;
//exit(EXIT_FAILURE);
//}
//std::cout << "webserv: configuration file " << pathConfigFile << " test is successful" << std::endl;
//exit(EXIT_SUCCESS);

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



//    return cli.getStatus();
//
//    std::string pathConfigFile;
//    int         positionPathFileConfig = checkOption(argc, argv);
//
//   if (positionPathFileConfig != -1) {
//
//        pathConfigFile = selectPath(argv, positionPathFileConfig);
////        Token     token;
////        Config webserv(token);
//        try {
//            PegParser<ConfigFile> peg(pathConfigFile.c_str(), "#");
////            ConfigFile extractConfigFile(webserv, peg);
//        }
//        catch (const std::exception &e) {
//            std::cout << "Config error on => " << e.what() << std::endl;
//        }
////        launcher(webserv);//@todo manage thread
//
//    }
//    exit(EXIT_FAILURE);
//}
