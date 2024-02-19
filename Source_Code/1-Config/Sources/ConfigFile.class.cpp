/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.class.cpp                                   :+:      :+:    :+:
 */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/29 14:27:05 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/ConfigFile.class.hpp"

ConfigFile::ConfigFile(const std::string &pathToConfigFile)
    : _parent(NULL), _config(*new Config),
      _peg(*(new PegParser<ConfigFile>(pathToConfigFile.c_str(), "#"))), _id() {
  parseFile();
}

ConfigFile::ConfigFile(Config &config, PegParser<ConfigFile> &peg)
    : _parent(&config), _config(config), _peg(peg), _id() {
  parseFile();
}

ConfigFile::ConfigFile(ConfigFile &other, Config *config)
    : _parent(other._parent), _config(*(new Config(*config))),
      _peg(other._peg) {}

ConfigFile::~ConfigFile() {}

void ConfigFile::printData() {
  for (std::map<int, Socket *>::iterator itSock = _config._mapFdSocket.begin();
       itSock != _config._mapFdSocket.end(); ++itSock) {
    cout << "Socket fd => " + intToString(itSock->first) << endl;
    cout << "ipaddress => " + itSock->second->getIpAddress() + " port => " +
                intToString(itSock->second->getPort())
         << endl;
    for (std::vector<std::pair<std::string, std::string> >::iterator
             itNameToken = itSock->second->getVectorServerNameToken().begin();
         itNameToken != itSock->second->getVectorServerNameToken().end();
         ++itNameToken) {
      cout << "server name => " + itNameToken->first + " = Token => " +
                  itNameToken->second
           << endl;
      for (std::map<std::string,
                    std::vector<std::pair<std::string, Config> > >::iterator
               itToken = _config._mapTokenVectorUriConfig.begin();
           itToken != _config._mapTokenVectorUriConfig.end(); ++itToken) {
        if (itToken->first == itNameToken->second) {
          for (std::vector<std::pair<std::string, Config> >::iterator itConfig =
                   itToken->second.begin();
               itConfig != itToken->second.end(); ++itConfig) {
            cout << "uri => " + itConfig->first << endl;
            for (std::set<std::string>::iterator itIndex =
                     itConfig->second._index.begin();
                 itIndex != itConfig->second._index.end(); ++itIndex) {
              cout << "index => " + *itIndex << endl;
            }
            cout << "root => " + itConfig->second._root << endl;
            cout << "allow method => " +
                        intToString(itConfig->second._allowMethods)
                 << endl;
            cout << "cgi => " + itConfig->second._cgiPass << endl;
            cout << "autoIndex => " +
                        (std::string)((itConfig->second._autoindex) ? "true"
                                                                    : "false")
                 << endl;
            cout << "return => " + intToString(itConfig->second._return)
                 << endl;
          }
        }
      }
    }
  }
}
void ConfigFile::parseFile() {
  cout << "\r\n\r\n\t\t\t\t#### Config File ####\r\n\r\n" << endl;
  setMapToken("");
  while (!_peg.checkIsEmpty()) {
    _peg.findToken(*this, 0);
  }
  if (_config._mapFdSocket.empty())
    throw Exception("No IP:PORT to listen", 0);
  cout << "\r\n\r\n\t\t\t\t#### Config data ####\r\n\r\n" << endl;
  printData();
}

void ConfigFile::parseBloc(std::string &id) {
  cout << "####" + id + "####" << endl;
  _id = id;
  if (id == "server")
    _config._tok = _config._token.generateToken();
  setMapToken(id);
  while (!_peg.checkIsEndOfBloc('}'))
    _peg.findToken(*this, 0);
}

std::string ConfigFile::blocToken(std::string &token) {
  std::string value = _peg.extractData('{');
  if ((value.empty() && token != "location") ||
      (!value.empty() && value[0] == '/' && token == "location")) {
    ConfigFile configFile(*this, &_config);
    if (token == "location") {
      configFile._config._root = configFile._config._root + value;
      configFile._config._uri = value;
    }
    configFile.parseBloc(token);
    if (token == "location" || token == "server") {
      if (configFile._config._uri.empty())
        configFile._config._uri = "/";
      _parent->addChild(configFile._config);
      _parent->addServerName(configFile._config);
    }
    setMapToken(_id);
    return "";
  }
  return "unexpected value => " + value;
}

