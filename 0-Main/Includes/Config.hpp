//
// Created by Matthis DoQuocBao on 2023-06-13.
//

#ifndef WEBSERVER_CONFIG_HPP
#define WEBSERVER_CONFIG_HPP

#include "Headers.hpp"
#include "2-Log/Log.class.hpp"
#include "3-Config/Types.class.hpp"
#include "1-Utils/Includes/Utils.hpp"
#include "3-Config/Code.class.hpp"
#include "5-Epoll/Token.hpp"
#include "5-Epoll/Socket.class.hpp"

struct Config;

struct ConfigBase {

    ConfigBase(const std::string & pathToConfigBaseFile, char **env);

    virtual ~ConfigBase() ;

    ConfigBase(const ConfigBase & other);

    ConfigBase & operator=(const ConfigBase & rhs);

    void addConfigBase(Config & server) ;

    /*data config for each bloc*/
    int                                                             workerProcess;
    int                                                             workerConnections;
    int                                                             clientBodyBufferSize;
    int                                                             clientHeaderBufferSize;
    int                                                             clientMaxBodySize;
    std::map<std::string, int>                                      listen;
    std::vector<std::string>                                        name;
    std::string                                                     index;
    std::string                                                     root;
    Code                                                            code;

    /*data to store config*/
    std::map<int, Socket>                                           mapFdServer;
    std::map<std::string, std::map<std::string, Config> >           mapTokenUriConfig;
    std::map<int, Socket>                                           mapFdClient;
    std::map<std::string, std::string>                              mapMimeType;

    /*environnement de travail*/
    Log                                                             accessLog;
    Log                                                             errorLog;
    Log                                                             pidLog;
    PegParser                                                       pegParser;
    Token                                                           token;
    char **                                                         envp;

};

union info {
    int*                                     _allowMethods;// GET = 1 POST = 2 DELETE = 4 GET/POST = 3 GET/DELETE = 5 POST/DELETE = 6 ALL = 7
    std::pair<int, std::string>*             _return;//return code [text]; text == uri or custom code
    std::string*                             _cgiPass;// /path=>>cgi
    bool*                                    _autoindex;//on/off
};

struct Config : public ConfigBase {

    explicit Config(ConfigBase & config);

    virtual ~Config();

    Config(const Config & other);

    Config & operator=(const Config & rhs);

    ConfigBase&                             _configBase;
    std::string                             _tok;
    std::string                             _uri;// "/..."
    std::vector<info>                       _info;
    int                                     _allowMethods;// GET = 1 POST = 2 DELETE = 4 GET/POST = 3 GET/DELETE = 5 POST/DELETE = 6 ALL = 7
    std::pair<int, std::string>             _return;//return code [text]; text == uri or custom code
    std::string                             _cgiPass;// /path=>>cgi
    bool                                    _autoindex;//on/off
};


#endif //WEBSERVER_CONFIG_HPP
