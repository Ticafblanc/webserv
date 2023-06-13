//
// Created by Matthis DoQuocBao on 2023-06-13.
//

#include <Source_Code/1-Config/Includes/Config.hpp>


ConfigBase::ConfigBase(const std::string & pathToConfigBaseFile, char **env)
        : workerProcess(1), workerConnections(10),
          clientBodyBufferSize(8192), clientHeaderBufferSize(1024),clientMaxBodySize(1048576),
          listen(), name(1,"localhost"), index("index.html"),
          root("/webserv/var/www/defaut.com"), code(),
          mapFdServer(), mapTokenUriConfig(), mapFdClient(),
          mapMimeType(Types("/webserv/etc/webserv/conf/mime.types").getMime()),
          accessLog("/webserv/var/log/log_info.log"),
          errorLog("/webserv/var/log/error.log"),
          pidLog("/webserv/var/log/webserv.pid"),
          pegParser(pathToConfigBaseFile.c_str(), "#"), token(),envp(setEnvp(env)) {}//@todo add free envp

ConfigBase::~ConfigBase() {}

ConfigBase::ConfigBase(const ConfigBase & other)
        : workerProcess(other.workerProcess), workerConnections(other.workerConnections),
          clientBodyBufferSize(other.clientBodyBufferSize),
          clientHeaderBufferSize(other.clientHeaderBufferSize),
          clientMaxBodySize(other.clientMaxBodySize),
          listen(other.listen), name(other.name), index(other.index), root(other.root), code(other.code),
          mapFdServer(other.mapFdServer),
          mapFdClient(other.mapFdClient), mapMimeType(other.mapMimeType),
          accessLog(other.accessLog), errorLog(other.errorLog), pidLog(other.pidLog),
          pegParser(other.pegParser), token(other.token),envp(other.envp){}

ConfigBase & ConfigBase::operator=(const ConfigBase & rhs){
    if (this != &rhs){
        this->workerProcess = rhs.workerProcess;
        this->workerConnections = rhs.workerConnections;
        this->clientBodyBufferSize = rhs.clientBodyBufferSize;
        this->clientHeaderBufferSize = rhs.clientHeaderBufferSize;
        this->clientMaxBodySize = rhs.clientMaxBodySize;
        this->listen = rhs.listen;
        this->name = rhs.name;
        this->index = rhs.index;
        this->root = rhs.root;
        this->code = rhs.code;
        this->mapFdServer = rhs.mapFdServer;
        this->mapTokenUriConfig = rhs.mapTokenUriConfig;
        this->mapFdClient = rhs.mapFdClient;
        this->mapMimeType = rhs.mapMimeType;
        this->accessLog = rhs.accessLog;
        this->errorLog = rhs.errorLog;
        this->pidLog = rhs.pidLog;
        this->pegParser = rhs.pegParser;
        this->token = rhs.token;
        this->envp = rhs.envp;
    }
}

void ConfigBase::addConfigBase(Config & server) {
    std::map<std::string, std::map<std::string, Config> >::iterator it = mapTokenUriConfig.find(server._tok);
    if (it != mapTokenUriConfig.end()){
        it->second.insert(std::make_pair(server._uri, server));
    } else {
        mapTokenUriConfig.insert(std::make_pair(server._tok, std::make_pair(server._uri, server)));
    }
}


Config::Config(ConfigBase & config)
: ConfigBase(config), _configBase(config),_tok(config.token.generateToken()), _uri("/"), _info(),
_allowMethods(7), _return(), _cgiPass(), _autoindex(false){}

Config::~Config() {}

Config::Config(const Config & other)
        : ConfigBase(other), _configBase(other._configBase), _tok(other._tok), _uri(other._uri), _info(), _allowMethods(other._allowMethods),
          _return(other._return), _cgiPass(), _autoindex(other._autoindex) {}

Config & Config::operator=(const Config & rhs){
    if (this != &rhs){
        Config::operator=(rhs);
        this->_configBase = rhs._configBase;
        this->_tok = rhs._tok;
        this->_uri = rhs._uri;
        this->_info = rhs._info;
        this->_allowMethods = rhs._allowMethods;
        this->_return = rhs._return;
        this->_cgiPass = rhs._cgiPass;
        this->_autoindex = rhs._autoindex;
    }
    return *this;
}