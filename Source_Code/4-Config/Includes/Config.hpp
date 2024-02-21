//
// Created by Matthis DoQuocBao on 2023-06-13.
//

#ifndef WEBSERVER_CONFIG_HPP
#define WEBSERVER_CONFIG_HPP

#include "../../1-Code/Includes/Code.class.hpp"
#include "../../10-Exception/Includes/Exception.hpp"
#include "../../12-Utils/Includes/Utils.hpp"
#include "../../13-Log/Includes/Log.class.hpp"
#include "../../2-Type/Includes/Types.class.hpp"
#include "../../5-Socket/Includes/Socket.class.hpp"
#include "../../6-Token/Includes/Token.class.hpp"

struct Config {

  Config();

  virtual ~Config();

  Config(const Config &other);

  Config &operator=(const Config &rhs);

  void addChild(const Config &child);

  void addServerName(Config &child);

  void addToSet(vecStr &value, setStr &conf);

  /*data config for each bloc*/
  int _workerProcess;
  int _workerConnections;
  int _clientBodyBufferSize;
  int _clientHeaderBufferSize;
  int _clientMaxBodySize;
  vecStr _name;
  setStr _index;
  string _root;
  string _uri;
  int _allowMethods; // GET = 1 POST = 2 DELETE = 4 GET/POST = 3 GET/DELETE = 5
                     // POST/DELETE = 6 ALL = 7
  pairStrStr _addHeader;
  int _return;     // return code [text]; text == uri or custom code
  string _cgiPass; // /path=>>cgi
  bool _autoindex; // on/off
  Code _code;      // code class

  /*data to store config*/
  mapFdSockPtr _mapFdSocket; // map int fd and Socket class for first
                           // : fd/server for server fd/client
  mapStrVecPairStrConf _mapTokenVectorUriConfig; // map id token and config chil
  Types _types; // mime type data

  /*environnement de travail*/
  Log _log;            // acces to log file
  Token _token;        // Token.class class
  string _tok;    // token for this
  char **_envp;        // envp
  Config &_configBase; // reference on first config
};

#endif // WEBSERVER_CONFIG_HPP
