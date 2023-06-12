#pragma once

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "0-Main/Includes/Headers.hpp"
#include "5-Epoll/Token.hpp"
#include "5-Epoll/Socket.class.hpp"
#include "1-Utils/Includes/Utils.hpp"
#include "2-Log/Log.class.hpp"
#include "3-Config/Code.class.hpp"
#include "3-Config/Types.class.hpp"
#include "6-PegParser/PegParser.class.hpp"
//#include "8-Exception/Includes/Exception.hpp"

//__FILE_NAME__
// __LINE__
//__PRETTY_FUNCTION__

struct ConfigLocation{
    ConfigLocation() : uri("/"), root(), index(), autoindex(){}

    explicit ConfigLocation(const std::string & uriw) : uri(uriw), root(), index(), autoindex(){}
    std::string                             uri;
    std::string                             root;
    std::string                             index;
    std::string                             autoindex;
};

struct ConfigServer{
    ConfigServer()
    : token("default server"), listen(), name(), root("/webserv/var/www/defaut.com"),
    index("index.html"){
        listen.insert(std::make_pair("0.0.0.0", 80));
        name.push_back("webserv.local");
        ConfigLocation loc;
        location.insert(std::make_pair(loc.uri, loc));
    }

    explicit ConfigServer(const std::string & tok)
    : token(tok), listen(), name(), root(), index(){}

    virtual ~ConfigServer() {}

    std::string                             token;
    std::map<std::string, int>              listen;
    std::vector<std::string>                name;
    std::string                             root;
    std::string                             index;
    std::map<std::string, ConfigLocation>   location;
};

struct Config {

    explicit Config(char **env)
    : pegParser(), envp(setEnvp(env)),
      accessLog("/webserv/var/log/access.log"),
      errorLog("/webserv/var/log/error.log"),
      pidLog("/webserv/var/log/pid.log"),
      workerProcess(1), workerConnections(10), clientBodyBufferSize(8192), clientHeaderBufferSize(1024),
      clientMaxBodySize(1048576), mapFdServer(), mapFdClient(),
      mapMimeType(Types("/webserv/etc/webserv/conf/mime.types").getMime()),
      code() {
        ConfigServer serv;
        addConfigServer(serv);
    }

    Config(const std::string & pathToConfigFile, char **env)
    : pegParser(pathToConfigFile.c_str(), "#"), envp(setEnvp(env)),
    accessLog("/webserv/config_content_server/var/log/log_info.log"),
    errorLog("/webserv/config_content_server/var/log/error.log"),
    pidLog("/webserv/config_content_server/var/log/webserv.pid"),
    workerProcess(1), workerConnections(10), clientBodyBufferSize(8192), clientHeaderBufferSize(1024),
    clientMaxBodySize(1048576), mapFdServer(), mapFdClient(),
    mapMimeType(Types("/webserv/config_content_server/etc/webserv/conf/mime.types").getMime()),
    code(), mapConfigServer() {}

    virtual ~Config() {}

    void addConfigServer(ConfigServer & server) {
        for ( std::map<std::string, int>::iterator it = server.listen.begin();
              it != server.listen.end(); ++it) {
            Socket sock(it->first, it->second);
            Socket& newSocket = sock;
            for(std::map<int, Socket>::iterator sockIt = mapFdServer.begin();
                sockIt != mapFdServer.end(); ++sockIt){
                if (sockIt->second == newSocket){
                    newSocket = sockIt->second;
                    break;
                }
            }
            newSocket.addServerName(server.name, server.token);
            try {
                newSocket.buildServerSocket();
            }catch (std::exception & e){
                std::cerr << e.what()<<std::endl;
                continue;
            }
            mapFdServer.insert(std::make_pair(newSocket.getSocket(), newSocket));
        }
    }

    PegParser                                           pegParser;
    Token                                               token;
    char **                                             envp;
    Log                                                 accessLog;
    Log                                                 errorLog;
    Log                                                 pidLog;
    int                                                 workerProcess;
    int                                                 workerConnections;
    int                                                 clientBodyBufferSize;
    int                                                 clientHeaderBufferSize;
    int                                                 clientMaxBodySize;
    std::map<int, Socket>                               mapFdServer;
    std::map<int, Socket>                               mapFdClient;
    std::map<std::string, std::string>                  mapMimeType;
    Code                                                code;
    std::map<std::string, ConfigServer>                 mapConfigServer;
};

#endif