std::string ConfigFile::setWorkerProcesses(std::string &token) {
  (void)token;
  std::string value = _peg.extractData(';');
  char *end;
  const long val = std::strtol(value.c_str(), &end, 10);
  if (end != value.c_str() && val > 0 && val < 5) {
    _config._workerProcess = static_cast<int>(val);
    cout << "worker processes = " + value << endl;
    return "";
  }
  return "invalide data for worker processes => " + value;
}

std::string ConfigFile::setClientBodyBufferSize(std::string &token) {
  (void)token;
  std::string value = _peg.extractData(';');
  char *end;
  const long val = std::strtol(value.c_str(), &end, 10);
  if (end != value.c_str() && val > 1023 && val < 8193) {
    _config._clientBodyBufferSize = static_cast<int>(val);
    cout << "client Body buffer size = " + value << endl;
    return "";
  }
  return "invalide data for body buffer size => " + value;
}

std::string ConfigFile::setClientHeaderBufferSize(std::string &token) {
  (void)token;
  std::string value = _peg.extractData(';');
  char *end;
  const long val = std::strtol(value.c_str(), &end, 10);
  if (end != value.c_str() && val > 511 && val < 1025) {
    _config._clientHeaderBufferSize = static_cast<int>(val);
    cout << "client Header buffer size = " + value << endl;
    return "";
  }
  return "invalide data for header buffer size => " + value;
}

std::string ConfigFile::setClientMaxBodySize(std::string &token) {
  (void)token;
  std::string value = _peg.extractData(';');
  char *end;
  const long val = std::strtol(value.c_str(), &end, 10);
  if (end != value.c_str() && val > 500000 && val < 1048576) {
    _config._clientMaxBodySize = static_cast<int>(val);
    cout << "client max Body size = " + value << endl;
    return "";
  }
  return "invalide data for max body size => " + value;
}

std::string ConfigFile::setWorkerConnections(std::string &token) {
  (void)token;
  std::string value = _peg.extractData(';');
  char *end;
  const long val = std::strtol(value.c_str(), &end, 10);
  if (end != value.c_str() && val > 9 && val < 21) {
    _parent->_workerConnections = static_cast<int>(val);
    cout << "worker connection = " + value << endl;
    return "";
  }
  return "invalide data for workerConnection => " + value;
}

std::string ConfigFile::addVectorListen(std::string &token) {
  (void)token;
  std::string value = _peg.extractData(';');
  Listen listen(_config, *_parent);
  return listen.parseListenData(value);
}

std::string ConfigFile::addMapAddHeader(std::string &token) {
  (void)token;
  std::string directive = _peg.extractData(' ');
  if (directive == "Content-Disposition") {
    std::string argument = _peg.extractData(';');
    if (argument == "attachment")
      _config._addHeader = std::make_pair(directive, argument);
    return "";
  }
  return std::string("no value at add_header");
}

std::string ConfigFile::addIndex(std::string &token) {
  (void)token;
  std::stringstream value(_peg.extractData(';'));
  if (!value.str().empty()) {
    std::vector<std::string> val;
    while (!value.eof()) {
      std::string line;
      value >> line >> std::ws;
      val.push_back(line);
    }
    _config.addToSet(val, _config._index);
    cout << "index = " + value.str() << endl;
    return "";
  }
  return std::string("no value at index");
}

std::string ConfigFile::addVectorServerName(std::string &token) {
  (void)token;
  std::stringstream value(_peg.extractData(';'));
  if (!value.str().empty()) {
    std::vector<std::string> val;
    while (!value.eof()) {
      std::string line;
      value >> line >> std::ws;
      val.push_back(line);
    }
    _config._name.insert(_config._name.end(), val.begin(), val.end());
    cout << "name = " + value.str() << endl;
    return "";
  }
  return std::string("no value at server_name");
}

