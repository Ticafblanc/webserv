//
// Created by Matthis DoQuocBao on 2023-06-13.
//

#ifndef WEBSERVER_CONFIG_HPP
#define WEBSERVER_CONFIG_HPP

#include <Source_Code/0-Main/Includes/Headers.hpp>
#include <Source_Code/4-Utils/Includes/Utils.hpp>

#include <Source_Code/1-Config/Includes/Log.class.hpp>
#include <Source_Code/1-Config/Includes/Types.class.hpp>
#include <Source_Code/1-Config/Includes/Code.class.hpp>
#include <Source_Code/2-Engin//Includes/Token.hpp>
#include <Source_Code/2-Engin//Includes/Socket.class.hpp>


struct Config {

    Config( Token & token, char **env);

    virtual ~Config() ;

    Config(const Config & other);

    Config & operator=(const Config & rhs);

    void addChild(const Config & child);

    void addServerName(Config & child);

    void addToSet(std::vector<std::string> & value, std::set<std::string> & conf);

    /*data config for each bloc*/
    int                                                             _workerProcess;
    int                                                             _workerConnections;
    int                                                             _clientBodyBufferSize;
    int                                                             _clientHeaderBufferSize;
    int                                                             _clientMaxBodySize;
    std::vector<std::string>                                        _name;
    std::set<std::string>                                           _index;
    std::string                                                     _root;
    std::string                                                     _uri;
    int                                                             _allowMethods;// GET = 1 POST = 2 DELETE = 4 GET/POST = 3 GET/DELETE = 5 POST/DELETE = 6 ALL = 7
    int                                                             _return;//return code [text]; text == uri or custom code
    std::string                                                     _cgiPass;// /path=>>cgi
    bool                                                            _autoindex;//on/off
    Code                                                            _code;//code class

    /*data to store config*/
    std::map<int, Socket>                                                   _mapFdSocket;// map int fd and Socket class for first : fd/server for server fd/client
    std::map<std::string, std::vector<std::pair<std::string, Config> > >    _mapTokenVectorUriConfig;//map id token and config child
    std::map<std::string, std::string>                                      _mapMimeType;//mime type data

    /*environnement de travail*/
    Log                                                             _accessLog;//store access
    Log                                                             _errorLog;//store error
    Log                                                             _pidLog;//store PID
    Token &                                                         _token;//Token class
    std::string                                                     _tok;//token for this
    char **                                                         _envp;//envp
    Config&                                                         _configBase;//reference on first config
};




#endif //WEBSERVER_CONFIG_HPP
