//
// Created by Matthis DoQuocBao on 2023-06-13.
//

#include <Source_Code/1-Config/Includes/Config.hpp>


Config::Config(Token & token, char **env)
: _workerProcess(1), _workerConnections(10),
  _clientBodyBufferSize(8192), _clientHeaderBufferSize(1024),_clientMaxBodySize(1048576),
  _listen(), _name(), _index(), _root("/webserv/var/www/defaut.com"), _allowMethods(7),
  _return(), _cgiPass(), _autoindex(false), _code(),
  _mapFdSocket(), _mapTokenConfig(),
  _mapMimeType(Types("/webserv/etc/webserv/conf/mime.types").getMime()),
  _accessLog("/webserv/var/log/log_info.log"),
  _errorLog("/webserv/var/log/error.log"),
  _pidLog("/webserv/var/log/webserv.pid"),
  _token(token), _tok(), _envp(setEnvp(env)),
  _configBase(*this) {
    _name.insert("localhost");
    _index.insert("index.html");
    _pidLog.writeLogFile(intToString(getpid()));
}//@todo add free envp

Config::~Config() {
    delete _envp;
}

Config::Config(const Config & other)
: _workerProcess(other._workerProcess), _workerConnections(other._workerConnections),
  _clientBodyBufferSize(other._clientBodyBufferSize),
  _clientHeaderBufferSize(other._clientHeaderBufferSize),
  _clientMaxBodySize(other._clientMaxBodySize),
  _listen(other._listen), _name(other._name), _index(other._index), _root(other._root),
  _allowMethods(other._allowMethods), _return(other._return), _cgiPass(other._cgiPass),
  _autoindex(other._autoindex), _code(other._code),
  _mapFdSocket(other._mapFdSocket), _mapTokenConfig(other._mapTokenConfig),
  _mapMimeType(other._mapMimeType),
  _accessLog(other._accessLog), _errorLog(other._errorLog), _pidLog(other._pidLog),
  _token(other._token), _tok(other._tok), _envp(other._envp), _configBase(const_cast<Config &>(other)){}

Config & Config::operator=(const Config & rhs){
    if (this != &rhs){
        this->_workerProcess = rhs._workerProcess;
        this->_workerConnections = rhs._workerConnections;
        this->_clientBodyBufferSize = rhs._clientBodyBufferSize;
        this->_clientHeaderBufferSize = rhs._clientHeaderBufferSize;
        this->_clientMaxBodySize = rhs._clientMaxBodySize;
        this->_listen = rhs._listen;
        this->_name = rhs._name;
        this->_index = rhs._index;
        this->_root = rhs._root;
        this->_allowMethods = rhs._allowMethods;
        this->_return = rhs._return;
        this->_cgiPass = rhs._cgiPass;
        this->_autoindex = rhs._autoindex;
        this->_code = rhs._code;
        this->_mapFdSocket = rhs._mapFdSocket;
        this->_mapTokenConfig = rhs._mapTokenConfig;
        this->_mapMimeType = rhs._mapMimeType;
        this->_accessLog = rhs._accessLog;
        this->_errorLog = rhs._errorLog;
        this->_pidLog = rhs._pidLog;
        this->_token = rhs._token;
        this->_tok = rhs._tok;
        this->_envp = rhs._envp;
    }
    return *this;
}

void Config::addChild(const Config & child) {
    if (!child._tok.empty()) {
        _mapTokenConfig.insert(std::make_pair(child._tok, child));
    }
}

void Config::addToSet(std::vector<std::string> & value, std::set<std::string> & conf) {
    if (!value.empty()) {
        for (std::vector<std::string>::iterator it = value.begin();
        it != value.end() ; ++it) {
            if (conf.find(*it) != conf.end())
                conf.insert(*it);
        }
    }
}