std::string ConfigFile::setRoot(std::string &token) {
  (void)token;
  std::string root = _peg.extractData(';');
  if (root.empty())
    return std::string("no value at root");
  struct stat statBuf;
  if (stat(root.c_str(), &statBuf) == 0)
    _config._root = root;
  else
    return "Path not found => " + root;
  cout << "root = " + root << endl;
  return std::string("");
}

std::string ConfigFile::setCgiPass(std::string &token) {
  (void)token;
  std::string cgi = _peg.extractData(';');
  if (cgi.empty())
    return std::string("no value at cgi");
  _config._cgiPass = cgi;
  cout << "cgi pass = " + cgi << endl;
  return std::string("");
}

std::string ConfigFile::setAllowMethods(std::string &token) {
  (void)token;
  int _get = 0;
  int _post = 0;
  int _delete = 0;

  std::stringstream value(_peg.extractData(';'));
  if (!value.str().empty()) {
    while (!value.eof()) {
      std::string line;
      value >> line >> std::ws;
      if (line == "GET")
        _get = 1;
      else if (line == "POST")
        _post = 2;
      else if (line == "DELETE")
        _delete = 4;
      else
        return line += " not allowed methods";
    }
    if (_config._allowMethods > _get + _post + _delete)
      _config._allowMethods = _get + _post + _delete;
    cout << "allow methods = " + value.str() +
                "conf = " + intToString(_config._allowMethods)
         << endl;
    return "";
  }
  return std::string("no value at allow_methods");
}

std::string ConfigFile::setErrorPage(std::string &token) {
  (void)token;
  std::stringstream value(_peg.extractData(';'));
  if (!value.str().empty()) {
    std::string line;
    value >> line >> std::ws;
    char *end;
    const long code = std::strtol(line.c_str(), &end, 10);
    if (end == line.c_str() || code < 100 || code > 599 ||
        !_config._code.FindCode((int)code)) {
      line = "value in code invalid for return => " + line;
      return line;
    }
    line.clear();
    value >> line >> std::ws;
    if (value.eof()) {
      if (!line.empty()) {
        _config._code.setDefaultPage((int)code, line);
        cout << "error page = " + value.str() << endl;
        return "";
      }
      return "no index to set";
    }
    return "to much value in error page";
  }
  return "no value at error page";
}

std::string ConfigFile::setReturn(std::string &token) {
  (void)token;
  std::stringstream value(_peg.extractData(';'));
  if (!value.str().empty()) {
    std::string line;
    value >> line >> std::ws;
    char *end;
    const long code = std::strtol(line.c_str(), &end, 10);
    if (end == line.c_str() || code < 100 || code > 599 ||
        !_config._code.FindCode((int)code)) {
      line = "value in code invalid for return => " + line;
      return line;
    }
    value >> line >> std::ws;
    if (value.eof()) {
      if (line[0] == '\"' && line[line.size()] == '\"' && _config._return == 0)
        _config._code.setStatus((int)code, line.substr(1, line.size() - 3));
      else if (_config._return == 0) {
        if ((line.find("http://www.") != 0) ||
            line.substr(line.find_last_of('.')) != "html")
          return "not html or http://www. content in return";
        _config._code.setDefaultPage((int)code, line);
      } else
        return "";
      _config._return = (int)code;
      cout << "return = " + value.str() << endl;
      return "";
    }
    return std::string("to much value in return");
  }
  return std::string("no value at return");
}

std::string ConfigFile::setAutoIndex(std::string &token) {
  (void)token;
  std::string value = _peg.extractData(';');
  if (value.empty())
    return std::string("no value at auto index");
  if (value == "on" || value == "off")
    _config._autoindex = (value == "on");
  else
    return std::string("error value at auto index");
  cout << "auto index = " + (std::string)((_config._autoindex) ? "on" : "off")
       << endl;
  return std::string("");
}

void ConfigFile::setMapToken(const std::string &token) {
  if (token.empty())
    _peg.setMapTokenFile();
  else if (token == "events")
    _peg.setMapTokenEvents();
  else if (token == "http")
    _peg.setMapTokenHttp();
  else if (token == "server")
    _peg.setMapTokenServer();
  else if (token == "location")
    _peg.setMapTokenLocation();
  else
    _peg.clearMapToken();
}
