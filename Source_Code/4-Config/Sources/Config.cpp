

#include "../Includes/Config.hpp"

Config::Config()
    : _workerProcess(1), _workerConnections(10), _clientBodyBufferSize(8192),
      _clientHeaderBufferSize(1024), _clientMaxBodySize(1048576), _name(),
      _index(), _root("www/default.com"), _uri(),
      _allowMethods(7), _addHeader(), _return(), _cgiPass(), _autoindex(false),
      _code(), _mapFdSocket(), _mapTokenVectorUriConfig(), _types(), _log(),
      _token(), _tok(), _envp(), _configBase(*this) {
  _name.push_back("localhost");
  _index.insert("index.html");
} //@todo add free envp

Config::~Config() {
  delete _envp;
  for (std::map<int, Socket *>::iterator itSoc = _mapFdSocket.begin();
       itSoc != _mapFdSocket.end(); ++itSoc) {
    delete itSoc->second;
  }
}

Config::Config(const Config &other)
    : _workerProcess(other._workerProcess),
      _workerConnections(other._workerConnections),
      _clientBodyBufferSize(other._clientBodyBufferSize),
      _clientHeaderBufferSize(other._clientHeaderBufferSize),
      _clientMaxBodySize(other._clientMaxBodySize), _name(other._name),
      _index(other._index), _root(other._root), _uri(),
      _allowMethods(other._allowMethods), _addHeader(other._addHeader),
      _return(), _cgiPass(), _autoindex(other._autoindex), _code(other._code),
      _mapFdSocket(), _mapTokenVectorUriConfig(
          other._mapTokenVectorUriConfig),
      _types(), _log(other._log), _token(other._token), _tok(other._tok),
      _envp(other._envp), _configBase(const_cast<Config &>(other)) {}

Config &Config::operator=(const Config &rhs) {
  if (this != &rhs) {
    this->_workerProcess = rhs._workerProcess;
    this->_workerConnections = rhs._workerConnections;
    this->_clientBodyBufferSize = rhs._clientBodyBufferSize;
    this->_clientHeaderBufferSize = rhs._clientHeaderBufferSize;
    this->_clientMaxBodySize = rhs._clientMaxBodySize;
    this->_name = rhs._name;
    this->_index = rhs._index;
    this->_root = rhs._root;
    this->_uri = rhs._uri;
    this->_allowMethods = rhs._allowMethods;
    this->_addHeader = rhs._addHeader;
    this->_return = rhs._return;
    this->_cgiPass = rhs._cgiPass;
    this->_autoindex = rhs._autoindex;
    this->_code = rhs._code;
    this->_mapFdSocket = rhs._mapFdSocket;
    this->_types = rhs._types;
    this->_log = rhs._log;
    this->_token = rhs._token;
    this->_tok = rhs._tok;
    this->_envp = rhs._envp;
  }
  return *this;
}

void Config::addChild(const Config &child) {
  if (_mapTokenVectorUriConfig.find(child._tok) !=
      _mapTokenVectorUriConfig.end()) {
    _mapTokenVectorUriConfig.find(child._tok)
        ->second.push_back(std::make_pair(child._uri, child));
  } else if (!child._tok.empty()) {
    _mapTokenVectorUriConfig[child._tok] =
        vecPairStrConf(1, make_pair(child._uri, child));
  }
}

void Config::addToSet(vecStr &value, setStr &conf) {
  if (!value.empty()) {
    for (vecStrIt it = value.begin();
         it != value.end(); ++it) {
      if (conf.find(*it) == conf.end())
        conf.insert(*it);
    }
  }
}

void Config::addServerName(Config &child) {
//  (void)child;
  for (mapFdSockPtrIt sockIt = _mapFdSocket.begin();
        sockIt != _mapFdSocket.end(); ++sockIt) {
       sockIt->second->addServerName(child._name, child._tok);
   }
}
