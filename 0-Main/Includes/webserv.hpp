#pragma once

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "1-Utils/Includes/Utils.hpp"
#include "2-Log/Log.class.hpp"
#include "3-Config/Code.class.hpp"
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
//


struct Config {

    Config(char **env)
    : pegParser(), envp(setEnvp(env)),
      log("/webserv/config_content_server/for_var/logs/log_info.logs"),
      errorLog("/webserv/config_content_server/for_var/logs/error.logs"),
      pidLog("/webserv/config_content_server/for_var/logs/webserv.pid"),
      workerProcess(1), workerConnections(10), clientBodyBufferSize(8192), clientHeaderBufferSize(1024),
      clientMaxBodySize(1048576), vecEpoll(),
      mapMimeType(Types("/webserv/config_content_server/for_etc/webserv/conf/mime.types").getMime()),
      code() {}

    Config(const std::string & pathToConfigFile, char **env)
    : pegParser(pathToConfigFile.c_str(), "#"), envp(setEnvp(env)),
    log("/webserv/config_content_server/for_var/logs/log_info.logs"),
    errorLog("/webserv/config_content_server/for_var/logs/error.logs"),
    pidLog("/webserv/config_content_server/for_var/logs/webserv.pid"),
    workerProcess(1), workerConnections(10), clientBodyBufferSize(8192), clientHeaderBufferSize(1024),
    clientMaxBodySize(1048576), vecEpoll(),
    mapMimeType(Types("/webserv/config_content_server/for_etc/webserv/conf/mime.types").getMime()),
    code() {}

    virtual ~Config() {}

    PegParser                                           pegParser;
    char **                                             envp;
    Log                                                 log;
    Log                                                 errorLog;
    Log                                                 pidLog;
    int                                                 workerProcess;
    int                                                 workerConnections;
    int                                                 clientBodyBufferSize;
    int                                                 clientHeaderBufferSize;
    int                                                 clientMaxBodySize;
    std::vector<Epoll>                                  vecEpoll;
    std::map<std::string, std::string>                  mapMimeType;
    Code                                                code;
};

#endif
