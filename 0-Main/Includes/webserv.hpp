#pragma once

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "1-Utils/Includes/Utils.hpp"
#include "2-Log/Log.class.hpp"
#include "3-Config/Code.class.hpp"
#include "3-Config/ConfigFile.class.hpp"
#include "3-Config/Types.class.hpp"
#include "6-PegParser/PegParser.class.hpp"
#include "5-Epoll/Epoll.class.hpp"
//#include "8-Exception/Includes/Exception.hpp"

#define FLAG1 0x01 // 0000 0001
#define FLAG2 0x02 // 0000 0010
#define FLAG3 0x04 // 0000 0100
#define FLAG4 0x08 // 0000 1000
#define FLAG5 0x10 // 0001 0000
#define FLAG6 0x20 // 0010 0000
#define FLAG7 0x40 // 0100 0000
#define FLAG8 0x80 // 1000 0000

//__FILE_NAME__
// __LINE__
//__PRETTY_FUNCTION__
//char** ConfigFile::setEnvp(char **envp){
//    if (envp) {
//        std::vector<char *> vecEnvp;
//        for (int i = 0; envp[i] != NULL; ++i) {
//            char * tmp = strdup(envp[i]);
//            vecEnvp.push_back(tmp);
//std::string path("/webserv/config_content_server/for_etc/webserv/conf/mime.types");
//        }
//        vecEnvp.push_back(NULL);
//        char **newEnvp = new char *[vecEnvp.size()];
//        std::copy(vecEnvp.begin(), vecEnvp.end(), newEnvp);
//        return newEnvp;
//    }
//void Http::setDefaultValue() {
//    Server.class serverProxy(_peg);
//    serverProxy.setDefaultValue("0.0.0.0:80");
//    Epoll epollProxy(serverProxy._vectorServerSocket, _peg._Events._workerConnections);
//    serverProxy._epoll = epollProxy;
//    _vecPairServerEpoll.push_back(std::make_pair(serverProxy, epollProxy));
//    Server.class Server1(_peg);
//    Server1.setDefaultValue("0.0.0.0:8080");
//    Epoll epoll(Server1._vectorServerSocket, _peg._Events._workerConnections);
//    Server1._epoll = epoll;
//    _vecPairServerEpoll.push_back(std::make_pair(Server1, epoll));
//    Server.class Server2(_peg);
//    Server2.setDefaultValue("0.0.0.0:8081");
//    Epoll epoll2(Server2._vectorServerSocket, _peg._Events._workerConnections);
//    Server2._epoll = epoll2;
//    _vecPairServerEpoll.push_back(std::make_pair(Server2, epoll2));
//}
//    return NULL;
//}_pegParser(pathToConfigFile.c_str(), "#"),, std::string & pathToConfigFile)
struct Config {
//    _enp(setEnvp(envp))
//    _Log.setLog(_pathLog);
//    _errorLog.setLog(_patherrorLog);
//    _pidLog.setLog(_pathpidLog);
//    _pidLog.writeLogFile(intToString(getpid()));
//    _pathLog("/webserv/config_content_server/for_var/logs/log.logs"),
//    _patherrorLog("/webserv/config_content_server/for_var/logs/error.logs"),
//    _pathpidLog("/webserv/config_content_server/for_var/logs/webserv.pid"),
    PegParser                                           pegParser;
    char **                                             enp;
    Log                                                 log;
    Log                                                 errorLog;
    Log                                                 pidLog;
    int                                                 workerProcess;//1
    int                                                 workerConnections;//10
    int                                                 clientBodyBufferSize;//(8192), _
    int                                                 clientHeaderBufferSize;//(1024), _
    int                                                 clientMaxBodySize;//(1048576)
    std::vector<Epoll>                                  vecEpoll;
    std::map<std::string, std::string>                  mapMimeType;
    Types                                               types;
    Code                                                code;
};

#endif
