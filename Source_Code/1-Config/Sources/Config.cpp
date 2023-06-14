//
// Created by Matthis DoQuocBao on 2023-06-13.
//

#include <Source_Code/1-Config/Includes/Config.hpp>


ConfigBase::ConfigBase(const std::string & pathToConfigBaseFile, char **env)
: workerProcess(1), workerConnections(10),
  clientBodyBufferSize(8192), clientHeaderBufferSize(1024),clientMaxBodySize(1048576),
  listen(), index(), root("/webserv/var/www/defaut.com"), code(),
  mapFdServer(), mapTokenUriConfig(), mapFdClient(),
  mapMimeType(Types("/webserv/etc/webserv/conf/mime.types").getMime()),
  accessLog("/webserv/var/log/log_info.log"),
  errorLog("/webserv/var/log/error.log"),
  pidLog("/webserv/var/log/webserv.pid"),
  pegParser(pathToConfigBaseFile.c_str(), "#"), token(),envp(setEnvp(env)),
  configBase(*this) {
   index.insert("localhost");
}//@todo add free envp

ConfigBase::~ConfigBase() {
    delete envp;
}

ConfigBase::ConfigBase(ConfigBase & other)
: workerProcess(other.workerProcess), workerConnections(other.workerConnections),
  clientBodyBufferSize(other.clientBodyBufferSize),
  clientHeaderBufferSize(other.clientHeaderBufferSize),
  clientMaxBodySize(other.clientMaxBodySize),
  listen(other.listen),index(other.index), root(other.root), code(other.code),
  mapFdServer(other.mapFdServer),
  mapFdClient(other.mapFdClient), mapMimeType(other.mapMimeType),
  accessLog(other.accessLog), errorLog(other.errorLog), pidLog(other.pidLog),
  pegParser(other.pegParser), token(other.token),envp(other.envp), configBase(other){}

ConfigBase & ConfigBase::operator=(const ConfigBase & rhs){
    if (this != &rhs){
        this->workerProcess = rhs.workerProcess;
        this->workerConnections = rhs.workerConnections;
        this->clientBodyBufferSize = rhs.clientBodyBufferSize;
        this->clientHeaderBufferSize = rhs.clientHeaderBufferSize;
        this->clientMaxBodySize = rhs.clientMaxBodySize;
        this->listen = rhs.listen;
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
        this->configBase = rhs.configBase;
    }
}

void ConfigBase::addConfigBase(Config & server) {
    if (!server.listen.empty()) {
        std::map<std::string, std::map<std::string, Config> >::iterator it = mapTokenUriConfig.find(server._tok);
        if (it != mapTokenUriConfig.end()) {
            it->second.insert(std::make_pair(server._uri, server));
        } else {
            std::map<std::string, Config> map;
            map.insert(std::make_pair(server._uri, server));
            mapTokenUriConfig.insert(std::make_pair(server._tok, map));
        }
    }
}

void ConfigBase::addIndex(std::vector<std::string> & value) {
    if (!value.empty()) {
        for (std::vector<std::string>::iterator it = value.begin();
        it != value.end() ; ++it) {
            if (index.find(*it) != index.end())
                index.insert(*it);
        }
    }
}

Config::Config(ConfigBase & config)
: ConfigBase(config), _tok(config.token.generateToken()),
_name(), _uri(), _info(),
_allowMethods(7), _return(), _cgiPass(), _autoindex(false){}

Config::~Config() {}

Config::Config(const Config & other)
    : ConfigBase((ConfigBase &) other), _tok(other._tok), _name(other._name), _uri(other._uri),
      _info(), _allowMethods(other._allowMethods), _return(other._return), _cgiPass(),
      _autoindex(other._autoindex) {}

Config & Config::operator=(const Config & rhs){
    if (this != &rhs){
        ConfigBase::operator=(rhs);
        this->_tok = rhs._tok;
        this->_name = rhs._name;
        this->_uri = rhs._uri;
        this->_info = rhs._info;
        this->_allowMethods = rhs._allowMethods;
        this->_return = rhs._return;
        this->_cgiPass = rhs._cgiPass;
        this->_autoindex = rhs._autoindex;
    }
    return *this;
}

void Config::addName(std::vector<std::string> & value) {
    if (!value.empty()) {
        for (std::vector<std::string>::iterator it = value.begin();
             it != value.end() ; ++it) {
            if (_name.find(*it) != _name.end())
                _name.insert(*it);
        }
    }
}

